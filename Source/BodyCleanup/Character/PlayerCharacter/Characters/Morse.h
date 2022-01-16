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
	TSet<TSoftObjectPtr<AActor>>			VacuumOverlapActors;

	UPROPERTY(VisibleAnywhere)
	UPrimitiveComponent*	VaccumPrimitiveComponent;


protected :
	FVector					ThrowTargetPos;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void MoveForward(float InputAxis)		override;
	virtual void MoveRight(float InputAxis)			override;
	virtual void InputPressedMouseLeftClick()		override;
	virtual void InputReleasedMouseLeftClick()		override;
	virtual void InputPressedMouseRightClick()		override;
	virtual void InputReleasedMouseRightClick()		override;
	virtual void UpdateAnimationType(EAnimationType AnimationType, EAnimationType BeforeAnimationType) override;

private :
	bool __IsVacuuming() const;
	void __SetOverlapVacuumActorsInteractiveAction(EInteractiveAction InteractiveAction);

private :
	UFUNCTION()
	void __OnVaccumRangeOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void __OnVaccumRangeOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void __OnVaccumOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
