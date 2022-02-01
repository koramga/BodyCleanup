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
	//Sound Wave는 Resource를 지정해야합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|Sound2DTriggerComponent")
	USoundWave*		SoundWave;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debug|Sound2DTriggerComponent")
	UAudioComponent*	AudioComponent;

	//시작 시, Fade In Time을 고려하여 시작합니다. 0이하의 값은 Fade In을 활용하지 않겠다는 의미가 됩니다. 기준은 초(Sec) 입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|Sound2DTriggerComponent")
	float			FadeInTime = 0.f;

	//종료 시, Fade Out Time을 고려하여 종료합니다. 0이하의 값은 Fade Out을 활용하지 않겠다는 의미가 됩니다. 기준은 초(Sec) 입니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|Sound2DTriggerComponent")
	float			FadeOutTime = 1.f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam) override;
};
