// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TriggerComponent.h"
#include "Interfaces/LevelActionInterface.h"
#include "ActionComponent.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UActionComponent : public UTriggerComponent, public ILevelActionInterface
{
	GENERATED_BODY()

public :
	UActionComponent();

protected :
	//TickTock Type을 정의합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|ActionComponent")
	EActionComponentActionType	ActionType;

protected :
	//사용자가 원하는 형태로의 변형이 이루어지고 있는지를 판단한다. 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug|ActionComponent")
	bool						bIsUpdateDestinationTransformed = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected :
	virtual void OnTrigger(bool bInputIsOnTrigger) override;
	virtual void UpdateTrigger(bool bInputIsOnTrigger) override;

protected:
	USceneComponent* FindMarkupComponentByName(USceneComponent* SceneComponent, const FName& Name) const;
	void FindMarkupComponentByTagName(TArray<TSoftObjectPtr<UActorComponent>>& InputMarkupComponents, AActor* Actor, const FName& TagName) const;

public :
	bool IsUpdateDestinationTransformed() const;
};
