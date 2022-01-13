// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ActionComponent.h"
#include "WarpComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BODYCLEANUP_API UWarpComponent : public UActionComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWarpComponent();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EWarpType	WarpType = EWarpType::Location;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "WarpType == EWarpType::Location", EditConditionHides, ToolTip = ""))
	TSoftObjectPtr<AActor>				WarpActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "WarpType == EWarpType::Location", EditConditionHides, ToolTip = ""))
	FName								MarkupName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "WarpType == EWarpType::Level", EditConditionHides, ToolTip = ""))
	FName								LevelName;

	UPROPERTY(VisibleAnywhere)
	TSoftObjectPtr<USceneComponent>	MarkupComponent;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public :
	EWarpType GetWarpType() const;		
	TSoftObjectPtr<USceneComponent> GetMarkupComponent() const;
	TSoftObjectPtr<AActor> GetWarpActor() const;
	TSoftObjectPtr<USceneComponent> FindMarkupComponent() const; 
	FVector GetWarpLocation() const;
};
