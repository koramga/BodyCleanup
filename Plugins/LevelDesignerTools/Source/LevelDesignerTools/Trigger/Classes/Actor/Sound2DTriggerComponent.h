// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerActorComponent.h"
#include "Sound2DTriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Triggers), meta = (BlueprintSpawnableComponent))
class LEVELDESIGNERTOOLS_API USound2DTriggerComponent : public UTriggerActorComponent
{
	GENERATED_BODY()
	
public :
	USound2DTriggerComponent();

	protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|Sound2DTriggerComponent")
	USoundWave*		SoundWave;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug|Sound2DTriggerComponent")
	UAudioComponent*	AudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|Sound2DTriggerComponent")
	float			FadeInTime = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|Sound2DTriggerComponent")
	float			FadeOutTime = 1.f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam) override;
};
