// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Interfaces/LevelTriggerInterface.h"
#include "Components/SceneComponent.h"
#include "TriggerSceneComponent.generated.h"


//UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
UCLASS()
class LEVELDESIGNERTOOLS_API UTriggerSceneComponent : public USceneComponent, public ILevelTriggerInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriggerSceneComponent();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|TriggerFrom")
	FLevelTriggerInputFrom		LevelTriggerInputFrom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FLevelTriggerUpdateParam	LevelTriggerUpdateParam;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup|TriggerSettings")
	FLevelTriggerSettings		LevelTriggerSettings;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void SetupTrigger() override; 

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual void GetTriggerLocation(TArray<FVector>& TriggerLocations) override;
	virtual void UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam) override;
	virtual void UpdateAction(const FLevelTriggerUpdateActionParam& LevelTriggerUpdateActionParam) override;
	virtual const FLevelTriggerInputFrom* GetLevelTriggerInputFrom() const override;
	virtual bool IsOnTrigger() const override;
	virtual const FLevelTriggerSettings& GetLevelTriggerSettings() const override;
	virtual bool IsApplyTriggerFromPrimitiveComopnent(UPrimitiveComponent* OtherPrimitiveComponent, AActor* OtherActor, const FHitResult& SweepResult) override;
};
