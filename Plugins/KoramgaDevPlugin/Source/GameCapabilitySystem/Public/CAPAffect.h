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
	
	//SourceCapabilitySystemComponent는 무조건 살아있다고 보장하지 못한다. 그렇지만 동작할 수 있어야 한다.
	//Target은 살아있고, Source는 죽을 경우가 존재하기 때문
	//우선 그 반대의 경우는 쿨하게 무시해도 되는데, [Target이 사라졌으므로 의미가 없으니까] 그렇지만 Source가 사라지는건 의미가 있음
	//ex) Projectile의 경우 Source가 Projectile, Character는 Target인 경우 Source는 의미없지만 Target은 의미가 있음.
	TSoftObjectPtr<class UCapabilitySystemComponent>	SourceCapabilitySystemComponent;
	TSoftObjectPtr<class UCapabilitySystemComponent>	TargetCapabilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FCAPEffectAdvantage>						Advantages;
	
protected:
	bool											bIsDone = false;
	bool											bIsFinish = false;
	float											RemainTime = 0.f;
	float											TotalTickTime = 0.f;
	FHitResult										HitResult;
	
private :
	void __SetDone();

protected:
	bool ProcessDone();
	
public :
	void SetEffect(TSoftObjectPtr<class UCAPEffect> InCAPEffect, int32 InAbilityLevel, float InWeight = 0.f);
	void SetAdvantage(const TArray<FCAPEffectAdvantage>& InAdvantages);
	void SetSourceCapabilitySystemComponent(class UCapabilitySystemComponent* InSourceCapabilitySystemComponent);
	void SetTargetCapabilitySystemComponent(class UCapabilitySystemComponent* InTargetCapabilitySystemComponent);
	void SetHitResult(const FHitResult& InHitResult);
	
public :
	void BeginPlay();
	void Tick(float DeltaTime);
	bool IsDone() const;
	const TSoftObjectPtr<class UCAPEffect> GetEffect() const;
};

