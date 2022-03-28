// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotify_ChangeOfState.h"

#include "Interface/Actor/AnimationToolsActorInterface.h"

UAnimNotify_ChangeOfState::UAnimNotify_ChangeOfState()
{
#if WITH_EDITORONLY_DATA
	NotifyColor = FColor::Green;
#endif	
}

void UAnimNotify_ChangeOfState::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if(IsValid(MeshComp))
	{
		if(MeshComp->GetOwner()->GetClass()->ImplementsInterface(UAnimationToolsActorInterface::StaticClass()))
		{
			IAnimationToolsActorInterface* AnimationToolsActorInterface = Cast<IAnimationToolsActorInterface>(MeshComp->GetOwner());

			AnimationToolsActorInterface->OnChangeOfStateFromNotify(ChangeOfStateStruct);
		}		
	}
}

FString UAnimNotify_ChangeOfState::GetNotifyName_Implementation() const
{
	if(EAnimNotify_ChangeOfStateType::EnableBeDamaged == ChangeOfStateStruct.Type)
	{
		FString EnableText = "Disable";
		
		if(true == ChangeOfStateStruct.bIsEnabled)
		{
			EnableText = "Enable";
		}

		return FString::Printf(TEXT("BeDamanged_%s"), *EnableText);
	}
	else if(EAnimNotify_ChangeOfStateType::EnableCollision == ChangeOfStateStruct.Type)
	{
		FString EnableText = "Disable";
		
		if(true == ChangeOfStateStruct.bIsEnabled)
		{
			EnableText = "Enable";
		}

		return FString::Printf(TEXT("Attack_%s"), *EnableText);
	}
	
	return "None";
}
