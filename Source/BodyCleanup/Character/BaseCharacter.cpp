// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Animation/BaseAnimInstance.h"
#include "../Components/InteractiveMovementComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	BaseAnimInstance = Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance());

	BodyCollisionProfileName = GetCapsuleComponent()->GetCollisionProfileName();

	InteractiveMovementComponent = Cast<UInteractiveMovementComponent>(GetComponentByClass(UInteractiveMovementComponent::StaticClass()));
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	BaseController = NewController;
}

void ABaseCharacter::UnPossessed()
{
	Super::UnPossessed();

	BaseController = nullptr;
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UCharacterMovementComponent* Movement = GetCharacterMovement();
	FVector Forward = GetActorForwardVector();
	FVector Velocity = Movement->Velocity;
	float Speed = Velocity.Size();
	float Angle = 0.f;

	if (Movement->IsMovingOnGround())
	{
		if (Speed > 0)
		{
			//https://amored8701.tistory.com/132

			//if (IsLockOn())
			//{
			//	FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), LockOnBaseCharacter->GetActorLocation());
			//
			//	SetActorRotation(Rotator.Quaternion());
			//
			//	vForward = Rotator.RotateVector(FVector::ForwardVector);
			//}

			Forward.Z = 0.f;
			Velocity.Z = 0.f;

			Forward.Normalize();
			Velocity.Normalize();

			float fDot = FVector::DotProduct(Forward, Velocity);
			float fAcosAngle = FMath::Acos(fDot);
			float fAngle = FMath::RadiansToDegrees(fAcosAngle);

			FVector vCross = FVector::CrossProduct(Forward, Velocity);

			if (vCross.Z < 0)
			{
				//fAngle *= -1.f;
				fAngle = 360 - fAngle;
			}

			//Angle = fAngle + QUARTER_VIEW_ANGLE;

			//UE_LOG(LogTemp, Display, TEXT("Angle : %.2f"), fAngle);
		}

		if (IsValid(BaseAnimInstance))
		{
			float Ratio = 0.5f;

			//if (EMoveType::Run == MoveType)
			//{
			//	Ratio = 1.f;
			//}
			//else if (EMoveType::Sprint == MoveType)
			//{
			//	Ratio = 1.5f;
			//}

			if (IsValid(BaseAnimInstance))
			{
				BaseAnimInstance->SetMoveBlendSpeed(Speed / GetCharacterMovement()->GetMaxSpeed() * Ratio);
				BaseAnimInstance->SetMoveBlendAngle(Angle);
			}
		}
	}

	if (IsValid(BaseAnimInstance))
	{
		BaseAnimInstance->SetMovementMode(GetCharacterMovement()->MovementMode);
	}
}

void ABaseCharacter::SetEnableCapsuleCollision(bool bIsEnable)
{
	if (false == bIsEnable)
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	}
	else
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
		GetCapsuleComponent()->SetCollisionProfileName(BodyCollisionProfileName);
	}
}

bool ABaseCharacter::IsInteractiveCharacter() const
{
	if (IsValid(InteractiveMovementComponent))
	{
		return true;
	}

	return false;
}


void ABaseCharacter::SetInteractiveActivate(bool bActivate)
{
	if (IsValid(InteractiveMovementComponent))
	{
		if (bActivate)
		{
			InteractiveMovementComponent->Activate();
		}
		else
		{
			InteractiveMovementComponent->Deactivate();
		}
	}
}

void ABaseCharacter::SetInteractiveAction(EInteractiveAction InputInteractiveAction)
{
	if (IsValid(InteractiveMovementComponent))
	{
		InteractiveMovementComponent->SetInteractiveAction(InputInteractiveAction);
	}
}

UInteractiveMovementComponent* ABaseCharacter::GetInteractiveMovementComponent() const
{
	return InteractiveMovementComponent;
}
