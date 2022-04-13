// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BasePlayerController.h"
#include "GroupPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API AGroupPlayerController : public ABasePlayerController
{
	GENERATED_BODY()

public :
	AGroupPlayerController();

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AMorse>		MorseCharacterClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ATank>		TankCharacterClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABasePlayerAIController>	AISubCharacterControllerClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<class AMorse> Morse;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<class ATank> Tank;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<class ABasePlayerAIController> SubPlayerController;

protected:
	// Begin PlayerController interface
	virtual void BeginPlay() override;

protected:
	virtual void PlayerTick(float DeltaTime) override;

public :
	virtual void OnStartMatch() override;

protected:
	virtual void InputPressedSwapCharacter()			override;
	virtual void InputPressedReturnToCharacter()		override;
};
