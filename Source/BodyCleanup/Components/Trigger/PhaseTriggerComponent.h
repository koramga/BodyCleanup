// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelDesignerTools/Trigger/Classes/Actor/TriggerActorComponent.h"
#include "UObject/Object.h"
#include "PhaseTriggerComponent.generated.h"

/**
 * 
*/
USTRUCT(BlueprintType)
struct BODYCLEANUP_API FPhaseInput
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float				HPPercent;
};

UCLASS( ClassGroup=(Triggers), meta=(BlueprintSpawnableComponent) )
class BODYCLEANUP_API UPhaseTriggerComponent : public UTriggerActorComponent
{
	GENERATED_BODY()

public :
	UPhaseTriggerComponent();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam) override;

public :
	virtual void UpdateAction(const FLevelTriggerUpdateActionParam& LevelTriggerUpdateActionParam) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|PhaseTriggerComponent")
	TArray<FPhaseInput>			PhaseInputs;
	
	TSoftObjectPtr<class UCapabilitySystemComponent>	CapabilitySystemComponent;

	FName	MaxHPStatName;
	FName	HPStatName;
	TSoftObjectPtr<class ABaseNPCCharacter>				BaseNPCCharacter;
	//TWeakPtr<class FCAPAttributeData>					MaxHPAttributeData;
	//FCAPAttributeData>							HPAttributeData;
};
