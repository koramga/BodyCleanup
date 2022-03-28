// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/BTTaskPatrolNode.h"
#include "AIController.h"
#include "Interface/BTControllerInterface.h"
#include "Interface/BTCharacterInterface.h"
#include "BTGameFunctionLibrary.h"
#include "Interface/BTPatrolActorInterface.h"

UBTTaskPatrolNode::UBTTaskPatrolNode()
{
	NodeName = TEXT("PatrolNode");
	bNotifyTick = true;
	AbilityGameplayTag = FGameplayTag::RequestGameplayTag(TEXT("NPC.Ability.Patrol"));
}


void UBTTaskPatrolNode::Release(UBehaviorTreeComponent& OwnerComp, EBTNodeResult::Type InType)
{
	IBTControllerInterface* OwnerControllerInterface = Cast<IBTControllerInterface>(OwnerComp.GetAIOwner());
	OwnerControllerInterface->DeActivateAbilityByTag(AbilityGameplayTag);

	if(bIsActivateAbility)
	{
		bIsActivateAbility = false;
		OwnerControllerInterface->DeActivateAbilityByTag(AbilityGameplayTag);
		OwnerComp.GetAIOwner()->StopMovement();
	}
	
	Super::Release(OwnerComp, InType);
}

EBTNodeResult::Type UBTTaskPatrolNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if(false == IsAvailableController(OwnerComp.GetAIOwner()))
	{
		return EBTNodeResult::Failed; 
	}

	const IBTControllerInterface* OwnerControllerInterface = Cast<IBTControllerInterface>(OwnerComp.GetAIOwner());

	if(EBTPatrolType::None == OwnerControllerInterface->GetPatrolType())
	{
		return EBTNodeResult::Failed;
	}
	
	FBTAbilityInfo AbilityInfo = OwnerControllerInterface->GetAbilityInfoByTag(AbilityGameplayTag);

	if(false == AbilityInfo.CanActivate)
	{
		return EBTNodeResult::Failed;
	}

	PatrolType = OwnerControllerInterface->GetPatrolType();

	return EBTNodeResult::InProgress;
}

void UBTTaskPatrolNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	AAIController* OwnerAIController = OwnerComp.GetAIOwner();
	IBTControllerInterface* OwnerControllerInterface = Cast<IBTControllerInterface>(OwnerComp.GetAIOwner());

	if(OwnerControllerInterface->IsDeathPossessActor())
	{
		return Release(OwnerComp, EBTNodeResult::Failed);
	}

	IBTPatrolActorInterface* PatrolActorInterface = OwnerControllerInterface->GetPatrolActorInterface();

	if(nullptr == PatrolActorInterface)
	{
		return Release(OwnerComp, EBTNodeResult::Failed);
	}

	TBlackboardVariable BlackboardTargetVariable = OwnerControllerInterface->GetBlackboardVariable(UBTGameFunctionLibrary::TargetObjectName, EBlackboardVariableType::Object);
	
	IBTControllerInterface* TargetControllerInterface = Cast<IBTControllerInterface>(BlackboardTargetVariable.Get<UObject*>());

	if(TargetControllerInterface != nullptr)
	{
		return Release(OwnerComp, EBTNodeResult::Failed);
	}
	
	FBTPatrolInfo PatrolInfo = OwnerControllerInterface->GetPatrolInfo();

	if(false == bIsActivateAbility)
	{
		bIsActivateAbility = true;		
		OwnerControllerInterface->ActivateAbilityByTag(AbilityGameplayTag);

		if(EBTPatrolType::Space == PatrolType)
		{
			bool bIsFindPath = false;
			
			AActor* PossessActor = OwnerControllerInterface->GetPossessActor();

			FRotator Rotator = PossessActor->GetActorRotation();

			while(true)
			{
				float RandYaw = FMath::RandRange(-90, 90);
			
				Rotator.Yaw += RandYaw;

				PossessActor->SetActorRelativeRotation(Rotator.Quaternion());

				FVector ForwardVector = PossessActor->GetActorForwardVector();
				FVector LocationVector = PossessActor->GetActorLocation();

				float Distance = PatrolInfo.MaxDistance;
			
				while(Distance >= PatrolInfo.MinDistance)
				{
					SpaceGoalPoint = ForwardVector * Distance + LocationVector;

					SpaceGoalPoint.Z = UBTGameFunctionLibrary::GetSurface(GetWorld(), SpaceGoalPoint);

					if(PatrolActorInterface->IsPointInActor(SpaceGoalPoint)
						&& false == IsGoalLocation(OwnerControllerInterface->GetPossessActor(), SpaceGoalPoint, PatrolInfo.GoalRadius))
					{
						bIsFindPath = true;
						break;
					}

					Distance /= 2.f;
				}

				if(bIsFindPath)
				{
					break;
				}				
			}		
		}
	}

	if(EBTPatrolType::Point == PatrolType)
	{
		if(PatrolActorInterface->IsGoal(OwnerControllerInterface->GetPossessActor()))
		{
			OwnerControllerInterface->SetNextPatrol();
			return Release(OwnerComp, EBTNodeResult::Succeeded);
		}
		else
		{
			OwnerAIController->MoveToLocation(PatrolActorInterface->GetGoalPosition());
		}		
	}
	else if(EBTPatrolType::Space == PatrolType)
	{
		if(IsGoalLocation(OwnerControllerInterface->GetPossessActor(), SpaceGoalPoint, PatrolInfo.GoalRadius))
		{
			return Release(OwnerComp, EBTNodeResult::Succeeded);
		}
		else
		{
			OwnerAIController->MoveToLocation(SpaceGoalPoint);
		}
	}
	
}
