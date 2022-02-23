// Fill out your copyright notice in the Description page of Project Settings.


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
#include "BodyCleanup/Controller/Player/BasePlayerController.h"
#include "Components/WidgetComponent.h"
#include "DrawDebugHelpers.h"
#include "BodyCleanup/Components/Actor/LevelComponent.h"

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

void AMorse::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if(NewController->IsA(ABasePlayerController::StaticClass()))
	{
		SetKeyboardControlType(EKeyboardControlType::MorseDefault);
	}
}

void AMorse::UnPossessed()
{
	Super::UnPossessed();
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
				if (BaseController->IsA(ABasePlayerController::StaticClass()))
				{					
					ABasePlayerController* BasePlayerController = Cast<ABasePlayerController>(BaseController);

					FHitResult HitResult;
					
					if(BasePlayerController->GetLevelHitResultAtMousePosition(HitResult))
					{
						FRotator tempRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), HitResult.ImpactPoint);
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
		ABasePlayerController* BasePlayerController = Cast<ABasePlayerController>(BaseController);
		
		FHitResult Hit;

		if(BasePlayerController->GetLevelHitResultAtMousePosition(Hit))
		{
			FVector ArcShootingEndLocation = Hit.Location;

			float Distance = FVector::Distance(ArcShootingEndLocation, ArcShootingStartLocation);

			if (Distance < MinArcShootingRange)
			{
				bIsCanArcShooting = false;
				return;
			}
			else if (Distance > MaxArcShootingRange)
			{
				ArcShootingEndLocation = __ProcessMaxDistnace(ArcShootingStartLocation, ArcShootingEndLocation);
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

			TArray<TEnumAsByte<EObjectTypeQuery>> PredictObjectTypes;
			TEnumAsByte<EObjectTypeQuery> WorldStatic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic);
			PredictObjectTypes.Add(WorldStatic);

			if (UGameplayStatics::SuggestProjectileVelocity_CustomArc(this, outVelocity, startLoc, targetLoc, GetWorld()->GetGravityZ(), ArcShootingArcValue))
			{
				ArcShootingVelocity = outVelocity;

				__PredictProjectilePath_ByObjectType(
					GetWorld(),
					Hit,
					arr,
					NullVector,
					ArcShootingStartLocation,
					ArcShootingVelocity,
					true,
					5.f,
					PredictObjectTypes,
					true,
					actorArr,
					EDrawDebugTrace::ForDuration,
					0);

				
				//UGameplayStatics::PredictProjectilePath(
				//	GetWorld(),
				//	Hit,
				//	arr,
				//	NullVector,
				//	ArcShootingStartLocation,
				//	ArcShootingVelocity,
				//	true,
				//	5.f,
				//	PredictObjectTypes,
				//	true,
				//	actorArr,
				//	EDrawDebugTrace::ForDuration,
				//	0);
			}
			
		}
	}
	else
	{
		if (VacuumEntranceComponent->IsSucking())
		{
			//모두 Sucking상태여야 합니다.

			for (auto OverlapTuple : OverlapInteractiveSuckingComponents)
			{
				OverlapTuple.Key->SetSucking(VacuumEntranceComponent.Get());
			}
		}
		else
		{
			for (auto OverlapTuple : OverlapInteractiveSuckingComponents)
			{
				EInteractiveSuckingType InteractiveSuckingType = OverlapTuple.Key->GetInteractiveSuckingType();

				if (EInteractiveSuckingType::Holding == InteractiveSuckingType)
				{

				}
				else if (EInteractiveSuckingType::None != InteractiveSuckingType)
				{
					OverlapTuple.Key->SetNone(VacuumEntranceComponent.Get());
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

bool AMorse::__PredictProjectilePath(const UObject* WorldContextObject, const FPredictProjectilePathParams& PredictParams, FPredictProjectilePathResult& PredictResult)
{
	PredictResult.Reset();
	bool bBlockingHit = false;

	UWorld const* const World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (World && PredictParams.SimFrequency > KINDA_SMALL_NUMBER)
	{
		const float SubstepDeltaTime = 1.f / PredictParams.SimFrequency;
		const float GravityZ = FMath::IsNearlyEqual(PredictParams.OverrideGravityZ, 0.0f) ? World->GetGravityZ() : PredictParams.OverrideGravityZ;
		const float ProjectileRadius = PredictParams.ProjectileRadius;

		FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(PredictProjectilePath), PredictParams.bTraceComplex);
		FCollisionObjectQueryParams ObjQueryParams;
		const bool bTraceWithObjectType = (PredictParams.ObjectTypes.Num() > 0);
		const bool bTracePath = PredictParams.bTraceWithCollision && (PredictParams.bTraceWithChannel || bTraceWithObjectType);
		if (bTracePath)
		{
			QueryParams.AddIgnoredActors(PredictParams.ActorsToIgnore);
			if (bTraceWithObjectType)
			{
				for (auto Iter = PredictParams.ObjectTypes.CreateConstIterator(); Iter; ++Iter)
				{
					const ECollisionChannel& Channel = UCollisionProfile::Get()->ConvertToCollisionChannel(false, *Iter);
					ObjQueryParams.AddObjectTypesToQuery(Channel);
				}
			}
		}

		FVector CurrentVel = PredictParams.LaunchVelocity;
		FVector TraceStart = PredictParams.StartLocation;
		FVector TraceEnd = TraceStart;
		float CurrentTime = 0.f;
		PredictResult.PathData.Reserve(FMath::Min(128, FMath::CeilToInt(PredictParams.MaxSimTime * PredictParams.SimFrequency)));
		PredictResult.AddPoint(TraceStart, CurrentVel, CurrentTime);

		FHitResult ObjectTraceHit(NoInit);
		FHitResult ChannelTraceHit(NoInit);
		ObjectTraceHit.Time = 1.f;
		ChannelTraceHit.Time = 1.f;

		const float MaxSimTime = PredictParams.MaxSimTime;
		while (CurrentTime < MaxSimTime)
		{
			// Limit step to not go further than total time.
			const float PreviousTime = CurrentTime;
			const float ActualStepDeltaTime = FMath::Min(MaxSimTime - CurrentTime, SubstepDeltaTime);
			CurrentTime += ActualStepDeltaTime;

			// Integrate (Velocity Verlet method)
			TraceStart = TraceEnd;
			FVector OldVelocity = CurrentVel;
			CurrentVel = OldVelocity + FVector(0.f, 0.f, GravityZ * ActualStepDeltaTime);
			TraceEnd = TraceStart + (OldVelocity + CurrentVel) * (0.5f * ActualStepDeltaTime);
			PredictResult.LastTraceDestination.Set(TraceEnd, CurrentVel, CurrentTime);

			if (bTracePath)
			{
				bool bObjectHit = false;
				bool bChannelHit = false;
				if (bTraceWithObjectType)
				{
					bObjectHit = World->SweepSingleByObjectType(ObjectTraceHit, TraceStart, TraceEnd, FQuat::Identity, ObjQueryParams, FCollisionShape::MakeSphere(ProjectileRadius), QueryParams);
				}
				if (PredictParams.bTraceWithChannel)
				{
					bChannelHit = World->SweepSingleByChannel(ChannelTraceHit, TraceStart, TraceEnd, FQuat::Identity, PredictParams.TraceChannel, FCollisionShape::MakeSphere(ProjectileRadius), QueryParams);
				}

				// See if there were any hits.
				if (bObjectHit || bChannelHit)
				{
					// Hit! We are done. Choose trace with earliest hit time.
					PredictResult.HitResult = (ObjectTraceHit.Time < ChannelTraceHit.Time) ? ObjectTraceHit : ChannelTraceHit;
					const float HitTimeDelta = ActualStepDeltaTime * PredictResult.HitResult.Time;
					const float TotalTimeAtHit = PreviousTime + HitTimeDelta;
					const FVector VelocityAtHit = OldVelocity + FVector(0.f, 0.f, GravityZ * HitTimeDelta);
					PredictResult.AddPoint(PredictResult.HitResult.Location, VelocityAtHit, TotalTimeAtHit);
					bBlockingHit = true;
					break;
				}
			}

			PredictResult.AddPoint(TraceEnd, CurrentVel, CurrentTime);
		}

		// Draw debug path
#if ENABLE_DRAW_DEBUG
		if (PredictParams.DrawDebugType != EDrawDebugTrace::None)
		{
			const bool bPersistent = PredictParams.DrawDebugType == EDrawDebugTrace::Persistent;
			const float LifeTime = (PredictParams.DrawDebugType == EDrawDebugTrace::ForDuration) ? PredictParams.DrawDebugTime : 0.f;
			const float DrawRadius = (ProjectileRadius > 0.f) ? ProjectileRadius : 5.f;

			// draw the path
			for (const FPredictProjectilePathPointData& PathPt : PredictResult.PathData)
			{
				::DrawDebugSphere(World, PathPt.Location, DrawRadius, 12, FColor::Green, bPersistent, LifeTime);
			}
			// draw the impact point
			if (bBlockingHit)
			{
				::DrawDebugSphere(World, PredictResult.HitResult.Location, DrawRadius + 1.0f, 12, FColor::Red, bPersistent, LifeTime);
			}
		}
#endif //ENABLE_DRAW_DEBUG
	}

	return bBlockingHit;
}

bool AMorse::__PredictProjectilePath_ByObjectType(const UObject* WorldContextObject, FHitResult& OutHit, TArray<FVector>& OutPathPositions, FVector& OutLastTraceDestination, FVector StartPos, FVector LaunchVelocity, bool bTracePath, float ProjectileRadius, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, EDrawDebugTrace::Type DrawDebugType, float DrawDebugTime, float SimFrequency, float MaxSimTime, float OverrideGravityZ)
{
	FPredictProjectilePathParams Params = FPredictProjectilePathParams(ProjectileRadius, StartPos, LaunchVelocity, MaxSimTime);
	Params.bTraceWithCollision = bTracePath;
	Params.bTraceComplex = bTraceComplex;
	Params.ActorsToIgnore = ActorsToIgnore;
	Params.DrawDebugType = DrawDebugType;
	Params.DrawDebugTime = DrawDebugTime;
	Params.SimFrequency = SimFrequency;
	Params.OverrideGravityZ = OverrideGravityZ;
	Params.ObjectTypes = ObjectTypes; // Object trace
	Params.bTraceWithChannel = false;

	// Do the trace
	FPredictProjectilePathResult PredictResult;
	bool bHit = __PredictProjectilePath(WorldContextObject, Params, PredictResult);

	// Fill in results.
	OutHit = PredictResult.HitResult;
	OutLastTraceDestination = PredictResult.LastTraceDestination.Location;
	OutPathPositions.Empty(PredictResult.PathData.Num());
	for (const FPredictProjectilePathPointData& PathPoint : PredictResult.PathData)
	{
		OutPathPositions.Add(PathPoint.Location);
	}
	return bHit;
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
			FSuckingInteractiveCertificate* SuckingInteractiveCertificate = OverlapInteractiveSuckingComponents.Find(SuckingComponent.Get());

			if(nullptr == SuckingInteractiveCertificate)
			{
				OverlapInteractiveSuckingComponents.Add(SuckingComponent.Get());
				SuckingInteractiveCertificate = OverlapInteractiveSuckingComponents.Find(SuckingComponent.Get());
			}

			if(nullptr != SuckingInteractiveCertificate
				&& false == SuckingInteractiveCertificate->OtherComponents.Contains(OtherComp))
			{
				SuckingInteractiveCertificate->OtherComponents.Add(OtherComp);
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
			FSuckingInteractiveCertificate* SuckingInteractiveCertificate = OverlapInteractiveSuckingComponents.Find(SuckingComponent.Get());

			if(nullptr != SuckingInteractiveCertificate)
			{
				SuckingInteractiveCertificate->OtherComponents.Remove(OtherComp);

				if(SuckingInteractiveCertificate->OtherComponents.Num() == 0)
				{
					OverlapInteractiveSuckingComponents.Remove(SuckingComponent.Get());
					SuckingComponent->SetNone(VacuumEntranceComponent.Get());
				}
			}
		}
	}
}

void AMorse::__OnVaccumOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
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
