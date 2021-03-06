// Fill out your copyright notice in the Description page of Project Settings.


#include "Mors.h"

#include "BodyCleanup/Actor/Modular/WeaponModularActor.h"
#include "BodyCleanup/Animation/BaseAnimInstance.h"
#include "BodyCleanup/Animation/PlayerCharacter/PlayerCharacterAnimInstance.h"
#include "BodyCleanup/GCS/Utility/GameGCSFunctionLibrary.h"


// Sets default values
AMors::AMors()
{
	
}

// Called when the game starts or when spawned
void AMors::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(RangeAttackCAPAbilityClass))
	{
		AddAbility(RangeAttackCAPAbilityClass);
	}
}

void AMors::InputPressedMouseLeftClick()
{
	Super::InputPressedMouseLeftClick();
	
	if(PlayerCharacterAnimInstance->CanUpdateAnimationType(EAnimationType::Attack))
	{
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
}

void AMors::InputReleasedMouseLeftClick()
{
	Super::InputReleasedMouseLeftClick();
}

void AMors::InputPressedMouseRightClick()
{	
	Super::InputPressedMouseRightClick();

	if(PlayerCharacterAnimInstance->CanUpdateAnimationType(EAnimationType::Attack))
	{
		if(CapabilitySystemComponent->CanActivateAbilityByTag(UGameGCSFunctionLibrary::SpecialAttackGameplayTag))
		{
			//활성화 시킨다.
			if(false == CapabilitySystemComponent->TryActivateAbilityByTag(UGameGCSFunctionLibrary::SpecialAttackGameplayTag))
			{
			}
		}		
	}
}

void AMors::InputReleasedMouseRightClick()
{	
	Super::InputReleasedMouseRightClick();

	if(CapabilitySystemComponent->IsActivateAbilityByTag(UGameGCSFunctionLibrary::SpecialAttackGameplayTag))
	{
		BaseAnimInstance->UpdateMontageFromKey(EInputEvent::IE_Released);
	}
}

void AMors::InputPressedMouseWheelClick()
{	
	Super::InputPressedMouseWheelClick();

	
	if(PlayerCharacterAnimInstance->CanUpdateAnimationType(EAnimationType::Attack))
	{
		if(CapabilitySystemComponent->CanActivateAbilityByTag(UGameGCSFunctionLibrary::ChargingAttackGameplayTag))
		{
			//활성화 시킨다.
			if(false == CapabilitySystemComponent->TryActivateAbilityByTag(UGameGCSFunctionLibrary::ChargingAttackGameplayTag))
			{
			}
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

void AMors::InputPressedSpacebar()
{	
	if(PlayerCharacterAnimInstance->CanUpdateAnimationType(EAnimationType::Dash))
	{
		PlayerCharacterAnimInstance->SetAnimationType(EAnimationType::Dash);
	}
}

void AMors::InputReleasedSpacebar()
{	
	//Super::InputReleasedSpacebar();
}

// Called every frame
void AMors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

