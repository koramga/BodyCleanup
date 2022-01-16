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
	// Begin PlayerController interface
	virtual void BeginPlay() override;

protected :
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

protected :
	virtual void InputPressedSwapCharacter();
	virtual void InputPressedReturnToCharacter();

private :
	void __InputMoveForward(float InputAxis);
	void __InputMoveRight(float InputAxis);
	void __InputMouseWheel(float InputAxis);
	void __InputPressedMouseLeftClick();
	void __InputReleasedMouseLeftClick();
	void __InputPressedMouseRightClick();
	void __InputReleasedMouseRightClick();
	void __InputPressedSwapCharacter();
	void __InputPressedReturnToTank();
	void __InputPressedJump();
	void __InputReleasedJump();
};
