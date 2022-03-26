// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CAPAbility.h"
#include "CAPAffect.h"
#include "CAPAttributeSet.h"
#include "Components/ActorComponent.h"
#include "CAPTypes.h"
#include "GameplayTagContainer.h"
#include "CapabilitySystemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMECAPABILITYSYSTEM_API UCapabilitySystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCapabilitySystemComponent();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UCAPAttributeSet*>		CAPAttributeSets;

	//영향을 준 것
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UCAPAffect*>				OwnCAPAffects;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UCAPAbility*>			CAPAbilities;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	bool IsBlockEffect(TSoftObjectPtr<class UCAPEffect> CAPEffect);
	
public :
	TSoftObjectPtr<UCAPAttributeSet> AddAttribute(TSubclassOf<class UCAPAttributeSet> CAPAttributeSetClass);
	virtual bool ApplyGameplayEffectToTarget(TSoftObjectPtr<class UCAPEffect> CAPEffect, UCapabilitySystemComponent* Target, int32 AbilityLevel = 0, float Weight = 0, const TArray<FCAPEffectAdvantage>* Advantages = nullptr);
	virtual bool ApplyGameplayEffectToSelf(TSoftObjectPtr<class UCAPEffect> CAPEffect, int32 AbilityLevel = 0, const TArray<FCAPEffectAdvantage>* Advantages = nullptr);
	bool AffectFrom(TSoftObjectPtr<class UCAPAffect> Affect, const FName& AttributeName, ECAPModifierOp ModifierOp, float Value);
	void AffectTo(TSoftObjectPtr<class UCAPAffect> Affect);

public :
	TSoftObjectPtr<UCAPAbility> AddAbility(TSubclassOf<class UCAPAbility> CAPAbilityClass, int32 AbilityLevel);
	TSoftObjectPtr<UCAPAbility> GetAbility(TSubclassOf<class UCAPAbility> CAPAbilityClass) const;
	TSoftObjectPtr<UCAPAbility> GetActivateAbility() const;
	bool RemoveAbility(TSubclassOf<class UCAPAbility> CAPAbilityClass);

public :
	bool TryActivateAbilityByClass(TSubclassOf<UCAPAbility> AbilityClass);
	bool TryActivateAbilityByTag(const FGameplayTag& Tag);
	bool TryDeActivateAbilityByTag(const FGameplayTag& Tag);
	bool CanActivateAbilityByTag(const FGameplayTag& Tag);
	bool IsActivateAbilityByTag(const FGameplayTag& Tag);
	bool IsActivateAbilityByClass(const TSubclassOf<UCAPAbility>& Class);
};