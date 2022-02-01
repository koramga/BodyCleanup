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
	static void FindInteractiveComponents(TArray<TSoftObjectPtr<USceneComponent>>& InputInteractiveComponents, USceneComponent* SceneComponent);
	static void FindInteractiveComponents(TArray<UActorComponent*>& InputInteractiveComponents, AActor* Actor);
	static TSoftObjectPtr<class UInteractiveSuckingComponent> FindInteractiveSuckingComponent(AActor* Actor);
};
