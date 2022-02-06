// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../ExDefines.h"
#include "AIController.h"
#include "../../BT/Interface/BTControllerInterface.h"
#include "MetaTools/Variable/FloatVariableMetaData.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API ABaseAIController : public AAIController, public IBTControllerInterface
{
	GENERATED_BODY()
	
public :
	ABaseAIController();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|BaseAIController")
	class UBehaviorTree*					BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|BaseAIController")
	class UBlackboardData*					BlackboardData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|BaseAIController")
	ETeamType								TeamType;
	
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public :
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void InitializeBlackboardData();

public :
	virtual ETeamType GetTeamType() const override;
	virtual TBlackboardVariable GetBlackboardVariable(const FName& Name, EBlackboardVariableType BlackboardVariableType) const override;
	virtual bool SetBlackboardVariable(const FName& Name, const TBlackboardVariable& Variable) override;
	virtual bool IsDeathPossessActor() const override;
	virtual FVector GetCharacterLocation() const override;
	virtual AActor* GetPossessActor() const override;
	virtual bool CanActivateAbilityByTag(const struct FGameplayTag& Tag) const override;
	virtual bool ActivateAbilityByTag(const struct FGameplayTag& Tag) override;
	virtual bool IsActivateAbilityByTag(const struct FGameplayTag& Tag) const override;
};