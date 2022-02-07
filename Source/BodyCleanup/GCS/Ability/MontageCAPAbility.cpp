// Fill out your copyright notice in the Description page of Project Settings.


#include "MontageCAPAbility.h"
#include "CapabilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "BodyCleanup/Character/BaseCharacter.h"

void UMontageCAPAbility::OnActivateAbility()
{
	Super::OnActivateAbility();
	
	TSoftObjectPtr<UCapabilitySystemComponent> CapabilitySystemComponent = GetOwnerCapabilitySystemComponent();

	if(CapabilitySystemComponent.IsValid())
	{
		ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(CapabilitySystemComponent->GetOwner());
		
		BaseCharacter->SetAnimationType(AnimationType, Montage);
	}
}

bool UMontageCAPAbility::CanActivate()
{
	if(Super::CanActivate())
	{
		if(IsValid(Montage))
		{
			TSoftObjectPtr<UCapabilitySystemComponent> CapabilitySystemComponent = GetOwnerCapabilitySystemComponent();

			if(CapabilitySystemComponent.IsValid())
			{
				ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(CapabilitySystemComponent->GetOwner());

				if(IsValid(BaseCharacter))
				{
					if(BaseCharacter->CanUpdateAnimationType(AnimationType))
					{
						if(false == BaseCharacter->IsActivateMontage(nullptr))
						{
							return true;
						}						
					}					
				}
			}			
		}
	}

	return false;
}

void UMontageCAPAbility::OnEndAbility()
{	
	Super::OnEndAbility();
}

void UMontageCAPAbility::LeftAnimationType(EAnimationType InAnimationType)
{
	Super::LeftAnimationType(InAnimationType);

	if(AnimationType == InAnimationType)
	{
		DeActivate();
	}
}
