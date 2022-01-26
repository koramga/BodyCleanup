// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Interfaces/LevelTriggerInterface.h"
#include "Components/ActorComponent.h"
#include "TriggerActorComponent.generated.h"


UCLASS()
class LEVELDESIGNERTOOLS_API UTriggerActorComponent : public UActorComponent, public ILevelTriggerInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriggerActorComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|TriggerFrom")
	FLevelTriggerInputFrom	LevelTriggerInputFrom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FLevelTriggerUpdateParam	LevelTriggerUpdateParam;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FLevelTriggerSettings		LevelTriggerSettings;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual void GetTriggerLocation(TArray<FVector>& TriggerLocations) override;
	virtual const FLevelTriggerInputFrom* GetLevelTriggerInputFrom() const override;
	virtual bool IsOnTrigger() const;
	virtual const FLevelTriggerSettings& GetLevelTriggerSettings() const override;
	virtual void UpdateAction(const FLevelTriggerUpdateActionParam& LevelTriggerUpdateActionParam) override;
	virtual bool IsApplyTriggerFromPrimitiveComopnent(UPrimitiveComponent* OtherPrimitiveComponent, AActor* OtherActor, const FHitResult& SweepResult) override;
};
