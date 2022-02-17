// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseRagdollActor.h"
#include "RobotCorpseActor.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API ARobotCorpseActor : public ABaseRagdollActor
{
	GENERATED_BODY()

public :
	ARobotCorpseActor();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UInteractiveSuckingComponent* InteractiveSuckingComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void UpdateDeath(bool bInIsDeath) override;
	
};
