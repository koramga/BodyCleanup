// Fill out your copyright notice in the Description page of Project Settings.


#include "BTGameFunctionLibrary.h"
#include "Interface/BTControllerInterface.h"
#include "Interface/BTCharacterInterface.h"
#include "DrawDebugHelpers.h"

const FName UBTGameFunctionLibrary::TraceRangeName = TEXT("TraceRange");
const FName UBTGameFunctionLibrary::TargetObjectName = TEXT("TargetObject");
const FName UBTGameFunctionLibrary::LookAroundCycleTimeName = TEXT("LookAroundCycleTime");
const FName UBTGameFunctionLibrary::PhaseName = TEXT("Phase");
const FName UBTGameFunctionLibrary::GoalTraceTargetRangeName = TEXT("GoalTraceTargetRange");

bool UBTGameFunctionLibrary::IsBTActor(const AActor* Actor)
{
	if(false == Actor->GetClass()->ImplementsInterface(UBTCharacterInterface::StaticClass()))
	{
		return false;
	}

	AController* Controller = Actor->GetInstigatorController();

	if(false == IsValid(Controller))
	{
		return false;
	}

	if(false == Controller->GetClass()->ImplementsInterface(UBTControllerInterface::StaticClass()))
	{
		return false;
	}

	return true;
}

bool UBTGameFunctionLibrary::IsBTController(const AController* Controller)
{
	return IsBTActor(Controller->GetPawn());
}

bool UBTGameFunctionLibrary::IsEnemy(const IBTControllerInterface* LHS, const IBTControllerInterface* RHS)
{
	ETeamType LHSTeamType = LHS->GetTeamType();
	ETeamType RHSTeamType = RHS->GetTeamType();

	if(ETeamType::None == LHSTeamType
		|| ETeamType::None == RHSTeamType)
	{
		//None은 무시한다.
		return false;
	}

	if(LHSTeamType != RHSTeamType)
	{
		return true;
	}

	return false;
}

float UBTGameFunctionLibrary::GetSurface(UWorld* World, const FVector& Point, bool bDrawDebugLines, const TArray<AActor*>* IgnoreActors)
{
	if (World)
	{
		FVector StartLocation{ Point.X, Point.Y, 1000 };    // Raytrace starting point.
		FVector EndLocation{ Point.X, Point.Y, -1000 };            // Raytrace end point.

		FCollisionQueryParams param;

		if (nullptr != IgnoreActors)
		{
			for (AActor* IgnoreActor : (*IgnoreActors))
			{
				param.AddIgnoredActor(IgnoreActor);
			}
		}

		// Raytrace for overlapping actors.
		FHitResult HitResult;
		World->LineTraceSingleByObjectType(
			OUT HitResult,
			StartLocation,
			EndLocation,
			FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
			param
		);

		// Draw debug line.
		if (bDrawDebugLines)
		{
			FColor LineColor;

			if (HitResult.GetActor()) LineColor = FColor::Red;
			else LineColor = FColor::Green;

			DrawDebugLine(
				World,
				StartLocation,
				EndLocation,
				LineColor,
				true,
				5.f,
				0.f,
				10.f
			);
		}

		// Return Z location.
		if (HitResult.GetActor()) return HitResult.ImpactPoint.Z;
	}

	return 0;
}
