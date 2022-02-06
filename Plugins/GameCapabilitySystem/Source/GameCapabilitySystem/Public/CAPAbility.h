// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"
#include "CAPAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAMECAPABILITYSYSTEM_API UCAPAbility : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Tags")
	FGameplayTagContainer				AbilityTags;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Costs")
	TSubclassOf<class UCAPEffect>		CostCAPEffectClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float								Cooldown = 1.f;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Debug")
	class UCAPEffect* CostCAPEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Debug")
	bool bIsActivate = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<class UCapabilitySystemComponent>	OwnerCapabilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32	AbilityLevel = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float								CurrentCooldown;
	
protected:
	virtual void OnActivateAbility();
	virtual bool CanActivate();
	virtual void OnEndAbility();

public :
	virtual void CommitAbility();

public :
	void Initialize(TSoftObjectPtr<class UCapabilitySystemComponent> InOwnerCapabilitySystemComponent);
	void Tick(float DeltaTime);
	bool IsActivate();	
	bool Activate();
	bool DeActivate();

public :
	void SetAbilityLevel(int32 InAbilityLevel);

public :
	int32 GetAbilityLevel() const;
};
