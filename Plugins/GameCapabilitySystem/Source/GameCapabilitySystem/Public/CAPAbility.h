// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"
#include "CAPAbility.generated.h"

/**
 * 
 */
UCLASS(DefaultToInstanced, Blueprintable)
class GAMECAPABILITYSYSTEM_API UCAPAbility : public UObject
{
	GENERATED_BODY()

protected:
	//Ability Tag입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Tags")
	FGameplayTagContainer				AbilityTags;

	//비용으로 사용되는 이펙트입니다. 마나를 소모한다거나 등등에 활용합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Costs")
	TSubclassOf<class UCAPEffect>		CostCAPEffectClass;

	//스킬을 사용하고 난 뒤 적용되는 쿨다운 시간입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Cooldown")
	float								Cooldown = 1.f;

	//초기 쿨다운 시간입니다. 보스같은 중요한 스킬 패턴은 바로 처음부터 나오는게 아니라 시간이 지나고 사용할 수 있어야 하므로 설정할 수 있도록 하였습니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Cooldown")
	float								InitCooldown = 0.f;
	
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

protected:
	TSoftObjectPtr<class UCapabilitySystemComponent> GetOwnerCapabilitySystemComponent() const;

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
