// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LevelSupportFunctionLibrary.generated.h"

/**
 * 
 */

class ILevelTriggerInterface;
class ILevelMarkupInterface;

UCLASS()
class LEVELDESIGNERTOOLS_API ULevelSupportFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public :
	static void FindPrimitiveComponets(TArray<TSoftObjectPtr<UPrimitiveComponent>>& Components, AActor* Actor);
	static UPrimitiveComponent* FindPrimitiveComponentByName(AActor* Actor, const FName& Name);
	static void FindPrimitiveComponentsByNames(TArray<TSoftObjectPtr<UPrimitiveComponent>>& PrimitiveComponents, AActor* Actor, const TArray<FName>& Names);
	static void FindPrimitiveComponentsByTag(TArray<TSoftObjectPtr<UPrimitiveComponent>>& PrimitiveComponents, AActor* Actor, const FName& Tag);
	static void FindPrimitiveComponentsByTags(TArray<TSoftObjectPtr<UPrimitiveComponent>>& PrimitiveComponents, AActor* Actor, const TArray<FName>& Tags);
	static void FindTriggerInterfaces(TArray<TSoftObjectPtr<ILevelTriggerInterface>>& InputTriggerComponents, AActor* Actor);
	static ILevelTriggerInterface* FindTriggerInterfaceByName(AActor* Actor, const FName& Name);
	static void FindTriggerInterfacesByNames(TArray<TSoftObjectPtr<ILevelTriggerInterface>>& InputTriggerComponents, AActor* Actor, const TArray<FName>& Names);
	static void FindTriggerInterfacesByTag(TArray<TSoftObjectPtr<ILevelTriggerInterface>>& InputTriggerComponents, AActor* Actor, const FName& Tag);
	static void FindTriggerInterfacesByTags(TArray<TSoftObjectPtr<ILevelTriggerInterface>>& InputTriggerComponents, AActor* Actor, const TArray<FName>& Tags);
	static void FindMarkupInterfaces(TArray<TSoftObjectPtr<ILevelMarkupInterface>>& InputTriggerComponents, AActor* Actor);
	static ILevelMarkupInterface* FindMarkupInterfaceByName(AActor* Actor, const FName& Name);
	static void FindMarkupInterfacesByNames(TArray<TSoftObjectPtr<ILevelMarkupInterface>>& InputMarkupInterfaces, AActor* Actor, const TArray<FName>& Names);
	static void FindMarkupInterfacesByTag(TArray<TSoftObjectPtr<ILevelMarkupInterface>>& InputMarkupInterfaces, AActor* Actor, const FName& Tag);
	static void FindMarkupInterfacesByTags(TArray<TSoftObjectPtr<ILevelMarkupInterface>>& InputMarkupInterfaces, AActor* Actor, const TArray<FName>& Tags);
};
