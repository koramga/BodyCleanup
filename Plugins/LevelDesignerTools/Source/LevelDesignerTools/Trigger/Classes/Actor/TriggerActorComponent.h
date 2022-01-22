// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Interfaces/LevelTriggerInterface.h"
#include "Components/ActorComponent.h"
#include "TriggerActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEVELDESIGNERTOOLS_API UTriggerActorComponent : public UActorComponent, public ILevelTriggerInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriggerActorComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|TriggerInput")
	FLevelTriggerInputFrom	LevelTriggerInputFrom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool	bIsOnTrigger = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(bool bInputIsOnTrigger) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual void GetTriggerLocation(TArray<FVector>& TriggerLocations) override;
	virtual const FLevelTriggerInputFrom* GetLevelTriggerInputFrom() const override;
	virtual bool IsOnTrigger() const;
};