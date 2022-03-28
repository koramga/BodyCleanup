// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraTriggerComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/GameModeBase.h"
#include "LevelDesignerTools/GameMode/LevelToolsGameModeBase.h"
#include "LevelDesignerTools/Markup/Classes/CameraMarkupComponent.h"
#include "LevelDesignerTools/Markup/Interfaces/LevelMarkupInterface.h"
#include "LevelDesignerTools/Utility/LevelSupportFunctionLibrary.h"

UCameraTriggerComponent::UCameraTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCameraTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickEnabled(false);
}

void UCameraTriggerComponent::SetupTrigger()
{
	Super::SetupTrigger();

	for(FCameraTriggerInput& CameraTriggerInput : CameraTriggerInputs)
	{
		if(ECameraTriggerInputType::CameraMarkup == CameraTriggerInput.TriggerInputType)
		{
			ILevelMarkupInterface* LevelMarkupInterface = nullptr;
			
			if(CameraTriggerInput.Actor.IsValid())
			{
				if(CameraTriggerInput.Name.IsNone())
				{
					LevelMarkupInterface = ULevelSupportFunctionLibrary::FindCameraMarkupInterface(CameraTriggerInput.Actor.Get());
				}
				else
				{
					LevelMarkupInterface = ULevelSupportFunctionLibrary::FindMarkupInterfaceByName(CameraTriggerInput.Actor.Get(), CameraTriggerInput.Name);					
				}
			}
			else
			{
				if(CameraTriggerInput.Name.IsNone())
				{
					LevelMarkupInterface = ULevelSupportFunctionLibrary::FindCameraMarkupInterface(GetOwner());
				}
				else
				{
					LevelMarkupInterface = ULevelSupportFunctionLibrary::FindMarkupInterfaceByName(GetOwner(), CameraTriggerInput.Name);					
				}					
			}		 

			if(nullptr != LevelMarkupInterface
				&& ELevelMarkupType::Camera == LevelMarkupInterface->GetLevelMarkupType())
			{
				CameraTriggerInput.CameraMarkupComponent = Cast<UCameraMarkupComponent>(LevelMarkupInterface->_getUObject());
			}
		}
	}
}

void UCameraTriggerComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	Super::UpdateTrigger(InputLevelTriggerUpdateParam);

	if(true == InputLevelTriggerUpdateParam.bIsOnTrigger)
	{
		if(CameraTriggerInputs.Num() > 0)
		{
			CurrentIndex = 0;
			__CreateTimer(CurrentIndex);
		}		
	}
	else
	{
		__DoneWork();
	}
}

void UCameraTriggerComponent::__CreateTimer(int32 InIndex)
{
	if(InIndex < 0)
	{
		GetOwner()->GetWorldTimerManager().SetTimer(TimerHandle, this, &UCameraTriggerComponent::__ReturnTimer, ReturnBlendTime, false);
	}
	else
	{
		GetOwner()->GetWorldTimerManager().SetTimer(TimerHandle, this, &UCameraTriggerComponent::__AdvanceTimer, CameraTriggerInputs[CurrentIndex].EventTime, false);
		__DoWork(&CameraTriggerInputs[InIndex]);			
	}
}

void UCameraTriggerComponent::__DestroyTimer()
{
	GetOwner()->GetWorldTimerManager().ClearTimer(TimerHandle);
}

void UCameraTriggerComponent::__AdvanceTimer()
{
	if(CurrentIndex + 1 < CameraTriggerInputs.Num())
	{
		CurrentIndex++;
		__CreateTimer(CurrentIndex);
	}
	else
	{
		if (GetWorld()->GetAuthGameMode()->GetClass()->ImplementsInterface(ULevelToolsGameModeBase::StaticClass()))
		{
			ILevelToolsGameModeBase* LevelToolsGameModeBase = Cast<ILevelToolsGameModeBase>(GetWorld()->GetAuthGameMode());

			if (nullptr != LevelToolsGameModeBase)
			{
				LevelToolsGameModeBase->UpdateTriggerOnce(this);
			}
		}

		__DoneWork();
	}
	
}

void UCameraTriggerComponent::__ReturnTimer()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if(IsValid(PlayerController))
	{
		PlayerController->EnableInput(PlayerController);
	}
}

void UCameraTriggerComponent::__DoWork(const FCameraTriggerInput* CameraTriggerInput) const
{
	if(ECameraTriggerInputType::CameraMarkup == CameraTriggerInput->TriggerInputType)
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

		if(IsValid(PlayerController))
		{
			if(CameraTriggerInput->CameraMarkupComponent.IsValid())
			{
				ULevelSupportFunctionLibrary::SetActivateCameraMarkupComponents(CameraTriggerInput->CameraMarkupComponent->GetOwner(), false);
				CameraTriggerInput->CameraMarkupComponent->Activate(true);
				PlayerController->SetViewTargetWithBlend(CameraTriggerInput->CameraMarkupComponent->GetOwner(), CameraTriggerInput->BlendTime);
			}

			if(bIsBlockPlayerInput)
			{
				PlayerController->DisableInput(PlayerController);
			}
			else
			{
				PlayerController->EnableInput(PlayerController);
			}
		}
	}
	else
	{
		
	}	
}

void UCameraTriggerComponent::__DoneWork()
{
	if(CurrentIndex >= 0)
	{
		CurrentIndex = -1;
		__DestroyTimer();
	
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

		if(IsValid(PlayerController))
		{
			PlayerController->SetViewTargetWithBlend(PlayerController->GetCharacter(), ReturnBlendTime);

			if(ReturnBlendTime > 0.f)
			{
				if(bIsBlockPlayerInput)
				{
					PlayerController->DisableInput(PlayerController);
				}
				else
				{
					PlayerController->EnableInput(PlayerController);
				}

				__CreateTimer(-1);
			}
			else
			{
				PlayerController->EnableInput(PlayerController);
			}
		}		
	}
}