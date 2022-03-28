// Fill out your copyright notice in the Description page of Project Settings.


#include "Mors.h"

#include "BodyCleanup/Actor/Modular/WeaponModularActor.h"
#include "BodyCleanup/Animation/BaseAnimInstance.h"
#include "BodyCleanup/GCS/Utility/GameGCSFunctionLibrary.h"


// Sets default values
AMors::AMors()
{
	
}

// Called when the game starts or when spawned
void AMors::BeginPlay()
{
	Super::BeginPlay();
}

void AMors::InputPressedMouseLeftClick()
{
	Super::InputPressedMouseLeftClick();

	if(CapabilitySystemComponent->IsActivateAbilityByTag(UGameGCSFunctionLibrary::GeneralAttackGameplayTag))
	{
		BaseAnimInstance->UpdateMontageFromKey(EInputEvent::IE_Pressed);
	}
	else
	{
		if(CapabilitySystemComponent->CanActivateAbilityByTag(UGameGCSFunctionLibrary::GeneralAttackGameplayTag))
		{
			//활성화 시킨다.
			if(false == CapabilitySystemComponent->TryActivateAbilityByTag(UGameGCSFunctionLibrary::GeneralAttackGameplayTag))
			{
			
			}
		}		
	}
}

void AMors::InputReleasedMouseLeftClick()
{
	Super::InputReleasedMouseLeftClick();
}

void AMors::InputPressedMouseRightClick()
{
	Super::InputPressedMouseRightClick();
}

void AMors::InputReleasedMouseRightClick()
{
	Super::InputReleasedMouseRightClick();
}

void AMors::InputPressedMouseWheelClick()
{
	Super::InputPressedMouseWheelClick();

	if(CapabilitySystemComponent->CanActivateAbilityByTag(UGameGCSFunctionLibrary::ChargingAttackGameplayTag))
	{
		//활성화 시킨다.
		if(false == CapabilitySystemComponent->TryActivateAbilityByTag(UGameGCSFunctionLibrary::ChargingAttackGameplayTag))
		{
		}
	}
}

void AMors::InputReleasedMouseWheelClick()
{
	Super::InputReleasedMouseWheelClick();

	if(CapabilitySystemComponent->IsActivateAbilityByTag(UGameGCSFunctionLibrary::ChargingAttackGameplayTag))
	{
		BaseAnimInstance->UpdateMontageFromKey(EInputEvent::IE_Released);
	}
}

// Called every frame
void AMors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

