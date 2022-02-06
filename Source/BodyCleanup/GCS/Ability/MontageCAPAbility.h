// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCAPAbility.h"
#include "BodyCleanup/ExDefines.h"
#include "MontageCAPAbility.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UMontageCAPAbility : public UBaseCAPAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage*	Montage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EAnimationType	AnimationType;

protected:
	virtual void OnActivateAbility();
	virtual void OnEndAbility();
	
public :
	virtual bool CanActivate() override;
	virtual void UpdateAnimationType(EAnimationType InAnimationType, EAnimationType BeforeAnimationType) override;
};
