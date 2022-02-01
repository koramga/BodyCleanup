// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BasePlayerCharacter.h"
#include "MetaTools/Static/InputProperties.h"
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
	TSubclassOf<AActor>		ArcShootingSpawnActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPropertyName			ArcShootingSpawnPhysicsComponents;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					CreateArcShootingSpawnActorOffset = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					ActorRotationInterpValue = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					MinArcShootingRange = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					MaxArcShootingRange = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float					MaxArcShootingZ = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.1", ClampMax = "0.9", UIMin = "0.1", UIMax = "0.9"))
	float					MinArcShootingArcRange = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.1", ClampMax = "0.9", UIMin = "0.1", UIMax = "0.9"))
	float					MaxArcShootingArcRange = 0.9f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32					JunkValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent*				HeldObjectSlotComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UPhysicsConstraintComponent*	GrabConstraintComponent;

	UPROPERTY(VisibleAnywhere)
	TSet<class UInteractiveSuckingComponent*>		OverlapInteractiveSuckingComponents;
	
	UPROPERTY(VisibleAnywhere)
	TSoftObjectPtr<class UVacuumEntranceComponent>	VacuumEntranceComponent;

	UPROPERTY(VisibleAnywhere)
	TSoftObjectPtr<class UMorseAnimInstance>		MorseAnimInstance;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent*							JunkValueViewerWidgetComponent;


protected :
	FVector					ArcShootingVelocity;
	float					ArcShootingArcValue = 0.5f;
	bool					bIsCanArcShooting = false;

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
	bool __IsArcShooting() const;
	void __UpdateOverlapInteractigeSuckingComponent(float DeltaTime);
	FVector __ProcessMaxDistnace(const FVector& StartArcShootingLocation, const FVector& EndArcShootingLocation);
	
	bool __SetHoldShooting(UInteractiveSuckingComponent* InteractiveSuckingComponent);
	bool __SetHolding(UInteractiveSuckingComponent* InteractiveSuckingComponent);
	void __SetSucking(UInteractiveSuckingComponent* InteractiveSuckingComponent);

public :
	void SetJunkValue(int32 InJunkValue);
	void AddJunkValue(int32 DeltaJunkValue);
	int32 GetJunkValue() const;
	
private :
	UFUNCTION()
	void __OnVaccumRangeOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void __OnVaccumRangeOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void __OnVaccumOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
