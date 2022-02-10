// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/BTTaskAttackTargetNode.h"
#include "AIController.h"
#include "Interface/BTControllerInterface.h"
#include "Interface/BTCharacterInterface.h"
#include "BTGameFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"

UBTTaskAttackTargetNode::UBTTaskAttackTargetNode()
{
	NodeName = TEXT("AttackTarget");
	bNotifyTick = true;
}

void UBTTaskAttackTargetNode::Release(UBehaviorTreeComponent& OwnerComp, EBTNodeResult::Type InType)
{
	Super::Release(OwnerComp, InType);
	
	IBTControllerInterface* OwnerControllerInterface = Cast<IBTControllerInterface>(OwnerComp.GetAIOwner());
	OwnerControllerInterface->DeActivateAbilityByTag(AbilityGameplayTag);

	if(bIsActivateAttack)
	{
		bIsActivateAttack = false;
		OwnerControllerInterface->DeActivateAbilityByTag(AbilityGameplayTag);
		OwnerComp.GetAIOwner()->StopMovement();
	}
}

EBTNodeResult::Type UBTTaskAttackTargetNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	AAIController* OwnerAIController = OwnerComp.GetAIOwner();

	if(false == UBTGameFunctionLibrary::IsBTController(OwnerComp.GetAIOwner()))
	{
		return EBTNodeResult::Failed;
	}

	IBTControllerInterface* OwnerControllerInterface = Cast<IBTControllerInterface>(OwnerComp.GetAIOwner());
	
	TBlackboardVariable BlackboardTargetVariable = OwnerControllerInterface->GetBlackboardVariable(UBTGameFunctionLibrary::TargetObjectName, EBlackboardVariableType::Object);

	if(OwnerControllerInterface->IsDeathPossessActor())
	{
		return EBTNodeResult::Failed;
	}
	
	IBTControllerInterface* TargetControllerInterface = Cast<IBTControllerInterface>(BlackboardTargetVariable.Get<UObject*>());

	if(TargetControllerInterface == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	if(TargetControllerInterface->IsDeathPossessActor())
	{
		return EBTNodeResult::Failed;
	}
	
	TBlackboardVariable BlackboardVariable = OwnerControllerInterface->GetBlackboardVariable(UBTGameFunctionLibrary::PhaseName, EBlackboardVariableType::Int32);
	int32 Phase = BlackboardVariable.Get<int32>();

	for(int i = 0; i < 5; ++i)
	{
		FString AttackAbilityTag = FString::Printf(TEXT("NPC.Attack.%d.%d"), Phase, i);

		AbilityGameplayTag = FGameplayTag::RequestGameplayTag(FName(AttackAbilityTag));

		FBTAbilityInfo AbilityInfo = OwnerControllerInterface->GetAbilityInfoByTag(AbilityGameplayTag);

		if (false == AbilityInfo.IsActivate
			&& true == AbilityInfo.CanActivate)
		{
			if (AbilityInfo.Range <= 0.f)
			{
				return EBTNodeResult::InProgress;
			}
			else
			{
				TBlackboardVariable TraceTargetRangeVariable;
				TraceTargetRangeVariable.Set<float>(AbilityInfo.Range);

				if (IsGoalActor(OwnerControllerInterface->GetPossessActor(), TargetControllerInterface->GetPossessActor(), TraceTargetRangeVariable.Get<float>()))
				{
					return EBTNodeResult::InProgress;
				}
				else
				{
					OwnerControllerInterface->SetBlackboardVariable(UBTGameFunctionLibrary::GoalTraceTargetRangeName, TraceTargetRangeVariable);
					return EBTNodeResult::Failed;
				}
			}
		}
	}
	
	return EBTNodeResult::Failed;
}

void UBTTaskAttackTargetNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* OwnerAIController = OwnerComp.GetAIOwner();
	IBTControllerInterface* OwnerControllerInterface = Cast<IBTControllerInterface>(OwnerComp.GetAIOwner());

	if(OwnerControllerInterface->IsDeathPossessActor())
	{
		return Release(OwnerComp, EBTNodeResult::Failed);
	}
	
	TBlackboardVariable BlackboardTargetVariable = OwnerControllerInterface->GetBlackboardVariable(UBTGameFunctionLibrary::TargetObjectName, EBlackboardVariableType::Object);
	
	IBTControllerInterface* TargetControllerInterface = Cast<IBTControllerInterface>(BlackboardTargetVariable.Get<UObject*>());

	if(TargetControllerInterface == nullptr)
	{
		return Release(OwnerComp, EBTNodeResult::Failed);
	}

	if(TargetControllerInterface->IsDeathPossessActor())
	{
		return Release(OwnerComp, EBTNodeResult::Failed);
	}

	if(false == bIsActivateAttack)
	{
		if(false == OwnerControllerInterface->ActivateAbilityByTag(AbilityGameplayTag))
		{
			return Release(OwnerComp, EBTNodeResult::Failed);
		}
		else
		{
			AActor* OwnerPossessActor = OwnerControllerInterface->GetPossessActor();			
		
			FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(OwnerPossessActor->GetActorLocation(),TargetControllerInterface->GetPossessActor()->GetActorLocation());

			FRotator OwnerPossessActorRotation = OwnerPossessActor->GetActorRotation();
			OwnerPossessActorRotation.Yaw = LookAtRotation.Yaw;
			OwnerPossessActor->SetActorRotation(OwnerPossessActorRotation);			
			
			bIsActivateAttack = true;
		}		
	}
	else
	{
		FBTAbilityInfo AbilityInfo = OwnerControllerInterface->GetAbilityInfoByTag(AbilityGameplayTag);

		if(false == AbilityInfo.IsActivate)
		{
			return Release(OwnerComp, EBTNodeResult::Succeeded);			
		}
	}
}