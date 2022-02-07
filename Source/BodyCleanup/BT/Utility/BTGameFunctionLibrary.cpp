// Fill out your copyright notice in the Description page of Project Settings.


#include "BTGameFunctionLibrary.h"
#include "../Interface/BTControllerInterface.h"
#include "../Interface/BTCharacterInterface.h"

const FName UBTGameFunctionLibrary::TraceRangeName = TEXT("TraceRange");
const FName UBTGameFunctionLibrary::LookAroundTimeName = TEXT("LookAroundTime");
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
