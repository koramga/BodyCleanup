// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BasePlayerCharacter.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API ATank : public ABasePlayerCharacter
{
	GENERATED_BODY()

public :
	ATank();

protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool	bIsFly;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool	bIsDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<ACharacter> FollowCharacter;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public :
	void SetFlyMode(TSoftObjectPtr<ACharacter> InputFollowCharacter);
	bool IsFlyMode() const;

public:
	virtual void MoveForward(float InputAxis) override;
	virtual void MoveRight(float InputAxis) override;
	virtual void InputPressedMouseLeftClick()	override;
	virtual void InputReleasedMouseLeftClick()	override;
};
