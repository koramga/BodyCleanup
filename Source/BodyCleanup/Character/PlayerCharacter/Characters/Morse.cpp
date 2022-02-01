﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Morse.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../../Animation/PlayerCharacter/PlayerCharacterAnimInstance.h"
#include "../../../Actor/Level/BaseLevelActor.h"
#include "../../../Character/BaseCharacter.h"
#include "Components/PrimitiveComponent.h"
#include "../../../Components/Utility/ComponentFunctionLibrary.h"
#include "../../../Components/Character/VacuumEntranceComponent.h"
#include "../../../Animation/PlayerCharacter/Morse/MorseAnimInstance.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "../../../Game/GameMode/BaseGameModeBase.h"
#include "LevelDesignerTools/Utility/LevelSupportFunctionLibrary.h"
#include "../../../Components/Interactive/Classes/InteractiveSuckingComponent.h"
#include "../../../UI/Viewer/JunkValueViewerUserWidget.h"
#include "Components/WidgetComponent.h"

AMorse::AMorse()
{
	JunkValue = 0;
	
	JunkValueViewerWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("JunkValueViewer");
	JunkValueViewerWidgetComponent->SetupAttachment(GetMesh());
	JunkValueViewerWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
}

void AMorse::BeginPlay()
{
	Super::BeginPlay();

	MorseAnimInstance = Cast<UMorseAnimInstance>(PlayerCharacterAnimInstance);

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

	HeldObjectSlotComponent = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("HeldObjectSlot")));
	GrabConstraintComponent = Cast<UPhysicsConstraintComponent>(GetDefaultSubobjectByName(TEXT("GrabConstraint")));
	VacuumEntranceComponent = Cast<UVacuumEntranceComponent>(GetComponentByClass(UVacuumEntranceComponent::StaticClass()));

	if (VacuumEntranceComponent.IsValid())
	{
		VacuumEntranceComponent->SetHeldObjectSlot(HeldObjectSlotComponent);
		VacuumEntranceComponent->SetGrabConstraintComponent(GrabConstraintComponent);
		VacuumEntranceComponent->OnComponentBeginOverlap.AddDynamic(this, &AMorse::__OnVaccumOverlapBegin);
	}
	
	SetTextToSpeechBubble(TEXT("가나다라마바사\n아자차카타파하"));
	SetHiddenInGameSpeechBubble(true);

	SetJunkValue(JunkValue);
}

void AMorse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//마우스의 움직임을 감시하여 캐릭터가 회전할 수 있도록 한다.
	
	if (IsValid(PlayerCharacterAnimInstance))
	{
		if (EAnimationType::Wait != PlayerCharacterAnimInstance->GetAnimationType())
		{
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

							if (ActorRotationInterpValue <= 0.f)
							{
								SetActorRotation(tempRot);
							}
							else
							{
								FRotator ActorRotator = GetActorRotation();
								ActorRotator.Pitch = 0.f;
								ActorRotator.Roll = 0.f;

								FRotator Rotator = FMath::RInterpTo(ActorRotator, tempRot, DeltaTime, ActorRotationInterpValue);

								SetActorRotation(Rotator);
							}
						}
					}
				}
			}
		}

		__UpdateOverlapInteractigeSuckingComponent(DeltaTime);
	}
}

void AMorse::InputMoveForward(float InputAxis)
{
	if(MorseAnimInstance.IsValid())
	{
		if(MorseAnimInstance->IsShot())
		{
			return;
		}
	}
	
	Super::InputMoveForward(InputAxis);
}

void AMorse::InputMoveRight(float InputAxis)
{
	if(MorseAnimInstance.IsValid())
	{
		if(MorseAnimInstance->IsShot())
		{
			return;
		}
	}
	
	Super::InputMoveRight(InputAxis);
}

