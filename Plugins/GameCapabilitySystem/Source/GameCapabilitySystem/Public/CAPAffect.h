// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CAPTypes.h"
#include "CAPAffect.generated.h"

/**
 * 
 */
UCLASS()
class GAMECAPABILITYSYSTEM_API UCAPAffect : public UObject
{
	GENERATED_BODY()

public :
	UCAPAffect();

protected:
	TSoftObjectPtr<class UCAPEffect>					CAPEffect;
	int32												AbilityLevel;
	float												Weight;
	TSoftObjectPtr<class UCapabilitySystemComponent>	SourceCapabilitySystemComponent;
	TSoftObjectPtr<class UCapabilitySystemComponent>	TargetCapabilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FCAPEffectAdvantage>						Advantages;
	
protected:
	bool											bIsDone = false;
	bool											bIsFinish = false;
	float											RemainTime = 0.f;
	float											TotalTickTime = 0.f;
	
private :
	void __SetDone();

protected:
	bool ProcessDone();
	
public :
	void SetEffect(TSoftObjectPtr<class UCAPEffect> InCAPEffect, int32 InAbilityLevel, float InWeight = 0.f);
	void SetAdvantage(const TArray<FCAPEffectAdvantage>& InAdvantages);
	void SetSourceCapabilitySystemComponent(class UCapabilitySystemComponent* InSourceCapabilitySystemComponent);
	void SetTargetCapabilitySystemComponent(class UCapabilitySystemComponent* InTargetCapabilitySystemComponent);
	
public :
	void BeginPlay();
	void Tick(float DeltaTime);
	bool IsDone() const;
	const TSoftObjectPtr<class UCAPEffect> GetEffect() const;
};

