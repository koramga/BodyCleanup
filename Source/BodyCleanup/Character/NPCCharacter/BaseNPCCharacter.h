// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseCharacter.h"
#include "BaseNPCCharacter.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ENPCPatrolType : uint8
{
	None,
	Point,
	Space,	
};

UCLASS()
class BODYCLEANUP_API ABaseNPCCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public :
	ABaseNPCCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|NPCCharacter")
	ENPCPatrolType						PatrolType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|NPCCharacter", meta = (EditCondition = "PatrolType != ENPCPatrolType::None", EditConditionHides))
	TArray<class ABasePatrolActor*>		PatrolActors;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	
};
