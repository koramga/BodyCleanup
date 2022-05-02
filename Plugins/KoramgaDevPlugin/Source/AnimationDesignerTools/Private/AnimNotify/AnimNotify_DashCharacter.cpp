// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotify/AnimNotify_DashCharacter.h"

#include "GameFramework/Character.h"

UAnimNotify_DashCharacter::UAnimNotify_DashCharacter()
{
#if WITH_EDITORONLY_DATA
	NotifyColor = FColor::Green;
#endif		
}

void UAnimNotify_DashCharacter::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	
	if(IsValid(MeshComp))
	{
		AActor* Owner = MeshComp->GetOwner();

		ACharacter* Character = Cast<ACharacter>(Owner);

		if(IsValid(Character))
		{
			Character->LaunchCharacter(Character->GetActorForwardVector() * LaunchPower, false, false);
		}		
	}
}

FString UAnimNotify_DashCharacter::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}