// Fill out your copyright notice in the Description page of Project Settings.


#include "Morse.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../../Animation/PlayerCharacter/PlayerCharacterAnimInstance.h"
#include "../../../Actor/Level/BaseLevelActor.h"
#include "../../../Character/BaseCharacter.h"
#include "../../../Components/Interactive/InteractiveObjectComponent.h"
#include "Components/PrimitiveComponent.h"
#include "../../../Utilities/FunctionLibraries/FindFunctionLibrary.h"
#include "../../../Components/Interfaces/InteractiveInterface.h"

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

	if (__IsShooting())
	{
		FVector ThrowStartPos = GetActorLocation();
		ThrowStartPos += GetActorForwardVector() * CreateShotSpawnActorOffset;
	
		FHitResult Hit;
	
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursor(ECC_WorldStatic, false, Hit);
	
		FVector startLoc = ThrowStartPos;
		FVector targetLoc = Hit.Location;
		FVector outVelocity = FVector::ZeroVector;
		FOccluderVertexArray arr;
		TArray<AActor*> actorArr;
		FVector NullVector;
	
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		TEnumAsByte<EObjectTypeQuery> WorldStatic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic);
		TEnumAsByte<EObjectTypeQuery> WorldDynamic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic);
		TEnumAsByte<EObjectTypeQuery> WorldPhysicsBody = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody);
		ObjectTypes.Add(WorldStatic);
		ObjectTypes.Add(WorldDynamic);
		ObjectTypes.Add(WorldPhysicsBody);
	
		if (UGameplayStatics::SuggestProjectileVelocity_CustomArc(this, outVelocity, startLoc, targetLoc, GetWorld()->GetGravityZ(), ThrowArcValue))
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

void AMorse::InputMoveForward(float InputAxis)
{
	Super::InputMoveForward(InputAxis);
}

void AMorse::InputMoveRight(float InputAxis)
{
	Super::InputMoveRight(InputAxis);
}

void AMorse::InputMouseWheel(float InputAxis)
{
	Super::InputMouseWheel(InputAxis);

	if (InputAxis != 0.f)
	{
		if (__IsShooting())
		{
			ThrowArcValue -= (InputAxis / 50.f);

			ThrowArcValue = FMath::Clamp(ThrowArcValue, 0.1f, 0.9f);
		}
	}

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
		__SetOverlapVacuumActorsInteractiveAction(EInteractiveAction::None);
	}
}

void AMorse::InputPressedMouseRightClick()
{
	Super::InputPressedMouseRightClick();

	if (IsValid(PlayerCharacterAnimInstance))
	{
		if (PlayerCharacterAnimInstance->GetAnimationType() == EAnimationType::Idle)
		{
			PlayerCharacterAnimInstance->SetAnimationType(EAnimationType::Shot);
		}
		else if (PlayerCharacterAnimInstance->GetAnimationType() == EAnimationType::Vacuum)
		{
			TArray<TSoftObjectPtr<AActor>>	ShootingActors;

			for (const TSoftObjectPtr<AActor>& VaccumOverlapActor : VacuumOverlapActors)
			{
				TArray<TSoftObjectPtr<USceneComponent>> InteractiveComopnents;
				UFindFunctionLibrary::FindInteractiveComponents(InteractiveComopnents, VaccumOverlapActor->GetRootComponent());

				if (InteractiveComopnents.Num() > 0)
				{
					for (TSoftObjectPtr<USceneComponent> InteractiveComponent : InteractiveComopnents)
					{
						IInteractiveInterface* InteractiveInterface = Cast<IInteractiveInterface>(InteractiveComponent.Get());
						InteractiveInterface->SetInteractiveAction(EInteractiveAction::Shooting);
					}
				}

				//VaccumInteractiveMovementComponent->AddForce(GetActorForwardVector() * 1000.f);
				//
				//FVector startLoc = VaccumOverlapActor->GetActorLocation() + GetActorForwardVector();
				//FVector targetLoc = VaccumOverlapActor->GetActorLocation() + GetActorForwardVector() * 2000.f;
				//float arcValue = 0.9f;
				//FVector outVelocity = FVector::ZeroVector;
				//
				//if (UGameplayStatics::SuggestProjectileVelocity_CustomArc(this, outVelocity, startLoc, targetLoc, GetWorld()->GetGravityZ(), arcValue))
				//{
				//
				//	VaccumInteractiveMovementComponent->SetInteractiveAction(EInteractiveAction::Shooting);
				//
				//	UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(VaccumInteractiveMovementComponent->GetOwner()->FindComponentByClass(UStaticMeshComponent::StaticClass()));
				//
				//	StaticMeshComponent->SetPhysicsLinearVelocity(outVelocity);
				//}
				//if (IsValid(VaccumInteractiveMovementComponent))
				//{
				//	if (EInteractiveAction::Holding == VaccumInteractiveMovementComponent->GetInteractiveAction())
				//	{
				//		//여기서 쏴져야한다.
				//
				//	}
				//}
			}

			PlayerCharacterAnimInstance->SetAnimationType(EAnimationType::Idle);
		}
	}
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

void AMorse::UpdateAnimationType(EAnimationType AnimationType, EAnimationType BeforeAnimationType)
{
	if (EAnimationType::Vacuum == AnimationType)
	{
		__SetOverlapVacuumActorsInteractiveAction(EInteractiveAction::Absorbing);
	}

	Super::UpdateAnimationType(AnimationType, BeforeAnimationType);
}

bool AMorse::__IsVacuuming() const
{
	if (IsValid(PlayerCharacterAnimInstance))
	{
		if (IsPressedLeftMouse()
			&& EAnimationType::Vacuum == PlayerCharacterAnimInstance->GetAnimationType())
		{
			return true;
		}
	}

	return false;
}

bool AMorse::__IsShooting() const
{
	if (PlayerCharacterAnimInstance->GetAnimationType() == EAnimationType::Shot
		&& IsPressedRightMouse())
	{
		return true;
	}

	return false;
}

void AMorse::__SetOverlapVacuumActorsInteractiveAction(EInteractiveAction InteractiveAction)
{
	for (TSoftObjectPtr<AActor> VacuumActor : VacuumOverlapActors)
	{
		TArray<TSoftObjectPtr<USceneComponent>> InteractiveComopnents;
		UFindFunctionLibrary::FindInteractiveComponents(InteractiveComopnents, VacuumActor->GetRootComponent());

		if (InteractiveComopnents.Num() > 0)
		{
			for (TSoftObjectPtr<USceneComponent> InteractiveComponent : InteractiveComopnents)
			{
				IInteractiveInterface* InteractiveInterface = Cast<IInteractiveInterface>(InteractiveComponent.Get());
				InteractiveInterface->SetInteractiveAction(InteractiveAction);
			}
		}
	}
}

void AMorse::__OnVaccumRangeOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor)
		&& false == VacuumOverlapActors.Contains(OtherActor))
	{
		TArray<TSoftObjectPtr<USceneComponent>> InteractiveComopnents;
		UFindFunctionLibrary::FindInteractiveComponents(InteractiveComopnents, OtherActor->GetRootComponent());

		if (InteractiveComopnents.Num() > 0)
		{
			for (TSoftObjectPtr<USceneComponent> InteractiveComponent : InteractiveComopnents)
			{
				IInteractiveInterface* InteractiveInterface = Cast<IInteractiveInterface>(InteractiveComponent.Get());
				InteractiveInterface->SetInteractiveComponent(VaccumPrimitiveComponent);

				if (__IsVacuuming())
				{
					InteractiveInterface->SetInteractiveAction(EInteractiveAction::Absorbing);
				}
			}

			VacuumOverlapActors.Add(OtherActor);
		}
	}
}

