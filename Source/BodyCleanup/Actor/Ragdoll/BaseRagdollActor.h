// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseActor.h"
#include "BaseRagdollActor.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API ABaseRagdollActor : public ABaseActor
{
	GENERATED_BODY()

public :
	ABaseRagdollActor();
	
protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USkeletalMeshComponent* SkeletalMeshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void UpdateDeath(bool bInIsDeath) override;

};
