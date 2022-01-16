// Fill out your copyright notice in the Description page of Project Settings.


#include "Morse.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../../Animation/PlayerCharacter/PlayerCharacterAnimInstance.h"
#include "../../../Actor/Level/BaseLevelActor.h"
#include "../../../Character/BaseCharacter.h"
#include "../../../Components/Interactives/InteractiveObjectComponent.h"
#include "Components/PrimitiveComponent.h"
#include "../../../Utilities/FunctionLibraries/FindFunctionLibrary.h"
#include "../../../Components/Interfaces/InteractiveInterface.h"
#include "../../../Components/Character/VacuumEntranceComponent.h"

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

	VacuumEntranceComponent = Cast<UVacuumEntranceComponent>(GetComponentByClass(UVacuumEntranceComponent::StaticClass()));
	VacuumEntranceComponent->OnComponentBeginOverlap.AddDynamic(this, &AMorse::__OnVaccumOverlapBegin);
}

void AMorse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//마우스의 움직임을 감시하여 캐릭터가 회전할 수 있도록 한다.
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
					FRotator tempRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Hit.ImpactPoint);
					tempRot.Pitch = 0;
					tempRot.Roll = 0;
					SetActorRotation(tempRot);
				}
			}
		}
	}

	//Shooting은 PredictProjectilePath를 이용해서 그림을 그려야하므로, Tick에 들어가야만 한다.
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
		//ArcValue를 수정하여 사용자가 원하는 방향에 Arc값을 지정할 수 있도록 한다.
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

		TSoftObjectPtr<AActor> HoldingActor = nullptr;

		//HoldingActor는 Overlap End를 당해도 InteractiveComponent가 소멸되지 않는다.
		//그러므로 Vacuum의 행위가 종료되면 HoldingActor를 초기화해줘야한다.
		if (VacuumEntranceComponent->HasHoldingActor())
		{
			HoldingActor = VacuumEntranceComponent->GetHoldingActor();

			__SetInteractiveComponent(HoldingActor.Get(), nullptr);

			VacuumEntranceComponent->SetHoldingActor(nullptr);
		}
		
		__SetOverlapVacuumActorsInteractiveAction(EInteractiveAction::None);

		//HoldingActor를 초기화했는데 VacuumTrigger안에 들어가있다면 초기화에서 다시 VacuumEnteranceComponent를 추가해준다.
		if (HoldingActor.IsValid())
		{
			TSet<AActor*> OverlappingActors;
			VacuumEntranceComponent->GetOverlappingActors(OverlappingActors);

			if (nullptr != OverlappingActors.Find(HoldingActor.Get()))
			{
				__SetInteractiveComponent(HoldingActor.Get(), VacuumEntranceComponent);
			}
		}

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
			//Holding된 Actor가 존재한다면 쏜다!
			if (VacuumEntranceComponent->HasHoldingActor())
			{
				TSoftObjectPtr<AActor> HoldingActor = VacuumEntranceComponent->GetHoldingActor();

				__SetInteractiveAction(HoldingActor.Get(), EInteractiveAction::Shooting);
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

			if (!SpawnActor)
			{
				return;
			}

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
	//실제 애니메이션의 시작을 알리는 함수이다.

	if (EAnimationType::Vacuum == AnimationType)
	{
		//VacuumEntranceComponent에 이미 Overlapping되어있는 Actor가 있는지 조사한다.
		//이미 Overlapping된 Actor가 존재한다면 HoldingActor로 변경해주고 나머지들은 None으로 조정한다.
		TSet<AActor*> OverlappingActors;

		VacuumEntranceComponent->GetOverlappingActors(OverlappingActors);

		OverlappingActors.Remove(this);

		if (OverlappingActors.Num() > 0)
		{
			AActor* OverlappingActor = OverlappingActors.Array()[0];

			__SetInteractiveAction(OverlappingActor, EInteractiveAction::Holding);
		}
		else
		{
			//Overlapping된 것이 없다면 진공으로 빨아들이도록 한다.

			__SetOverlapVacuumActorsInteractiveAction(EInteractiveAction::Absorbing);
		}
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

bool AMorse::__CanVacuuming() const
{
	if (__IsVacuuming()
		&& false == VacuumEntranceComponent->HasHoldingActor())
	{
		return true;
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

void AMorse::__SetInteractiveComponent(TSoftObjectPtr<AActor> Actor, TSoftObjectPtr<class UVacuumEntranceComponent> SetInteractiveComponent)
{
	TArray<TSoftObjectPtr<USceneComponent>> InteractiveComopnents;
	UFindFunctionLibrary::FindInteractiveComponents(InteractiveComopnents, Actor->GetRootComponent());

	if (InteractiveComopnents.Num() > 0)
	{
		for (TSoftObjectPtr<USceneComponent> InteractiveComponent : InteractiveComopnents)
		{
			IInteractiveInterface* InteractiveInterface = Cast<IInteractiveInterface>(InteractiveComponent.Get());
			InteractiveInterface->SetInteractiveComponent(SetInteractiveComponent);
		}
	}
}

void AMorse::__SetInteractiveAction(TSoftObjectPtr<AActor> Actor, EInteractiveAction InteractiveAction)
{
	TArray<TSoftObjectPtr<USceneComponent>> InteractiveComopnents;
	UFindFunctionLibrary::FindInteractiveComponents(InteractiveComopnents, Actor->GetRootComponent());

	if (InteractiveComopnents.Num() > 0)
	{
		for (TSoftObjectPtr<USceneComponent> InteractiveComponent : InteractiveComopnents)
		{
			IInteractiveInterface* InteractiveInterface = Cast<IInteractiveInterface>(InteractiveComponent.Get());
			InteractiveInterface->SetInteractiveAction(InteractiveAction);

			if (EInteractiveAction::Holding == InteractiveInterface->GetInteractiveAction())
			{
				//Holding으로 업데이트되었다면 VacuumEntranceComponent에도 Holding된 객체가 있음을 전달한다.
				VacuumEntranceComponent->SetHoldingActor(Actor);
			}
			else if (EInteractiveAction::Shooting == InteractiveInterface->GetInteractiveAction())
			{
				//Shooting즉시 Hodling Actor를 제거한다.
				VacuumEntranceComponent->SetHoldingActor(nullptr);
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
				InteractiveInterface->SetInteractiveComponent(VacuumEntranceComponent);

				if (__CanVacuuming())
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

		if (VacuumEntranceComponent->GetHoldingActor() != OtherActor)
		{
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
}

void AMorse::__OnVaccumOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ABaseActor::StaticClass()))
	{
		TArray<TSoftObjectPtr<USceneComponent>> InteractiveComopnents;
		UFindFunctionLibrary::FindInteractiveComponents(InteractiveComopnents, OtherActor->GetRootComponent());

		if (InteractiveComopnents.Num() > 0)
		{
			if (__CanVacuuming())
			{
				__SetInteractiveAction(OtherActor, EInteractiveAction::Holding);
			}

			if (VacuumEntranceComponent->HasHoldingActor())
			{
				__SetOverlapVacuumActorsInteractiveAction(EInteractiveAction::None);
			}
		}
	}
}
