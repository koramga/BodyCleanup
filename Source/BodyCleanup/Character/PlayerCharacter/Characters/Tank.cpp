// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Components/CapsuleComponent.h"
#include "../../../Animation/PlayerCharacter/Tank/TankAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

ATank::ATank()
{

}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(0.3f, 0.3f, 0.3f));
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(FollowCharacter))
	{
		FVector GoalLocation = FollowCharacter->GetActorLocation();
		GoalLocation.Z += 150.f;

		FVector NextLocation = UKismetMathLibrary::VLerp(GetActorLocation(), GoalLocation, 0.05f);

		SetActorLocation(NextLocation);
		SetActorRotation(FollowCharacter->GetActorRotation());
	}
	else
	{

	}
}

void ATank::SetFlyMode(ACharacter* InputFollowCharacter)
{
	if (IsValid(InputFollowCharacter))
	{
		SetEnableCapsuleCollision(false);
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	}
	else
	{
		SetEnableCapsuleCollision(true);
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		GetCharacterMovement()->Velocity = GetActorForwardVector() * GetCharacterMovement()->MaxWalkSpeed * 2;
	}

	if (IsValid(BaseAnimInstance))
	{
		BaseAnimInstance->SetMovementMode(GetCharacterMovement()->MovementMode);
	}

	FollowCharacter = InputFollowCharacter;
}

bool ATank::IsFlyMode() const
{
	if (IsValid(FollowCharacter))
	{
		return true;
	}

	return false;
}

void ATank::MoveForward(float InputAxis)
{
	Super::MoveForward(InputAxis);
}

void ATank::MoveRight(float InputAxis)
{
	Super::MoveRight(InputAxis);
}

void ATank::InputPressedMouseLeftClick()
{
	Super::InputPressedMouseLeftClick();
}

void ATank::InputReleasedMouseLeftClick()
{
	Super::InputReleasedMouseLeftClick();
}
