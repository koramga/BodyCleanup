// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotify_CreateActor.h"
#include "Interface/Actor/AnimationToolsActorInterface.h"

UAnimNotify_CreateActor::UAnimNotify_CreateActor()
{
#if WITH_EDITORONLY_DATA
	NotifyColor = FColor::Green;
#endif	
}

void UAnimNotify_CreateActor::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if(IsValid(MeshComp))
	{
		AActor* Actor = MeshComp->GetWorld()->SpawnActor(ActorClass);

		if(BoneName != NAME_None)
		{
			int32 BoneIndex = MeshComp->GetBoneIndex(BoneName);
			FTransform BoneTransform;

			if(BoneIndex != INDEX_NONE)
			{
				BoneTransform = MeshComp->GetBoneTransform(BoneIndex);
			}
			else
			{
				BoneTransform = MeshComp->GetSocketTransform(BoneName);
			}

			UE_LOG(LogTemp, Display, TEXT("<%.2f, %.2f, %.2f>"), BoneTransform.GetLocation().X, BoneTransform.GetLocation().Y, BoneTransform.GetLocation().Z);
				
			Actor->SetActorLocation(BoneTransform.GetLocation() + MeshComp->GetOwner()->GetActorForwardVector() * DistanceOffset);
			Actor->SetActorRotation(MeshComp->GetOwner()->GetActorRotation());
		}
		
		if(MeshComp->GetOwner()->GetClass()->ImplementsInterface(UAnimationToolsActorInterface::StaticClass()))
		{
			Cast<IAnimationToolsActorInterface>(MeshComp->GetOwner())->OnCreateActorFromNotify(Actor);
		}		
	}
}

FString UAnimNotify_CreateActor::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}
