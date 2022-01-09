// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ExDefines.h"
#include "Components/ActorComponent.h"
#include "LevelComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BODYCLEANUP_API ULevelComponent : public UActorComponent
{
	GENERATED_BODY()

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ELevelType		LevelType = ELevelType::Object;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditCondition = "LevelType == ELevelType::Junk", EditConditionHides,ToolTip="one cube per four junk"))
	int32			JunkValue = 1;

public:	
	// Sets default values for this component's properties
	ULevelComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public :
	void SetLevelType(ELevelType InputLevelType);
	
public :
	ELevelType GetLevelType() const;
};
