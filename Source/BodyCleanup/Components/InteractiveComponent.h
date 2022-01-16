// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ExDefines.h"
#include "TriggerComponent.h"
#include "Interfaces/InteractiveInterface.h"
#include "InteractiveComponent.generated.h"

UCLASS()
class BODYCLEANUP_API UInteractiveComponent : public UTriggerComponent, public IInteractiveInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractiveComponent();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|InteractiveComponent")
	TArray<EInteractiveAction>	TriggerInteractiveActions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|InteractiveComponent")
	EInteractiveType			InteractiveType;

protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug|InteractiveComponent")
	EInteractiveAction	InteractiveAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug|InteractiveComponent")
	TSoftObjectPtr<USceneComponent>	InteractiveComponent;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	

protected :
	virtual void UpdateInteractiveAction(EInteractiveAction NextInteractiveAction, EInteractiveAction BeforeInteractiveAction);
	virtual bool CanUpdateInteractive(EInteractiveAction NextInteractiveAction, EInteractiveAction CurrentInteractiveAction);

public:
	virtual EInteractiveAction GetInteractiveAction() const override;
	virtual void SetInteractiveAction(EInteractiveAction InputInteractiveAction) override;
	virtual void SetInteractiveComponent(TSoftObjectPtr<USceneComponent> InputInteractiveComponent) override;
	virtual EInteractiveType GetInteractiveType() const override;
	virtual void SetInteractiveType(EInteractiveType InputInteractiveType) override;
};