// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ComponentFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UComponentFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public :
	//static void FindComponentByClass(TArray<TSoftObjectPtr<UActorComponent>>& Components, USceneComponent* SceneComponent, UClass* Class);
	//static void FindPrimitiveComponets(TArray<TSoftObjectPtr<UPrimitiveComponent>>& Components, USceneComponent* SceneComponent);
	//static USceneComponent* FindComponentByName(USceneComponent* SceneComponent, const FName& Name);
	//static void FindComponentsByNames(TArray<TSoftObjectPtr<USceneComponent>>& NameComponents, USceneComponent* SceneComponent, const TArray<FName>& Names);
	//static void FindComponentsByTagName(TArray<TSoftObjectPtr<USceneComponent>>& TagComponents, AActor* Actor, const FName& TagName);
	//static void FindComponentsByTagNames(TArray<TSoftObjectPtr<USceneComponent>>& TagComponents, AActor* Actor, const TArray<FName>& TagNames);
	//static UPrimitiveComponent* FindPrimitiveComponentByName(USceneComponent* SceneComponent, const FName& Name);
	//static void FindPrimitiveComponentsByNames(TArray<TSoftObjectPtr<UPrimitiveComponent>>& NameComponents, USceneComponent* SceneComponent, const TArray<FName>& Names);
	//static void FindPrimitiveComponentsByTagName(TArray<TSoftObjectPtr<UPrimitiveComponent>>& TagComponents, AActor* Actor, const FName& TagName);
	//static void FindPrimitiveComponentsByTagNames(TArray<TSoftObjectPtr<UPrimitiveComponent>>& TagComponents, AActor* Actor, const TArray<FName>& TagNames);
	//static USceneComponent* FindTriggerComponentByName(USceneComponent* SceneComponent, const FName& Name);
	//static void FindTriggerComponents(TArray<TSoftObjectPtr<USceneComponent>>& InputTriggerComponents, USceneComponent* SceneComponent);
	//static void FindTriggerComponentsByTagName(TArray<TSoftObjectPtr<USceneComponent>>& InputTriggerComponents, AActor* Actor, const FName& TagName);
	//static USceneComponent* FindMarkupComponentByName(USceneComponent* SceneComponent, const FName& Name);
	//static void FindMarkupComponentsByNames(TArray<TSoftObjectPtr<USceneComponent>>& InputMarkupComponents, USceneComponent* SceneComponent, const TArray<FName>& Names);
	//static void FindMarkupComponentsByTagName(TArray<TSoftObjectPtr<USceneComponent>>& InputMarkupComponents, AActor* Actor, const FName& TagName);
	//static void FindMarkupComponentsByTagNames(TArray<TSoftObjectPtr<USceneComponent>>& InputMarkupComponents, AActor* Actor, const TArray<FName>& TagNames);
	static void FindInteractiveComponents(TArray<TSoftObjectPtr<USceneComponent>>& InputInteractiveComponents, USceneComponent* SceneComponent);
	static void FindInteractiveComponents(TArray<UActorComponent*>& InputInteractiveComponents, AActor* Actor);
	static TSoftObjectPtr<class UInteractiveSuckingComponent> FindInteractiveSuckingComponent(AActor* Actor);
	//static USceneComponent* FindInteractiveComponentByName(USceneComponent* SceneComponent, const FName& Name);
	//static void UActorComponent*USceneComponet>>& InputInteractiveComponents, USceneComponent* SceneComponent, const TArray<FName>& Names);
	//static void UActorComponent*USceneComponet>>& InputInteractiveComponents, AActor* Actor, const FName& TagName);
	//static void UActorComponent*USceneComponet>>& InputInteractiveComponents, AActor* Actor, const TArray<FName>& TagNames);
};
