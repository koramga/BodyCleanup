// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../ExDefines.h"
#include "Components/SphereComponent.h"
#include "VacuumEntranceComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Characters), meta = (BlueprintSpawnableComponent))
class BODYCLEANUP_API UVacuumEntranceComponent : public USphereComponent
{
	GENERATED_BODY()
	
public :
	UVacuumEntranceComponent();

protected :
	UPROPERTY(VisibleAnywhere, Category = "Debug|VacuumEntranceComponent")
	TSoftObjectPtr<AActor>	HoldingActor;

	UPROPERTY(VisibleAnywhere, Category = "Debug|VacuumEntranceComponent")
	TSoftObjectPtr<class UPhysicsConstraintComponent>	GrabConstraintComponent;

	UPROPERTY(VisibleAnywhere, Category = "Debug|VacuumEntranceComponent")
	TSoftObjectPtr<UStaticMeshComponent> HeldObjectSlotComponent;

	UPROPERTY(VisibleAnywhere)
	bool	bIsSucking = false;

private :
	void __GrabActor();
	void __DropActor();

public :
	bool IsSucking() const;
	void SetSucking(bool bInputIsSucking);
	void SetHoldingActor(TSoftObjectPtr<AActor> InputHoldingActor);
	TSoftObjectPtr<AActor> GetHoldingActor() const;
	bool HasHoldingActor() const;

	void SetHeldObjectSlot(UStaticMeshComponent* InputHeldObjectSlotComponent);
	void SetGrabConstraintComponent(class UPhysicsConstraintComponent* InputGrabConstraintComponent);

public :
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
