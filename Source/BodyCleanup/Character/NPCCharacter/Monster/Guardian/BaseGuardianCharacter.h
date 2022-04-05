// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BodyCleanup/Character/NPCCharacter/Monster/BaseMonsterCharacter.h"
#include "GameFramework/Actor.h"
#include "MetaTools/VariableGroup/MaterialInstanceVariable.h"
#include "BaseGuardianCharacter.generated.h"

USTRUCT(BlueprintType)
struct BODYCLEANUP_API FPhaseInformation
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float			HPPercent = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FMaterialInstanceVariable>	MaterialInstanceVariables;
};

UCLASS()
class BODYCLEANUP_API ABaseGuardianCharacter : public ABaseMonsterCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseGuardianCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnHit(const FOnCAPAttributeChangeData& Data) override;
	virtual void UpdataPhase(int32 InUpdatePhase, const FPhaseInformation& PhaseInformation);
	virtual void UpdatePhaseToBlackboard(int32 InUpdatePhase);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|Phase")
	TArray<FPhaseInformation>		PhaseInformations;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|Phase")
	int								CurrentPhase = 0;
};
