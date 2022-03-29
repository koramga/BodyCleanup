// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterAnimInstance.h"

#include "BodyCleanup/Character/PlayerCharacter/BasePlayerCharacter.h"

void UPlayerCharacterAnimInstance::UpdateMontage(float DeltaSeconds)
{
	UAnimMontage* CurrentActivateMontage = GetCurrentActiveMontage();

	if (IsValid(CurrentActivateMontage))
	{
		FName CurrentMontageSectionName = Montage_GetCurrentSection(CurrentActivateMontage);

		if(MontageCurrentSectionName == NAME_None
			|| MontageCurrentSectionName != CurrentMontageSectionName)
		{
			MontageCurrentSectionName = CurrentMontageSectionName;
			
			if(EMontageSectionType::Aim == MontageSectionType)
			{
				if(BasePlayerCharacter.IsValid())
				{
					BasePlayerCharacter->SetAimMode(false);
				}
			}		
			
			NextSectionName = NAME_None;
			PressedSectionName = NAME_None;
			ReleasedSectionName = NAME_None;
			MontageSectionType = EMontageSectionType::Normal;
			
			const TArray<UAnimMetaData*> MetaDatas = CurrentActivateMontage->GetSectionMetaData(MontageCurrentSectionName);

			for(UAnimMetaData* MetaData : MetaDatas)
			{
				UMontageSectionFlow* MontageSectionFlow = Cast<UMontageSectionFlow>(MetaData);

				if(IsValid(MontageSectionFlow))
				{			
				
					NextSectionName = MontageSectionFlow->GetNextSectionName();
					PressedSectionName = MontageSectionFlow->GetPressedSectionName();
					ReleasedSectionName = MontageSectionFlow->GetReleasedSectionName();
					MontageSectionType = MontageSectionFlow->GetSectionType();

					if(EMontageSectionType::Normal == MontageSectionType)
					{
						if(BasePlayerCharacter.IsValid())
						{
							BasePlayerCharacter->SetLookAtMousePoint();				
						}						
					}

					switch (MontageSectionFlow->GetNextSectionType())
					{
					case EMontageNextSectionType::Self :
						MontageNextSectionName = MontageCurrentSectionName;
						break;
						
					case EMontageNextSectionType::Next :
						MontageNextSectionName = NextSectionName;
						break;
						
					case EMontageNextSectionType::Pressed:
						MontageNextSectionName = PressedSectionName;
						break;
						
					case EMontageNextSectionType::Released:
						MontageNextSectionName = ReleasedSectionName;
						break;
					}

					Montage_SetNextSection(MontageCurrentSectionName, MontageNextSectionName);

					if(EMontageSectionType::Aim == MontageSectionType)
					{
						if(BasePlayerCharacter.IsValid())
						{
							BasePlayerCharacter->SetAimMode(true);
						}
					}

					break;
				}
			}
		}
		else
		{
			if(EMontageSectionType::Energy == MontageSectionType)
			{
				if(BasePlayerCharacter.IsValid())
				{
					UCapabilitySystemComponent* CapabilitySystemComponent = BasePlayerCharacter->GetCapabilitySystemComponent();

					if(IsValid(CapabilitySystemComponent))
					{
						TSoftObjectPtr<UCAPAbility> CAPActivateAbility = CapabilitySystemComponent->GetActivateAbility();

						if(CAPActivateAbility.IsValid())
						{
							CAPActivateAbility->AddWeight(DeltaSeconds);
						}
					}
				}
			}
			else if(EMontageSectionType::Aim == MontageSectionType)
			{
				//if(BasePlayerCharacter.IsValid())
				//{
				//	BasePlayerCharacter->SetLookAtMousePoint();
				//}
			}
		}
	}
}

void UPlayerCharacterAnimInstance::OnMontageUpdateFromKey(EInputEvent InputEvent)
{
	Super::OnMontageUpdateFromKey(InputEvent);

	if(EInputEvent::IE_Pressed == InputEvent)
	{
		if(PressedSectionName != NAME_None
			&& MontageNextSectionName != PressedSectionName)
		{
			ChangeMontageSection(PressedSectionName);
		}
	}
	else if(EInputEvent::IE_Released == InputEvent)
	{
		if(ReleasedSectionName != NAME_None
			&& MontageNextSectionName != ReleasedSectionName)
		{
			ChangeMontageSection(ReleasedSectionName, true);
		}
	}
}

void UPlayerCharacterAnimInstance::ChangeMontageSection(FName InputMontageNextSectionName, bool bJumpToSection)
{
	if (CanChangeMontageSection())
	{
		UAnimMontage* CurrentActivateMontage = GetCurrentActiveMontage();

		if (IsValid(CurrentActivateMontage))
		{
			if (bJumpToSection)
			{
				Montage_JumpToSection(InputMontageNextSectionName);
			}
			else
			{
				Montage_SetNextSection(MontageCurrentSectionName, InputMontageNextSectionName);
			}

			MontageNextSectionName = InputMontageNextSectionName;
		}
	}
}

bool UPlayerCharacterAnimInstance::CanChangeMontageSection() const
{
	return true;
}

void UPlayerCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	BasePlayerCharacter = Cast<ABasePlayerCharacter>(TryGetPawnOwner());
}

void UPlayerCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	UpdateMontage(DeltaSeconds);
}

bool UPlayerCharacterAnimInstance::CanMove() const
{
	if (EAnimationType::Wait == AnimationType)
	{
		return false;
	}

	return Super::CanMove();
}

void UPlayerCharacterAnimInstance::OnMontagePlay(UAnimMontage* AnimMontage)
{
	Super::OnMontagePlay(AnimMontage);

	MontageCurrentSectionName = NAME_None;
}

void UPlayerCharacterAnimInstance::SetMoveOffset(int32 InputMoveOffset)
{
	MoveOffset = InputMoveOffset;
}
