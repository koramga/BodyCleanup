// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/BTBaseTaskNode.h"
#include "DrawDebugHelpers.h"
#include "BTGameFunctionLibrary.h"
#include "AIController.h"
#include "Interface/BTControllerInterface.h"

UBTBaseTaskNode::UBTBaseTaskNode()
{
}

bool UBTBaseTaskNode::IsGoalActor(AActor* Source, AActor* Target, float Radius, bool bIsDebugDrawing) const
{
	if(nullptr == Source
		|| nullptr == Target
		|| Radius <= 0.f)
	{
		return true;
	}
	
	FVector SourceLocation = Source->GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();
	
	TArray<FHitResult> HitResults;
	FCollisionQueryParams param(NAME_None, true, Source);
	GetWorld()->SweepMultiByChannel(HitResults, SourceLocation, SourceLocation, FQuat::Identity,  ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(Radius), param);

	bool bIsGoal = false;
	
	for(const FHitResult& HitResult : HitResults)
	{
		if(HitResult.GetActor() == Target)
		{
			bIsGoal = true;
			break;
		}
	}
	
#ifdef ENABLE_DRAW_DEBUG

	if(bIsDebugDrawing)
	{
		FColor DrawColor = bIsGoal ? FColor::Red : FColor::Green;
		DrawDebugSphere(GetWorld(), SourceLocation, Radius, 20, DrawColor, false, 0.5f);		
	}	
	
#endif

	return bIsGoal;
}

bool UBTBaseTaskNode::IsAvailableController(AAIController* InAIController) const
{
	if (false == UBTGameFunctionLibrary::IsBTController(InAIController))
	{
		return false;
	}

	const IBTControllerInterface* OwnerControllerInterface = Cast<IBTControllerInterface>(InAIController);

	if (OwnerControllerInterface->IsDeathPossessActor())
	{
		return false;
	}

	return true;
}

void UBTBaseTaskNode::Release(UBehaviorTreeComponent& OwnerComp, EBTNodeResult::Type InType)
{
	return FinishLatentTask(OwnerComp, InType);
}

EBTNodeResult::Type UBTBaseTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

void UBTBaseTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

void UBTBaseTaskNode::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