void AMorse::InputMouseWheel(float InputAxis)
{
	Super::InputMouseWheel(InputAxis);

	if (InputAxis != 0.f)
	{
		//ArcValue를 수정하여 사용자가 원하는 방향에 Arc값을 지정할 수 있도록 한다.
		if (__IsArcShooting())
		{
			ArcShootingArcValue -= (InputAxis / 50.f);

			ArcShootingArcValue = FMath::Clamp(ArcShootingArcValue, MinArcShootingArcRange, MaxArcShootingArcRange);
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
		VacuumEntranceComponent->SetHoldingActor(nullptr);
		VacuumEntranceComponent->SetSucking(false);
	}
}

void AMorse::InputPressedMouseRightClick()
{
	Super::InputPressedMouseRightClick();

	if (IsValid(PlayerCharacterAnimInstance))
	{
		if (PlayerCharacterAnimInstance->GetAnimationType() == EAnimationType::Idle)
		{
			if(JunkValue >= 4)
			{
				PlayerCharacterAnimInstance->SetAnimationType(EAnimationType::Shot);				
			}			
		}
		else if (PlayerCharacterAnimInstance->GetAnimationType() == EAnimationType::Vacuum)
		{
			//Holding된 Actor가 존재한다면 쏜다!
			if (VacuumEntranceComponent->HasHoldingActor())
			{
				TSoftObjectPtr<AActor> HoldingActor = VacuumEntranceComponent->GetHoldingActor();

				if(HoldingActor.IsValid())
				{
					TSoftObjectPtr<UInteractiveSuckingComponent> InteractiveSuckingComponent = UComponentFunctionLibrary::FindInteractiveSuckingComponent(HoldingActor.Get());

					if(InteractiveSuckingComponent.IsValid())
					{
						if(__SetHoldShooting(InteractiveSuckingComponent.Get()))
						{
							VacuumEntranceComponent->SetHoldingActor(nullptr);
							VacuumEntranceComponent->SetSucking(false);

							if (MorseAnimInstance.IsValid())
							{
								MorseAnimInstance->SetShot();
							}							
						}
					}					
				}
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
		if (bIsCanArcShooting
			&& EAnimationType::Shot == PlayerCharacterAnimInstance->GetAnimationType())
		{
			AddJunkValue(-4);
			
			AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(ArcShootingSpawnActor, FTransform(GetActorForwardVector().Rotation(), GetActorLocation() + GetActorForwardVector() * CreateArcShootingSpawnActorOffset));

			if (!SpawnActor)
			{
				return;
			}

			ABaseGameModeBase* GameModeBase = Cast<ABaseGameModeBase>(GetWorld()->GetAuthGameMode());

			if (IsValid(GameModeBase))
			{
				GameModeBase->SetupTriggerAfterSpawn(SpawnActor);
			}

			if (MorseAnimInstance.IsValid())
			{
				MorseAnimInstance->SetShot();
			}

			TArray<TSoftObjectPtr<UPrimitiveComponent>> PrimitiveComponents;
			
			if(ArcShootingSpawnPhysicsComponents.Names.Num() == 0)
			{
				ULevelSupportFunctionLibrary::FindPrimitiveComponets(PrimitiveComponents, SpawnActor);				
			}
			else
			{
				if(ArcShootingSpawnPhysicsComponents.bIsTag)
				{
					ULevelSupportFunctionLibrary::FindPrimitiveComponentsByTags(PrimitiveComponents, SpawnActor, ArcShootingSpawnPhysicsComponents.Names);
				}
				else
				{
					ULevelSupportFunctionLibrary::FindPrimitiveComponentsByNames(PrimitiveComponents, SpawnActor, ArcShootingSpawnPhysicsComponents.Names);
				}
			}		

			for (const TSoftObjectPtr<UPrimitiveComponent>& PrimitiveComponent : PrimitiveComponents)
			{
				PrimitiveComponent->SetSimulatePhysics(true);
				PrimitiveComponent->SetPhysicsLinearVelocity(ArcShootingVelocity);
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
		VacuumEntranceComponent->SetSucking(true);
		
		TSet<AActor*> OverlappingActors;

		VacuumEntranceComponent->GetOverlappingActors(OverlappingActors);

		OverlappingActors.Remove(this);

		if (OverlappingActors.Num() > 0)
		{
			for(AActor* OverlapActor : OverlappingActors)
			{
				TSoftObjectPtr<UInteractiveSuckingComponent> InteractiveSuckingComponent = UComponentFunctionLibrary::FindInteractiveSuckingComponent(OverlapActor);

				if(InteractiveSuckingComponent.IsValid())
				{
					if (InteractiveSuckingComponent->IsJunk())
					{
						JunkValue += InteractiveSuckingComponent->GetJunkValue();
						OverlapActor->Destroy();
					}
					else
					{
						if (__SetHolding(InteractiveSuckingComponent.Get()))
						{
							break;
						}
					}
				}
			}
		}		
	}
	else
	{
		if (VacuumEntranceComponent.IsValid())
		{
			if (VacuumEntranceComponent->IsSucking())
			{
				VacuumEntranceComponent->SetSucking(false);
			}
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

bool AMorse::__IsArcShooting() const
{
	if (PlayerCharacterAnimInstance->GetAnimationType() == EAnimationType::Shot
		&& IsPressedRightMouse())
	{
		return true;
	}

	return false;
}

void AMorse::__UpdateOverlapInteractigeSuckingComponent(float DeltaTime)
{
	//Shooting은 PredictProjectilePath를 이용해서 그림을 그려야하므로, Tick에 들어가야만 한다.
	if (__IsArcShooting())
	{
		FVector ArcShootingStartLocation = GetActorLocation();
		ArcShootingStartLocation += GetActorForwardVector() * CreateArcShootingSpawnActorOffset;

		FHitResult Hit;

		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		PlayerController->GetHitResultUnderCursor(ECC_WorldStatic, false, Hit);
		FVector ArcShootingEndLocation = Hit.Location;

		float Distance = FVector::Distance(ArcShootingEndLocation, ArcShootingStartLocation);

		if (Distance < MinArcShootingRange)
		{
			bIsCanArcShooting = false;
			return;
		}
		else if (Distance > MaxArcShootingRange)
		{
			
			//최적의 거리를 계산해야한다.
			//bIsCanArcShooting = false;
			//return;

			ArcShootingEndLocation = __ProcessMaxDistnace(ArcShootingStartLocation, ArcShootingEndLocation);
			
			/*
			ArcShootingEndLocation = ArcShootingStartLocation + GetActorForwardVector() * MaxArcShootingRange;

			FHitResult HitResult;
			
			GetWorld()->LineTraceSingleByChannel(HitResult, ArcShootingEndLocation + FVector(0.f, 0.f, 10000.f), ArcShootingEndLocation - FVector(0.f, 0.f, 20000.f)
				, ECC_WorldStatic);

			if(IsValid(Hit.GetActor()))
			{
				Distance = FVector::Distance(ArcShootingStartLocation, Hit.ImpactPoint);

				if(Distance < MaxArcShootingRange)
				{
					
				}
				else if(Distance > MaxArcShootingRange)
				{
					
				}
			}
			*/
		}

		if(FMath::Abs(ArcShootingEndLocation.Z - ArcShootingStartLocation.Z) >= MaxArcShootingZ)
		{
			if(ArcShootingEndLocation.Z > ArcShootingStartLocation.Z)
			{
				ArcShootingEndLocation.Z = ArcShootingStartLocation.Z + MaxArcShootingZ;
			}
			else
			{
				ArcShootingEndLocation.Z = ArcShootingStartLocation.Z - MaxArcShootingZ;
			}
		}

		bIsCanArcShooting = true;
		Distance = FVector::Distance(ArcShootingEndLocation, ArcShootingStartLocation);

		FVector startLoc = ArcShootingStartLocation;
		FVector targetLoc = ArcShootingEndLocation;
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

		if (UGameplayStatics::SuggestProjectileVelocity_CustomArc(this, outVelocity, startLoc, targetLoc, GetWorld()->GetGravityZ(), ArcShootingArcValue))
		{
			ArcShootingVelocity = outVelocity;

			UGameplayStatics::PredictProjectilePath(
				GetWorld(),
				Hit,
				arr,
				NullVector,
				ArcShootingStartLocation,
				ArcShootingVelocity,
				true,
				5.f,
				ObjectTypes,
				false,
				actorArr,
				EDrawDebugTrace::ForOneFrame,
				0);
		}
	}
	else
	{
		if (VacuumEntranceComponent->IsSucking())
		{
			//모두 Sucking상태여야 합니다.

			for (UInteractiveSuckingComponent* InteractiveSuckingComponent : OverlapInteractiveSuckingComponents)
			{
				InteractiveSuckingComponent->SetSucking(VacuumEntranceComponent.Get());
			}
		}
		else
		{
			for (UInteractiveSuckingComponent* InteractiveSuckingComponent : OverlapInteractiveSuckingComponents)
			{
				EInteractiveSuckingType InteractiveSuckingType = InteractiveSuckingComponent->GetInteractiveSuckingType();

				if (EInteractiveSuckingType::Holding == InteractiveSuckingType)
				{

				}
				else if (EInteractiveSuckingType::None != InteractiveSuckingType)
				{
					InteractiveSuckingComponent->SetNone(VacuumEntranceComponent.Get());
				}
			}
		}
	}
}

FVector AMorse::__ProcessMaxDistnace(const FVector& StartArcShootingLocation, const FVector& EndArcShootingLocation)
{
	float Distance = FVector::Distance(StartArcShootingLocation, EndArcShootingLocation);

	if(Distance < 1.f)
	{
		return EndArcShootingLocation;
	}
	
	//Radix를 구한다.
	int Radix = 1;

	while(Radix < Distance) Radix *= 10;
	
	Radix /= 10;

	//원하는 Radix의 값이 나왔다.

	//처음은 무조건 음수이다. (값이 크기 때문에)
	int32 Sign = -1;
	float DistanceOffset = Distance;
	FVector NewEndArcShootingLocation = EndArcShootingLocation;

	for(; Radix > 1; Radix /= 10)
	{
		int RadixOffset = 0;
		
		for(; RadixOffset < 10; ++RadixOffset)
		{
			FVector LineTraceStandardLocation = StartArcShootingLocation + GetActorForwardVector() * (DistanceOffset + RadixOffset * Radix * Sign);
			
			FHitResult HitResult;
			
			GetWorld()->LineTraceSingleByChannel(HitResult,  LineTraceStandardLocation + FVector(0.f, 0.f, 10000.f), LineTraceStandardLocation - FVector(0.f, 0.f, 20000.f)
				, ECC_WorldStatic);

			if(IsValid(HitResult.GetActor()))
			{
				NewEndArcShootingLocation = HitResult.ImpactPoint;
				float NewDistance = FVector::Distance(StartArcShootingLocation, NewEndArcShootingLocation);

				if(Sign < 0)
				{
					if(NewDistance <= MaxArcShootingRange)
					{
						break;
					}
				}
				else
				{
					if(NewDistance >= MaxArcShootingRange)
					{
						break;
					}
				}				
			}			
		}
		
		DistanceOffset = DistanceOffset + RadixOffset * Radix * Sign;
		Sign *= -1;
	}

	return NewEndArcShootingLocation;
}

bool AMorse::__SetHolding(UInteractiveSuckingComponent* InteractiveSuckingComponent)
{
	if(false == VacuumEntranceComponent->HasHoldingActor())
	{
		if(InteractiveSuckingComponent->SetHolding(VacuumEntranceComponent.Get()))
		{
			VacuumEntranceComponent->SetHoldingActor(InteractiveSuckingComponent->GetOwner());

			return true;
		}		
	}

	return false;
}

void AMorse::__SetSucking(UInteractiveSuckingComponent* InteractiveSuckingComponent)
{
	if(false == VacuumEntranceComponent->HasHoldingActor())
	{
		InteractiveSuckingComponent->SetSucking(VacuumEntranceComponent.Get());
	}
}

void AMorse::SetJunkValue(int32 InJunkValue)
{
	JunkValue = InJunkValue;

	if(IsValid(JunkValueViewerWidgetComponent))
	{
		UJunkValueViewerUserWidget* JunkValueViewerUserWidget = Cast<UJunkValueViewerUserWidget>(JunkValueViewerWidgetComponent->GetWidget());

		if(IsValid(JunkValueViewerUserWidget))
		{
			JunkValueViewerUserWidget->SetJunkValue(JunkValue);
		}
	}	
}

void AMorse::AddJunkValue(int32 DeltaJunkValue)
{
	SetJunkValue(JunkValue + DeltaJunkValue);
}

int32 AMorse::GetJunkValue() const
{
	return JunkValue;
}

bool AMorse::__SetHoldShooting(UInteractiveSuckingComponent* InteractiveSuckingComponent)
{
	if(InteractiveSuckingComponent->SetHoldShooting(VacuumEntranceComponent.Get()))
	{
		return true;
	}

	return false;
}

void AMorse::__OnVaccumRangeOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
	{
		TSoftObjectPtr<UInteractiveSuckingComponent> SuckingComponent = UComponentFunctionLibrary::FindInteractiveSuckingComponent(OtherActor);

		if(SuckingComponent.IsValid())
		{
			if(false == OverlapInteractiveSuckingComponents.Contains(SuckingComponent.Get()))
			{
				OverlapInteractiveSuckingComponents.Add(SuckingComponent.Get());
			}
		}
	}
}

void AMorse::__OnVaccumRangeOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsValid(OtherActor))
	{
		TSoftObjectPtr<UInteractiveSuckingComponent> SuckingComponent = UComponentFunctionLibrary::FindInteractiveSuckingComponent(OtherActor);

		if(SuckingComponent.IsValid())
		{
			if(OverlapInteractiveSuckingComponents.Remove(SuckingComponent.Get()) > 0)
			{
				SuckingComponent->SetNone(VacuumEntranceComponent.Get());
			}
		}
	}
}

void AMorse::__OnVaccumOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ABaseActor::StaticClass()))
	{
		TSoftObjectPtr<UInteractiveSuckingComponent> InteractiveSuckingComponent = UComponentFunctionLibrary::FindInteractiveSuckingComponent(OtherActor);

		if(InteractiveSuckingComponent.IsValid())
		{
			if(__CanVacuuming())
			{
				if (InteractiveSuckingComponent->IsJunk())
				{
					AddJunkValue(InteractiveSuckingComponent->GetJunkValue());
					OtherActor->Destroy();
				}
				else
				{
					if (false == VacuumEntranceComponent->HasHoldingActor())
					{
						__SetHolding(InteractiveSuckingComponent.Get());
					}
				}
			}
		}
	}
}
