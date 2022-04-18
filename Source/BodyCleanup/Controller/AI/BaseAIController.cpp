// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIController.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BodyCleanup/Character/BaseCharacter.h"
#include "BTGameFunctionLibrary.h"

ABaseAIController::ABaseAIController()
{
	TeamType = ETeamType::None;
}

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	UE_LOG(LogTemp, Display, TEXT("koramga : <%s> OnPossess"), *InPawn->GetName());

	UBlackboardComponent* BlackboardComponent = Blackboard.Get();
	
	if(IsValid(BehaviorTree)
		&& IsValid(BlackboardData))
	{
		if(false == UseBlackboard(BlackboardData, BlackboardComponent))
		{
			UE_LOG(LogTemp, Display, TEXT("ABaseAIController::OnPossess UseBlackboard Failed.."));
			return;			
		}
		
		if (false == RunBehaviorTree(BehaviorTree))
		{
			UE_LOG(LogTemp, Display, TEXT("ABaseAIController::OnPossess RunBehaviorTree Failed.."));
			return;
		}

		InitializeBlackboardData();

		UE_LOG(LogTemp, Display, TEXT("AI OnPossess Success"));
	}
	
	Super::OnPossess(InPawn);
}

void ABaseAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ABaseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ABaseAIController::InitializeBlackboardData()
{
	
}

ETeamType ABaseAIController::GetTeamType() const
{
	return TeamType;
}

TBlackboardVariable ABaseAIController::GetBlackboardVariable(const FName& Name, EBlackboardVariableType BlackboardVariableType) const
{
	TBlackboardVariable Variable;
	
	switch (BlackboardVariableType)
	{
	case EBlackboardVariableType::Float :
		Variable.Set<float>(Blackboard->GetValueAsFloat(Name));
		break;
	case EBlackboardVariableType::Int32 :
		Variable.Set<int32>(Blackboard->GetValueAsInt(Name));
		break;
	case EBlackboardVariableType::Object :
		Variable.Set<UObject*>(Blackboard->GetValueAsObject(Name));
		break;
	case EBlackboardVariableType::FVector :
		Variable.Set<FVector>(Blackboard->GetValueAsVector(Name));
		break;

	case EBlackboardVariableType::Bool :
		Variable.Set<bool>(Blackboard->GetValueAsBool(Name));
		break;
	}
	
	return Variable;
}

bool ABaseAIController::SetBlackboardVariable(const FName& Name, const TBlackboardVariable& Variable)
{
	switch (static_cast<EBlackboardVariableType>(Variable.GetIndex()))
	{
	case EBlackboardVariableType::Float :
		Blackboard->SetValueAsFloat(Name, Variable.Get<float>());
		break;
	case EBlackboardVariableType::Int32 :
		Blackboard->SetValueAsInt(Name, Variable.Get<int32>());
		break;
	case EBlackboardVariableType::Object :
		Blackboard->SetValueAsObject(Name, Variable.Get<UObject*>());
		break;
	case EBlackboardVariableType::FVector :
		Blackboard->SetValueAsVector(Name, Variable.Get<FVector>());
		break;
	case EBlackboardVariableType::Bool :
		Blackboard->SetValueAsBool(Name, Variable.Get<bool>());
		break;
	}
	
	return true;
}

bool ABaseAIController::IsDeathPossessActor() const
{
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetCharacter());

	if(IsValid(BaseCharacter))
	{
		return BaseCharacter->IsDeath();
	}

	return true;	
}

FVector ABaseAIController::GetCharacterLocation() const
{
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetCharacter());

	if(IsValid(BaseCharacter))
	{
		return BaseCharacter->GetActorLocation();
	}

	return FVector();
}

AActor* ABaseAIController::GetPossessActor() const
{
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetCharacter());

	if(IsValid(BaseCharacter))
	{
		return BaseCharacter;
	}

	return nullptr;
}

bool ABaseAIController::CanMovePossessActor() const
{
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetCharacter());

	if(IsValid(BaseCharacter))
	{
		return BaseCharacter->CanMove();
	}

	return false;
}

bool ABaseAIController::CanUpdateAnimationPossessActor(uint8 InAnimationType) const
{
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetCharacter());

	if(IsValid(BaseCharacter))
	{
		return BaseCharacter->CanUpdateAnimationType(static_cast<EAnimationType>(InAnimationType));
	}

	return false;
}

FBTAbilityInfo ABaseAIController::GetAbilityInfoByTag(const FGameplayTag& Tag) const
{
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetCharacter());

	if (IsValid(BaseCharacter))
	{
		return BaseCharacter->GetAbilityInfoByTag(Tag);
	}

	return FBTAbilityInfo();
	
}

bool ABaseAIController::ActivateAbilityByTag(const FGameplayTag& Tag)
{
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetCharacter());

	if(IsValid(BaseCharacter))
	{
		return BaseCharacter->ActivateAbilityByTag(Tag);
	}

	return false;
}

bool ABaseAIController::DeActivateAbilityByTag(const FGameplayTag& Tag)
{
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetCharacter());

	if(IsValid(BaseCharacter))
	{
		return BaseCharacter->DeActivateAbilityByTag(Tag);
	}
	
	return false;
}

EBTPatrolType ABaseAIController::GetPatrolType() const
{
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetCharacter());

	if(IsValid(BaseCharacter))
	{
		return BaseCharacter->GetPatrolType();
	}
	
	return EBTPatrolType::None;
}

IBTPatrolActorInterface* ABaseAIController::GetPatrolActorInterface() const
{
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetCharacter());

	if(IsValid(BaseCharacter))
	{
		return BaseCharacter->GetPatrolActorInterface();
	}

	return nullptr;
}

void ABaseAIController::SetNextPatrol()
{
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetCharacter());

	if(IsValid(BaseCharacter))
	{
		return BaseCharacter->SetNextPatrol();
	}
}

FBTPatrolInfo ABaseAIController::GetPatrolInfo() const
{
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetCharacter());

	if(IsValid(BaseCharacter))
	{
		return BaseCharacter->GetPatrolInfo();
	}

	return FBTPatrolInfo();
}
