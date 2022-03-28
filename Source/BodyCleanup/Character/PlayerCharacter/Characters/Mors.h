// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BodyCleanup/Character/PlayerCharacter/BasePlayerCharacter.h"
#include "Mors.generated.h"

UCLASS()
class BODYCLEANUP_API AMors : public ABasePlayerCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMors();

protected:
	class AWeaponModularActor*	WeaponModularActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	virtual void InputPressedMouseLeftClick() override;
	virtual void InputReleasedMouseLeftClick() override;
	virtual void InputPressedMouseRightClick() override;
	virtual void InputReleasedMouseRightClick() override;
	virtual void InputPressedMouseWheelClick() override;
	virtual void InputReleasedMouseWheelClick() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
