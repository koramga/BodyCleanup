// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BasePlayerCharacter.h"
#include "Morse.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API AMorse : public ABasePlayerCharacter
{
	GENERATED_BODY()

public :
	AMorse();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent*		HorseComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor>		ShotSpawnActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					CreateShotSpawnActorOffset = 150.f;

	UPROPERTY(VisibleAnywhere)
	TSet<TSoftObjectPtr<AActor>>					VacuumOverlapActors;

	UPROPERTY(VisibleAnywhere)
	TSoftObjectPtr<class UVacuumEntranceComponent>	VacuumEntranceComponent;


protected :
	FVector					ThrowTargetPos;
	float					ThrowArcValue = 0.5f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void InputMoveForward(float InputAxis)	override;
	virtual void InputMoveRight(float InputAxis)	override;
	virtual void InputMouseWheel(float InputAxis)	override;
	virtual void InputPressedMouseLeftClick()		override;
	virtual void InputReleasedMouseLeftClick()		override;
	virtual void InputPressedMouseRightClick()		override;
	virtual void InputReleasedMouseRightClick()		override;
	virtual void UpdateAnimationType(EAnimationType AnimationType, EAnimationType BeforeAnimationType) override;

private :
	bool __IsVacuuming() const;
	bool __CanVacuuming() const;
	bool __IsShooting() const;
	void __SetOverlapVacuumActorsInteractiveAction(EInteractiveAction InteractiveAction);
	void __SetInteractiveComponent(TSoftObjectPtr<AActor> Actor, TSoftObjectPtr<class UVacuumEntranceComponent> SetInteractiveComponent);
	void __SetInteractiveAction(TSoftObjectPtr<AActor> Actor, EInteractiveAction InteractiveAction);

private :
	UFUNCTION()
	void __OnVaccumRangeOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void __OnVaccumRangeOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void __OnVaccumOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
