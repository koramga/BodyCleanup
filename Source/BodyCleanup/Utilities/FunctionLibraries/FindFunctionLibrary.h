// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FindFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UFindFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public :
	static USceneComponent* FindComponentByName(USceneComponent* SceneComponent, const FName& Name);
	static void FindComponentsByNames(TArray<TSoftObjectPtr<USceneComponent>>& NameComponents, USceneComponent* SceneComponent, const TArray<FName>& Names);
	static void FindComponentsByTagName(TArray<TSoftObjectPtr<USceneComponent>>& TagComponents, AActor* Actor, const FName& TagName);
	static void FindComponentsByTagNames(TArray<TSoftObjectPtr<USceneComponent>>& TagComponents, AActor* Actor, const TArray<FName>& TagNames);
	static UPrimitiveComponent* FindPrimitiveComponentByName(USceneComponent* SceneComponent, const FName& Name);
	static void FindPrimitiveComponentsByNames(TArray<TSoftObjectPtr<UPrimitiveComponent>>& NameComponents, USceneComponent* SceneComponent, const TArray<FName>& Names);
	static void FindPrimitiveComponentsByTagName(TArray<TSoftObjectPtr<UPrimitiveComponent>>& TagComponents, AActor* Actor, const FName& TagName);
	static void FindPrimitiveComponentsByTagNames(TArray<TSoftObjectPtr<UPrimitiveComponent>>& TagComponents, AActor* Actor, const TArray<FName>& TagNames);
	static USceneComponent* FindTriggerComponentByName(USceneComponent* SceneComponent, const FName& Name);
	static void FindTriggerComponents(TArray<TSoftObjectPtr<USceneComponent>>& InputTriggerComponents, USceneComponent* SceneComponent);
	static void FindTriggerComponentsByTagName(TArray<TSoftObjectPtr<USceneComponent>>& InputTriggerComponents, AActor* Actor, const FName& TagName);
	static USceneComponent* FindMarkupComponentByName(USceneComponent* SceneComponent, const FName& Name);
	static void FindMarkupComponentsByNames(TArray<TSoftObjectPtr<USceneComponent>>& InputMarkupComponents, USceneComponent* SceneComponent, const TArray<FName>& Names);
	static void FindMarkupComponentsByTagName(TArray<TSoftObjectPtr<USceneComponent>>& InputMarkupComponents, AActor* Actor, const FName& TagName);
	static void FindMarkupComponentsByTagNames(TArray<TSoftObjectPtr<USceneComponent>>& InputMarkupComponents, AActor* Actor, const TArray<FName>& TagNames);
	static void FindInteractiveComponents(TArray<TSoftObjectPtr<USceneComponent>>& InputInteractiveComponents, USceneComponent* SceneComponent);
	static USceneComponent* FindInteractiveComponentByName(USceneComponent* SceneComponent, const FName& Name);
	static void FindInteractiveComponentsByNames(TArray<TSoftObjectPtr<USceneComponent>>& InputInteractiveComponents, USceneComponent* SceneComponent, const TArray<FName>& Names);
	static void FindInteractiveComponentsByTagName(TArray<TSoftObjectPtr<USceneComponent>>& InputInteractiveComponents, AActor* Actor, const FName& TagName);
	static void FindInteractiveComponentsByTagNames(TArray<TSoftObjectPtr<USceneComponent>>& InputInteractiveComponents, AActor* Actor, const TArray<FName>& TagNames);
};
