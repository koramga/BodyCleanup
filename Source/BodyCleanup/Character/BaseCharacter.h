// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ExDefines.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class BODYCLEANUP_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected :
	UPROPERTY(VisibleAnywhere)
	class UBaseAnimInstance* BaseAnimInstance;

	UPROPERTY(VisibleAnywhere)
	FName BodyCollisionProfileName;

	UPROPERTY(VisibleAnywhere)
	AController* BaseController;

	UPROPERTY(VisibleAnywhere)
	class UInteractiveMovementComponent* InteractiveMovementComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public :
	void SetEnableCapsuleCollision(bool bIsEnable);
	bool IsInteractiveCharacter() const;
	void SetInteractiveActivate(bool bActivate);
	void SetInteractiveAction(EInteractiveAction InputInteractiveAction);
	class UInteractiveMovementComponent* GetInteractiveMovementComponent() const;
};