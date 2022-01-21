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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|TriggerInput")
	FLevelTriggerInputFrom	LevelTriggerInputFrom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool	bIsOnTrigger = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual void GetTriggerLocation(TArray<FVector>& TriggerLocations) override;
	virtual void UpdateTrigger(bool bInputIsOnTrigger) override;
	virtual const FLevelTriggerInputFrom* GetLevelTriggerInputFrom() const override;
	virtual bool IsOnTrigger() const override;
};
