// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMonsterCharacter.h"
#include "../../../Components/Scene/SuperJumpComponent.h"
#include "BodyCleanup/Animation/BaseAnimInstance.h"

ABaseMonsterCharacter::ABaseMonsterCharacter()
{
	
}

void ABaseMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<UActorComponent*> SuperJumpComponents = GetComponentsByClass(USuperJumpComponent::StaticClass());

	for(UActorComponent* SuperJumpComponent : SuperJumpComponents)
	{
		Cast<USuperJumpComponent>(SuperJumpComponent)->SetCallbackOverlapSuperJump(this, &ABaseMonsterCharacter::__OverlapSuperJump);
	}
}

void ABaseMonsterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseMonsterCharacter::UpdateDeath(bool bInIsDeath)
{
	Super::UpdateDeath(bInIsDeath);

	if(bInIsDeath)
	{
		TArray<UActorComponent*> SuperJumpComponents = GetComponentsByClass(USuperJumpComponent::StaticClass());
	
		for(UActorComponent* SuperJumpActorComponent : SuperJumpComponents)
		{
			USuperJumpComponent* SuperJumpComponent = Cast<USuperJumpComponent>(SuperJumpActorComponent);
		
			SuperJumpComponent->ClearCallbackOverlapSuperJump();
			SuperJumpComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}		
	}	
}

void ABaseMonsterCharacter::__OverlapSuperJump(AActor* Actor)
{
	//Stun이든 뭐든 여기다가 넣으면 된다.
	if(IsValid(BaseAnimInstance))
	{
		BaseAnimInstance->SetAnimationType(EAnimationType::Stun);
		BaseAnimInstance->SetAnimationDruationTime(EAnimationType::Stun, 3.f);
	}
}
