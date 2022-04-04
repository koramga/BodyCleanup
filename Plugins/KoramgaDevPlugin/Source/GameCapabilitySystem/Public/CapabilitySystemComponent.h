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
	TArray<UCAPAffect*>				WorkCAPAffects;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UCAPAbility*>			CAPAbilities;

	UPROPERTY()
	FGameplayTagContainer			BlockGameplayTagContainer;

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
	FCAPAttributeData* GetAttributeDataByAttributeName(const FName& AttributeName);
	
	virtual bool ApplyGameplayEffectToTarget(TSoftObjectPtr<class UCAPEffect> CAPEffect, UCapabilitySystemComponent* Target, int32 AbilityLevel = 0, float Weight = 0, const FHitResult& HitResult = FHitResult(), const TArray<FCAPEffectAdvantage>* Advantages = nullptr);
	virtual bool ApplyGameplayEffectFromSource(TSoftObjectPtr<class UCAPEffect> CAPEffect, UCapabilitySystemComponent* Source, int32 AbilityLevel = 0, float Weight = 0, const FHitResult& HitResult = FHitResult(), const TArray<FCAPEffectAdvantage>* Advantages = nullptr);
	virtual bool ApplyGameplayEffectToSelf(TSoftObjectPtr<class UCAPEffect> CAPEffect, int32 AbilityLevel = 0, const FHitResult& HitResult = FHitResult(), const TArray<FCAPEffectAdvantage>* Advantages = nullptr);

	//AffectFrom만 있고 To는 없는 이유
	//Target은 살아있고, Source는 죽을 경우가 존재하기 때문
	//우선 그 반대의 경우는 쿨하게 무시해도 되는데, [Target이 사라졌으므로 의미가 없으니까] 그렇지만 Source가 사라지는건 의미가 있음
	//ex) Projectile의 경우 Source가 Projectile, Character는 Target인 경우 Source는 의미없지만 Target은 의미가 있음. 
	bool AffectFrom(TSoftObjectPtr<class UCAPAffect> Affect, const FName& AttributeName, ECAPModifierOp ModifierOp, float Value, const FHitResult& HitResult);
	void AddBlockGameplayTag(const FGameplayTag& GameplayTag);
	void RemoveBlockGameplayTag(const FGameplayTag& GameplayTag);

public :
	TSoftObjectPtr<UCAPAbility> AddAbility(TSubclassOf<class UCAPAbility> CAPAbilityClass, int32 AbilityLevel);
	TSoftObjectPtr<UCAPAbility> GetAbility(TSubclassOf<class UCAPAbility> CAPAbilityClass) const;
	TSoftObjectPtr<UCAPAbility> GetAbilityFromIndex(int32 Index);
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