void AMorse::__OnVaccumRangeOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (VacuumOverlapActors.Contains(OtherActor))
	{
		VacuumOverlapActors.Remove(OtherActor);

		TArray<TSoftObjectPtr<USceneComponent>> InteractiveComopnents;
		UFindFunctionLibrary::FindInteractiveComponents(InteractiveComopnents, OtherActor->GetRootComponent());

		if (InteractiveComopnents.Num() > 0)
		{
			for (TSoftObjectPtr<USceneComponent> InteractiveComponent : InteractiveComopnents)
			{
				IInteractiveInterface* InteractiveInterface = Cast<IInteractiveInterface>(InteractiveComponent.Get());
				InteractiveInterface->SetInteractiveComponent(nullptr);
				InteractiveInterface->SetInteractiveAction(EInteractiveAction::None);
			}
		}
	}	
}

void AMorse::__OnVaccumOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ABaseActor::StaticClass()))
	{
		TArray<TSoftObjectPtr<USceneComponent>> InteractiveComopnents;
		UFindFunctionLibrary::FindInteractiveComponents(InteractiveComopnents, OtherActor->GetRootComponent());

		if (InteractiveComopnents.Num() > 0)
		{
			if (__IsVacuuming())
			{
				for (TSoftObjectPtr<USceneComponent> InteractiveComponent : InteractiveComopnents)
				{
					IInteractiveInterface* InteractiveInterface = Cast<IInteractiveInterface>(InteractiveComponent.Get());
					InteractiveInterface->SetInteractiveAction(EInteractiveAction::Holding);

					if (InteractiveInterface->GetInteractiveAction() == EInteractiveAction::Holding)
					{
						break;
					}
				}
			}
		}
		//ABaseActor* BaseActor = Cast<ABaseActor>(OtherActor);
		//
		//if (IsValid(BaseActor))
		//{
		//	if (BaseActor->IsInteractiveActor())
		//	{
		//		UInteractiveMovementComponent* InputInteractiveMovementComponent = BaseActor->GetInteractiveMovementComponent();
		//
		//		if (EInteractiveAction::Absorbing == InputInteractiveMovementComponent->GetInteractiveAction())
		//		{
		//			if (EInteractiveType::Junk == InputInteractiveMovementComponent->GetInteractiveType())
		//			{
		//				//해당 Actor는 소멸되어야한다.
		//				VaccumOverlapActors.Remove(BaseActor);
		//				BaseActor->Destroy();
		//			}
		//			else if (EInteractiveType::Rigid == InputInteractiveMovementComponent->GetInteractiveType())
		//			{
		//				InputInteractiveMovementComponent->SetInteractiveAction(EInteractiveAction::Holding);
		//			}
		//		}
		//	}
		//}
	}
}
