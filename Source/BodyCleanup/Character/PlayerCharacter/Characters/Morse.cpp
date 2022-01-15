// Fill out your copyright notice in the Description page of Project Settings.


#include "Morse.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../../Animation/PlayerCharacter/PlayerCharacterAnimInstance.h"
#include "../../../Actor/Level/BaseLevelActor.h"
#include "../../../Character/BaseCharacter.h"
#include "../../../Components/InteractiveMovementComponent.h"
#include "Components/PrimitiveComponent.h"

AMorse::AMorse()
{
}

void AMorse::BeginPlay()
{
	Super::BeginPlay();

	TArray<UActorComponent*> Ranges = GetComponentsByTag(UStaticMeshComponent::StaticClass(), TEXT("VaccumRange"));
	
	for (UActorComponent* ActorComponent : Ranges)
	{
		UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(ActorComponent);

		if (IsValid(PrimitiveComponent))
		{
			UE_LOG(LogTemp, Display, TEXT("VaccumRange PrimitiveComponent : <%s>"), *PrimitiveComponent->GetName());
			PrimitiveComponent->OnComponentBeginOverlap.Clear();
			PrimitiveComponent->OnComponentEndOverlap.Clear();

			PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &AMorse::__OnVaccumRangeOverlapBegin);
			PrimitiveComponent->OnComponentEndOverlap.AddDynamic(this, &AMorse::__OnVaccumRangeOverlapEnd);
		}
	}

	TArray<UActorComponent*> VaccumCollisions = GetComponentsByTag(UPrimitiveComponent::StaticClass(), TEXT("VaccumCollision"));

	if (VaccumCollisions.Num() > 0)
	{
		VaccumPrimitiveComponent = Cast<UPrimitiveComponent>(VaccumCollisions[0]);
		VaccumPrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &AMorse::__OnVaccumOverlapBegin);
	}
}

void AMorse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(BaseController))
	{
		if (BaseController->IsA(APlayerController::StaticClass()))
		{
			FHitResult Hit;
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursor(ECC_WorldStatic, false, Hit);

			if (Hit.bBlockingHit)
			{
				if (Hit.Actor != this)
				{
					//Look Mouse
					//UE_LOG(LogTemp, Display, TEXT("HitActor : <%s>"), *Hit.Actor->GetName());

					FRotator tempRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Hit.ImpactPoint);
					tempRot.Pitch = 0;
					tempRot.Roll = 0;
					SetActorRotation(tempRot);
				}
			}
		}
	}

	if (IsValid(PlayerCharacterAnimInstance))
	{
		EAnimationType AnimationType = PlayerCharacterAnimInstance->GetAnimationType();

		if (EAnimationType::Vacuum == AnimationType)
		{
			if (IsValid(VaccumPrimitiveComponent))
			{
				const FTransform& WorldTransform = VaccumPrimitiveComponent->GetComponentToWorld();

				UInteractiveMovementComponent* InputInteractiveMovementComponent = nullptr;

				for (TSoftObjectPtr<AActor> VaccumActor : VaccumOverlapActors)
				{
					InputInteractiveMovementComponent = nullptr;

					if (VaccumActor->IsA(ABaseLevelActor::StaticClass()))
					{
						InputInteractiveMovementComponent = Cast<ABaseActor>(VaccumActor.Get())->GetInteractiveMovementComponent();
					}
					else if (VaccumActor->IsA(ABaseCharacter::StaticClass()))
					{
						InputInteractiveMovementComponent = Cast<ABaseCharacter>(VaccumActor.Get())->GetInteractiveMovementComponent();
					}

					if (IsValid(InputInteractiveMovementComponent))
					{
						InputInteractiveMovementComponent->SetInteractiveTransform(WorldTransform);

						if (EInteractiveAction::None == InputInteractiveMovementComponent->GetInteractiveAction())
						{
							InputInteractiveMovementComponent->SetInteractiveAction(EInteractiveAction::Absorbing);
						}
					}
				}
			}
		}
	}


	if (PlayerCharacterAnimInstance->GetAnimationType() == EAnimationType::Shot
		&& IsPressedRightMouse())
	{
		FVector ThrowStartPos = GetActorLocation();
		ThrowStartPos += GetActorForwardVector() * CreateShotSpawnActorOffset;

		FHitResult Hit;

		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursor(ECC_WorldStatic, false, Hit);

		FVector startLoc = ThrowStartPos;
		FVector targetLoc = Hit.Location;
		float arcValue = 0.5f;
		FVector outVelocity = FVector::ZeroVector;
		FOccluderVertexArray arr;
		TArray<AActor*> actorArr;
		FVector NullVector;

		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes; // ��Ʈ ������ ������Ʈ ������.
		TEnumAsByte<EObjectTypeQuery> WorldStatic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic);
		TEnumAsByte<EObjectTypeQuery> WorldDynamic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic);
		TEnumAsByte<EObjectTypeQuery> WorldPhysicsBody = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody);
		ObjectTypes.Add(WorldStatic);
		ObjectTypes.Add(WorldDynamic);
		ObjectTypes.Add(WorldPhysicsBody);

		if (UGameplayStatics::SuggestProjectileVelocity_CustomArc(this, outVelocity, startLoc, targetLoc, GetWorld()->GetGravityZ(), arcValue))
		{
			ThrowTargetPos = outVelocity;

			UGameplayStatics::PredictProjectilePath(
				GetWorld(),
				Hit,
				arr,
				NullVector,
				ThrowStartPos,
				ThrowTargetPos,
				true,
				5.f,
				ObjectTypes,
				false,
				actorArr,
				EDrawDebugTrace::ForOneFrame,
				0);
		}

	}
}

