// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mors.h"
#include "MorsWithShovel.generated.h"

UCLASS()
class BODYCLEANUP_API AMorsWithShovel : public AMors
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMorsWithShovel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
