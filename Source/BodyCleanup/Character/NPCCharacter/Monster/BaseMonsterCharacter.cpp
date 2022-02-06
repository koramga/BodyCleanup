// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMonsterCharacter.h"
#include "../../../Components/Scene/SuperJumpComponent.h"
#include "BodyCleanup/Animation/BaseAnimInstance.h"

ABaseMonsterCharacter::ABaseMonsterCharacter()
{
	SuperJumpComponent = CreateDefaultSubobject<USuperJumpComponent>(TEXT("SuperJumpComponent"));

	//Arm을 Root에 붙여준다.
	SuperJumpComponent->SetupAttachment(GetMesh());
}

void ABaseMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(SuperJumpComponent))
	{
		SuperJumpComponent->SetCallbackOverlapSuperJump(this, &ABaseMonsterCharacter::__OverlapSuperJump);
	}	
}

void ABaseMonsterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseMonsterCharacter::__OverlapSuperJump(AActor* Actor)
{
	//Stun이든 뭐든 여기다가 넣으면 된다.
	if(IsValid(BaseAnimInstance))
	{
		BaseAnimInstance->SetAnimationType(EAnimationType::Stun);
		BaseAnimInstance->SetAnimationDruationTime(3.f);
	}
}