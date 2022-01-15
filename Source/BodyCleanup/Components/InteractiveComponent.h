// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ExDefines.h"
#include "TriggerComponent.h"
#include "Interfaces/InteractiveInterface.h"
#include "InteractiveComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BODYCLEANUP_API UInteractiveComponent : public UTriggerComponent, public IInteractiveInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractiveComponent();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|InteractiveComponent")
	TArray<EInteractiveAction>	TriggerInteractiveActions;

protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug|InteractiveComponent")
	EInteractiveAction	InteractiveAction;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	

protected :
	virtual void UpdateInteractiveAction(EInteractiveAction NextInteractiveAction, EInteractiveAction BeforeInteractiveAction);

public:
	virtual EInteractiveAction GetInteractiveAction() const override;
	virtual void SetInteractiveAction(EInteractiveAction InputInteractiveAction) override;
};