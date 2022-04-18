// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BaseActor.h"

#if WITH_EDITOR
#include "Engine/Classes/Components/LineBatchComponent.h"
#endif // WITH_EDITOR

#include "BaseLevelActor.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API ABaseLevelActor : public ABaseActor
{
	GENERATED_BODY()

public :
	ABaseLevelActor();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class ULevelComponent* LevelComponent;

#if WITH_EDITOR

	//UPROPERTY(EditInstanceOnly, Category = "DrawData")
	//ULineBatchComponent* LineBatchComponent;

	bool	bIsSelected = false;

#endif

#if WITH_EDITOR

protected :	
	virtual void PreEditChange(FProperty* PropertyThatWillChange) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostEditMove(bool bFinished) override;
	//UFUNCTION()
	//void OnChangeSelectObject(UObject* SelectionObj);

	void DisplayLinkConnection(bool bShow = true);

#endif

protected :

#if WITH_EDITOR
	void GetComponentByLinkConnect(TArray<FBatchedLine>& BatchLines);
#endif

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

//public :
//	void AddBatchLine(const FVector& End);
};
