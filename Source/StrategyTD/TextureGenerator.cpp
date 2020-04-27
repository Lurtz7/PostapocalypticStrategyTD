// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/Texture2D.h"
#include "Engine/Texture.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/Color.h"
#include "AssetRegistryModule.h"
#include "Misc/Paths.h"
#include "TextureGenerator.h"

TextureGenerator::TextureGenerator()
{

}

void TextureGenerator::CreateProceduralTexture(int32 textureHeight, int32 textureWidth, FColor colorMap[], float noisePerlinValues[], bool isItNoiseMap)
{
	PackageName = TEXT("/Game/ProceduralTextures/");
	BaseTextureName = FString("ProcTexture");
	PackageName += BaseTextureName;

	Package = CreatePackage(NULL, *PackageName);
	GLog->Log("project dir:" + FPaths::ProjectDir());

	//Create a unique name for our asset. For example, if a texture named ProcTexture already exists the editor
	//will name the new texture as "ProcTexture_1"
	FName TextureName = FName(*PackageName);
	//FName TextureName = MakeUniqueObjectName(Package, UTexture2D::StaticClass(), FName(*BaseTextureName));
	Package->FullyLoad();

	UTexture2D* NewTexture = NewObject<UTexture2D>(Package, TextureName, RF_Public | RF_Standalone | RF_MarkAsRootSet);

	float* noisePtr;
	noisePtr = noisePerlinValues;

	if (NewTexture)
	{
		int32 TextureWidth = textureWidth;
		int32 TextureHeight = textureHeight;

		//Prevent the object and all its descedants from being deleted during garbage collecion
		NewTexture->AddToRoot();

		NewTexture->PlatformData = new FTexturePlatformData();
		NewTexture->PlatformData->SizeX = TextureWidth;
		NewTexture->PlatformData->SizeY = TextureHeight;
		NewTexture->PlatformData->PixelFormat = EPixelFormat::PF_B8G8R8A8;

		//uint8* Pixels = GeneratePixels(TextureHeight, TextureWidth);
	//Each element of the array contains a single color so in order to represent information in
	//RGBA we need to have an array of length TextureWidth * TextureHeight * 4
		float *nPtr = noisePerlinValues;
		FColor* cPtr = colorMap;
		uint8* Pixels = new uint8[TextureWidth * TextureHeight * 4];
		for (int32 y = 0; y < TextureHeight; y++)
		{
			for (int32 x = 0; x < TextureWidth; x++)
			{
				int32 CurrentPixelIndex = ((y * TextureWidth) + x);
				if (drawMode) {
					FLinearColor lerpedColor = FLinearColor::LerpUsingHSV(FLinearColor::White, FLinearColor::Black, *(nPtr + CurrentPixelIndex));

					FLinearColor* K = &lerpedColor;
					FColor b = K->ToFColor(true);

					Pixels[4 * CurrentPixelIndex] = b.B; //b
					Pixels[4 * CurrentPixelIndex + 1] = b.G; //g
					Pixels[4 * CurrentPixelIndex + 2] = b.R; //r
					Pixels[4 * CurrentPixelIndex + 3] = 255; //set A channel always to maximum
				}
				else
				{
					FColor b = *(cPtr + CurrentPixelIndex);

					Pixels[4 * CurrentPixelIndex] = b.B; //b
					Pixels[4 * CurrentPixelIndex + 1] = b.G; //g
					Pixels[4 * CurrentPixelIndex + 2] = b.R; //r
					Pixels[4 * CurrentPixelIndex + 3] = 255; //set A channel always to maximum
				}
			}
		}

		//Allocate first mipmap.
		FTexture2DMipMap* Mip = new FTexture2DMipMap();
		NewTexture->PlatformData->Mips.Add(Mip);
		Mip->SizeX = TextureWidth;
		Mip->SizeY = TextureHeight;

		//Lock the mipmap data so it can be modified
		Mip->BulkData.Lock(LOCK_READ_WRITE);
		uint8* TextureData = (uint8*)Mip->BulkData.Realloc(TextureWidth * TextureHeight * 4);
		//Copy the pixel data into the Texture data
		FMemory::Memcpy(TextureData, Pixels, sizeof(uint8) * TextureHeight * TextureWidth * 4);
		Mip->BulkData.Unlock();


		//Initialize a new texture
		NewTexture->Source.Init(TextureWidth, TextureHeight, 1, 1, ETextureSourceFormat::TSF_BGRA8, Pixels);
		NewTexture->UpdateResource();

		//Mark the package as dirty so the editor will prompt you to save the file if you haven't
		Package->MarkPackageDirty();

		//Notify the editor that we created a new asset
		FAssetRegistryModule::AssetCreated(NewTexture);

		//Auto-save the new  asset
		FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
		bool bSaved = UPackage::SavePackage(Package, NewTexture, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *PackageFileName, GError, nullptr, true, true, SAVE_NoError);

		//Since we don't need access to the pixel data anymore free the memory
		delete[] Pixels;
	}
}

