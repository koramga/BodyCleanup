// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BodyCleanup/Actor/BaseActor.h"
#include "BaseModularActor.generated.h"

UCLASS()
class BODYCLEANUP_API ABaseModularActor : public ABaseActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseModularActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public :
	void SetEnableCollision(bool bIsEnableCollision);
	void SetDuplicateOverlap(bool bInIsDuplicateOverlap);

protected:
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						  int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UFUNCTION()
	void __OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                      int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBoxComponent*	BoxComponent;

	bool										bIsDuplicateOverlap = false;
	TWeakObjectPtr<class ABaseCharacter>		BaseCharacter;
	TArray<TWeakObjectPtr<class AActor>>		OverlapActors;
};