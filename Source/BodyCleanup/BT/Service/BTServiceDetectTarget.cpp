// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServiceDetectTarget.h"
#include "AIController.h"
#include "../../BT/Interface/BTControllerInterface.h"
#include "../../BT/Interface/BTCharacterInterface.h"
#include "../../Controller/Player/BasePlayerController.h"
#include "../Utility/BTGameFunctionLibrary.h"
#include "DrawDebugHelpers.h"

UBTServiceDetectTarget::UBTServiceDetectTarget()
{
	Interval = 0.5f;
	NodeName = TEXT("DetectTarget");
}

void UBTServiceDetectTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if(false == UBTGameFunctionLibrary::IsBTController(OwnerComp.GetAIOwner()))
	{
		return;
	}
	
	IBTControllerInterface* OwnerControllerInterface = Cast<IBTControllerInterface>(OwnerComp.GetAIOwner());

	if(OwnerControllerInterface->IsDeathPossessActor())
	{
		return;
	}
	
	TBlackboardVariable TraceRangeVariable = OwnerControllerInterface->GetBlackboardVariable(UBTGameFunctionLibrary::TraceRangeName, EBlackboardVariableType::Float);
	TArray<FHitResult> HitResults;

	FVector OwnerCharacterLocation = OwnerControllerInterface->GetCharacterLocation();

	if(TraceRangeVariable.IsType<float>())
	{
		FCollisionQueryParams param(NAME_None, true, OwnerControllerInterface->GetPossessActor());
		GetWorld()->SweepMultiByChannel(HitResults, OwnerCharacterLocation, OwnerCharacterLocation, FQuat::Identity,  ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(TraceRangeVariable.Get<float>()), param);	
	}

	float Distance = FLT_MAX;
	IBTControllerInterface* TargetControllerInterface = nullptr;
	
	for(const FHitResult& HitResult : HitResults)
	{
		AActor* HitActor = HitResult.GetActor();

		if(false == UBTGameFunctionLibrary::IsBTActor(HitActor))
		{
			continue;
		}

		IBTControllerInterface* ControllerInterface = Cast<IBTControllerInterface>(HitActor->GetInstigatorController());

		if(ControllerInterface->IsDeathPossessActor())
		{
			continue;
		}

		if(false == UBTGameFunctionLibrary::IsEnemy(OwnerControllerInterface, ControllerInterface))
		{
			continue;
		}

		FVector CharacterLocation = ControllerInterface->GetCharacterLocation();

		float CurrentDistance = FVector::Distance(OwnerCharacterLocation, CharacterLocation);

		if(Distance > CurrentDistance)
		{
			Distance = CurrentDistance;
			TargetControllerInterface = ControllerInterface;
		}
	}

#ifdef ENABLE_DRAW_DEBUG

	FColor DrawColor = TargetControllerInterface ? FColor::Red : FColor::Green;
	DrawDebugSphere(GetWorld(), OwnerCharacterLocation, TraceRangeVariable.Get<float>(), 20, DrawColor, false, 0.5f);
	
#endif

	TBlackboardVariable TargetVariable;
	
	TargetVariable.Set<UObject*>(nullptr);
	
	if(nullptr != TargetControllerInterface)
	{
		TargetVariable.Set<UObject*>(Cast<UObject>(TargetControllerInterface));
	}

	OwnerControllerInterface->SetBlackboardVariable(UBTGameFunctionLibrary::TargetObjectName, TargetVariable);
}