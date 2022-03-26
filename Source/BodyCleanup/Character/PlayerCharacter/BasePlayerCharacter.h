// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BaseCharacter.h"
#include "GameFramework/Character.h"
#include "BasePlayerCharacter.generated.h"

UCLASS()
class BODYCLEANUP_API ABasePlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasePlayerCharacter();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	class UPlayerCharacterAnimInstance* PlayerCharacterAnimInstance;

protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float						BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float						BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32						MoveOffset;

	bool						bIsPressedLeftMouse = false;
	bool						bIsPressedRightMouse = false;
	bool						bIsPressedWheelMouse = false;
	bool						bIsPressedInteractive = false;	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void UpdateDeath(bool bInIsDeath) override;
	void SetKeyboardControlType(EKeyboardControlType KeyboardControlType);
	virtual void SetEnableAttack(bool bIsEnableAttack) override;

public :
	bool	IsPressedLeftMouse() const;
	bool	IsPressedRightMouse() const;
	bool	IsPressedWheelMouse() const;
	bool	IsPressedInteractive() const;
	void	SetLookAtMousePoint();

public :
	virtual void InputMoveForward(float InputAxis);
	virtual void InputMoveRight(float InputAxis);
	virtual void InputMouseWheel(float InputAxis);
	virtual void InputJump();
	virtual void InputStopJumping();
	virtual void InputPressedMouseLeftClick();
	virtual void InputReleasedMouseLeftClick();
	virtual void InputPressedMouseRightClick();
	virtual void InputReleasedMouseRightClick();
	virtual void InputPressedMouseWheelClick();
	virtual void InputReleasedMouseWheelClick();
	virtual void InputPressedInteractive();
	virtual void InputReleasedInteractive();
	virtual void InputPressedToggleMoving();
	
};
