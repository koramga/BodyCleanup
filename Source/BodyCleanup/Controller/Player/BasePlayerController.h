// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../ExDefines.h"
#include "GameFramework/PlayerController.h"
#include "../../BT/Interface/BTControllerInterface.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API ABasePlayerController : public APlayerController, public IBTControllerInterface
{
	GENERATED_BODY()

public :
	ABasePlayerController();

protected:
	bool	bIsFocusOnCharacter = true;


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
	void __InputPressedInteractive();
	void __InputReleasedInteractive();
	void __InputPressedUITestKey();
	void __InputPressedUIUp();
	void __InputPressedUIDown();
	void __InputPressedEnter();

public :
	virtual void SetFocusOnCharacter(bool bInIsFocusOnCharacter);
	virtual bool IsFocusOnCharacter() const;
	
public :
	virtual ETeamType GetTeamType() const override;
	virtual TBlackboardVariable GetBlackboardVariable(const FName& Name, EBlackboardVariableType BlackboardVariableType) const override;
	virtual bool SetBlackboardVariable(const FName& Name, const TBlackboardVariable& Variable) override;
	virtual bool IsDeathPossessActor() const override;
	virtual FVector GetCharacterLocation() const override;
	virtual AActor* GetPossessActor() const override;
	virtual bool CanUpdateTaskPattern(EBTTaskPatternType PatternType) const override;
	virtual bool SetTaskPattern(EBTTaskPatternType PatternType) override;
	virtual EBTTaskPatternType GetTaskPattern() const override;
};