void AMorse::MoveForward(float InputAxis)
{
	Super::MoveForward(InputAxis);
}

void AMorse::MoveRight(float InputAxis)
{
	Super::MoveRight(InputAxis);
}

void AMorse::InputPressedMouseLeftClick()
{
	Super::InputPressedMouseLeftClick();

	if (IsValid(PlayerCharacterAnimInstance))
	{
		PlayerCharacterAnimInstance->SetAnimationType(EAnimationType::Vacuum);
	}
}

void AMorse::InputReleasedMouseLeftClick()
{
	Super::InputReleasedMouseLeftClick();

	if (IsValid(PlayerCharacterAnimInstance))
	{
		PlayerCharacterAnimInstance->SetAnimationType(EAnimationType::Idle);
	}
}

void AMorse::InputPressedMouseRightClick()
{
	Super::InputPressedMouseRightClick();

	if (IsValid(PlayerCharacterAnimInstance))
	{
		PlayerCharacterAnimInstance->SetAnimationType(EAnimationType::Shot);
	}

	//if (PlayerCharacterAnimInstance->GetAnimationType() == EAnimationType::Idle)
	//{
	//	//ThrowStartPos = GetActorLocation();
	//	//ThrowStartPos += GetActorForwardVector() * 80;
	//	//
	//	//FHitResult Hit;
	//	//
	//	//FVector startLoc = ThrowStartPos;
	//	//FVector targetLoc = Hit.Location;
	//	//float arcValue = 0.5f;
	//	//FVector outVelocity = FVector::ZeroVector;
	//	//
	//	//if (UGameplayStatics::SuggestProjectileVelocity_CustomArc(this, outVelocity, startLoc, targetLoc, GetWorld()->GetGravityZ(), arcValue))
	//	//{
	//	//	ThrowTargetPos = outVelocity;
	//	//
	//	//	UGameplayStatics::PredictProjectilePath(
	//	//		GetWorld(),
	//	//		Hit,
	//	//		arr,
	//	//		NullVector,
	//	//		ThrowStartPos,
	//	//		ThrowTargetPos,
	//	//		true,
	//	//		5.f,
	//	//		ObjectTypes,
	//	//		false,
	//	//		actorArr,
	//	//		EDrawDebugTrace::ForOneFrame,
	//	//		0);
	//	//}
	//
	//}
	//else
	//{
	//	//PlayerCharacterAnimInstance->SetAnimationType(EAnimationType::Idle);
	//
	//	for (TSoftObjectPtr<AActor> VaccumOverlapActor : VaccumOverlapActors)
	//	{
	//		UInteractiveMovementComponent* VaccumInteractiveMovementComponent = nullptr;
	//
	//		if (VaccumOverlapActor->IsA(ABaseCharacter::StaticClass()))
	//		{
	//			VaccumInteractiveMovementComponent = Cast<ABaseCharacter>(VaccumOverlapActor.Get())->GetInteractiveMovementComponent();
	//		}
	//		else if (VaccumOverlapActor->IsA(ABaseActor::StaticClass()))
	//		{
	//			VaccumInteractiveMovementComponent = Cast<ABaseActor>(VaccumOverlapActor.Get())->GetInteractiveMovementComponent();
	//		}
	//
	//		if (IsValid(VaccumInteractiveMovementComponent))
	//		{
	//			if (EInteractiveAction::Holding == VaccumInteractiveMovementComponent->GetInteractiveAction())
	//			{
	//				//여기서 쏴져야한다.
	//
	//				//VaccumInteractiveMovementComponent->AddForce(GetActorForwardVector() * 1000.f);
	//
	//				VaccumInteractiveMovementComponent->SetInteractiveAction(EInteractiveAction::None);
	//
	//				//VaccumInteractiveMovementComponent->GetOwner()->SetActorLocation(VaccumInteractiveMovementComponent->GetOwner()->GetActorLocation() + GetActorForwardVector() * 1000.f);
	//
	//				VaccumInteractiveMovementComponent->Velocity = GetActorForwardVector() * 1000.f;
	//				VaccumInteractiveMovementComponent->SetUpdatedComponent(VaccumInteractiveMovementComponent->GetOwner()->GetRootComponent());
	//
	//				VaccumInteractiveMovementComponent->UpdateComponentVelocity();
	//
	//				//UE_LOG(LogTemp, Display, TEXT("Velocity : <%.2f, %.2f, %.2f>"), VaccumInteractiveMovementComponent->GetComponentVe.X, VaccumInteractiveMovementComponent->Velocity.Y, VaccumInteractiveMovementComponent->Velocity.Z);
	//			}
	//		}
	//	}
	//}

}

