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

	if (IsValid(PlayerCharacterAnimInstance))
	{
		if (EAnimationType::Idle == PlayerCharacterAnimInstance->GetAnimationType())
		{
			if (FollowCharacter.IsValid())
			{
				FVector GoalLocation = FollowCharacter->GetActorLocation();
				GoalLocation.Z += 150.f;

				FVector NextLocation = UKismetMathLibrary::VLerp(GetActorLocation(), GoalLocation, 0.05f);

				SetActorLocation(NextLocation);
				SetActorRotation(FollowCharacter->GetActorRotation());

				//float Distance = FVector::Distance(GetActorLocation(), GoalLocation);
				//
				//UE_LOG(LogTemp, Display, TEXT("%.2f"), Distance);
				//
				//if (Distance <= 80.f)
				//{
				//	FVector NextLocation = UKismetMathLibrary::VLerp(GetActorLocation(), GoalLocation, 0.05f);
				//
				//	SetActorLocation(NextLocation);
				//	SetActorRotation(FollowCharacter->GetActorRotation());
				//}
				//else
				//{
				//	FVector Direction = GoalLocation - GetActorLocation();
				//	Direction.Normalize();
				//
				//	SetActorLocation(GetActorLocation() + Direction * 50.f * DeltaTime);
				//	SetActorRotation(FollowCharacter->GetActorRotation());
				//}
			}
		}
	}
}

void ATank::SetFlyMode(TSoftObjectPtr<ACharacter> InputFollowCharacter)
{
	if (InputFollowCharacter.IsValid())
	{
		SetActorEnableCollision(false);
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	}
	else
	{
		SetActorEnableCollision(true);
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
	if (FollowCharacter.IsValid())
	{
		return true;
	}

	return false;
}

void ATank::InputMoveForward(float InputAxis)
{
	Super::InputMoveForward(InputAxis);
}

void ATank::InputMoveRight(float InputAxis)
{
	Super::InputMoveRight(InputAxis);
}

void ATank::InputPressedMouseLeftClick()
{
	Super::InputPressedMouseLeftClick();
}

void ATank::InputReleasedMouseLeftClick()
{
	Super::InputReleasedMouseLeftClick();
}
