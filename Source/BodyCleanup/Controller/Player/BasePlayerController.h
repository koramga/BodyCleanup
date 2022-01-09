// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../ExDefines.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public :
	ABasePlayerController();

protected :
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AMorse>		MorseCharacterClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ATank>		TankCharacterClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class AMorse* Morse;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class ATank* Tank;

protected :
	// Begin PlayerController interface
	virtual void BeginPlay() override;

protected :
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

private :
	void __InputMoveForward(float InputAxis);
	void __InputMoveRight(float InputAxis);
	void __InputPressedMouseLeftClick();
	void __InputReleasedMouseLeftClick();
	void __InputPressedMouseRightClick();
	void __InputPressedSwapCharacter();
	void __InputPressedReturnTank();
	void __InputPressedJump();
	void __InputReleasedJump();
};