void AMorse::InputReleasedMouseRightClick()
{
	Super::InputReleasedMouseRightClick();

	if (IsValid(PlayerCharacterAnimInstance))
	{
		if (EAnimationType::Shot == PlayerCharacterAnimInstance->GetAnimationType())
		{
			AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(ShotSpawnActor, FTransform(GetActorForwardVector().Rotation(), GetActorLocation() + GetActorForwardVector() * CreateShotSpawnActorOffset));

			if (!SpawnActor) return;

			UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(SpawnActor->GetComponentByClass(UStaticMeshComponent::StaticClass()));

			if (IsValid(StaticMeshComponent))
			{
				StaticMeshComponent->SetSimulatePhysics(true);

				StaticMeshComponent->SetPhysicsLinearVelocity(ThrowTargetPos);
			}
		}

		PlayerCharacterAnimInstance->SetAnimationType(EAnimationType::Idle);
	}

}

void AMorse::__OnVaccumRangeOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (false == VaccumOverlapActors.Contains(OtherActor))
	{
		if (OtherActor->IsA(ABaseActor::StaticClass()))
		{
			ABaseActor* BaseActor = Cast<ABaseActor>(OtherActor);

			if (IsValid(BaseActor))
			{
				if (BaseActor->IsInteractiveActor())
				{
					UE_LOG(LogTemp, Display, TEXT("BeginOverlap <%s> : <%s>"), *OverlappedComp->GetName(), *OtherActor->GetName());
					VaccumOverlapActors.Add(OtherActor);
				}
			}
		}
		else if (OtherActor->IsA(ABaseCharacter::StaticClass()))
		{
			ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(OtherActor);

			if (IsValid(BaseCharacter))
			{
				if (BaseCharacter->IsInteractiveCharacter())
				{
					UE_LOG(LogTemp, Display, TEXT("BeginOverlap <%s> : <%s>"), *OverlappedComp->GetName(), *OtherActor->GetName());
					VaccumOverlapActors.Add(OtherActor);
				}
			}
		}
	}
}

void AMorse::__OnVaccumRangeOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (VaccumOverlapActors.Contains(OtherActor))
	{
		VaccumOverlapActors.Remove(OtherActor);

		//UE_LOG(LogTemp, Display, TEXT("EndOverlap <%s> : <%s>"), *OverlappedComp->GetName(), *OtherActor->GetName());

		UInteractiveMovementComponent* InputInteractiveMovementComponent = nullptr;

		if (OtherActor->IsA(ABaseLevelActor::StaticClass()))
		{
			InputInteractiveMovementComponent = Cast<ABaseActor>(OtherActor)->GetInteractiveMovementComponent();
		}
		else if (OtherActor->IsA(ABaseCharacter::StaticClass()))
		{
			InputInteractiveMovementComponent = Cast<ABaseCharacter>(OtherActor)->GetInteractiveMovementComponent();
		}

		if (IsValid(InputInteractiveMovementComponent))
		{
			if (EInteractiveAction::None != InputInteractiveMovementComponent->GetInteractiveAction())
			{
				InputInteractiveMovementComponent->SetInteractiveAction(EInteractiveAction::None);
			}
		}
	}	
}

void AMorse::__OnVaccumOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ABaseActor::StaticClass()))
	{
		ABaseActor* BaseActor = Cast<ABaseActor>(OtherActor);

		if (IsValid(BaseActor))
		{
			if (BaseActor->IsInteractiveActor())
			{
				UInteractiveMovementComponent* InputInteractiveMovementComponent = BaseActor->GetInteractiveMovementComponent();

				if (EInteractiveAction::Absorbing == InputInteractiveMovementComponent->GetInteractiveAction())
				{
					if (EInteractiveType::Junk == InputInteractiveMovementComponent->GetInteractiveType())
					{
						//해당 Actor는 소멸되어야한다.
						VaccumOverlapActors.Remove(BaseActor);
						BaseActor->Destroy();
					}
					else if (EInteractiveType::Rigid == InputInteractiveMovementComponent->GetInteractiveType())
					{
						InputInteractiveMovementComponent->SetInteractiveAction(EInteractiveAction::Holding);
					}
				}
			}
		}
	}
	//else if (OtherActor->IsA(ABaseCharacter::StaticClass()))
	//{
	//	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(OtherActor);
	//
	//	if (IsValid(BaseCharacter))
	//	{
	//		if (BaseCharacter->IsInteractiveCharacter())
	//		{
	//			UE_LOG(LogTemp, Display, TEXT("BeginOverlap <%s> : <%s>"), *OverlappedComp->GetName(), *OtherActor->GetName());
	//			VaccumOverlapActors.Add(OtherActor);
	//		}
	//	}
	//}
}
