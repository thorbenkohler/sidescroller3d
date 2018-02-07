// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScrollerStatics.h"
#include "Engine.h"

ASideScrollerGameMode* USideScrollerStatics::GetSideScrollerGameMode(UObject* WorldContextObject)
{
	return Cast<ASideScrollerGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
}

TArray<UObject*> USideScrollerStatics::LoadObjectLibrary(const FString& Path, TSubclassOf<UObject> ObjectClass)
{
	TArray<UObject*> Assets;

	UObjectLibrary* ObjectLibrary = UObjectLibrary::CreateLibrary(ObjectClass, false, GIsEditor);
	if (ObjectLibrary != nullptr)
	{
		ObjectLibrary->AddToRoot();
		FString NewPath = TEXT("/Game") / Path;
		int32 NumOfAssetDatas = ObjectLibrary->LoadAssetDataFromPath(NewPath);
		TArray<FAssetData> AssetDatas;
		ObjectLibrary->GetAssetDataList(AssetDatas);


		UObject* Asset;

		for (int32 i = 0; i < AssetDatas.Num(); ++i)
		{
			FAssetData& AssetData = AssetDatas[i];
			Asset = AssetData.GetAsset();
			if (Asset)
			{
				Assets.Add(AssetData.GetAsset());
			}
		}
	}
	return Assets;
}
