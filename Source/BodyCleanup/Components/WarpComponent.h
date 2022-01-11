// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ExDefines.h"
#include "Components/SceneComponent.h"
#include "WarpComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BODYCLEANUP_API UWarpComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWarpComponent();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EWarpType	WarpType = EWarpType::Point;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "WarpType == ELevelType::Point", EditConditionHides, ToolTip = ""))
	TSoftObjectPtr<class ABaseActor>	WarpActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "WarpType == ELevelType::Point", EditConditionHides, ToolTip = ""))
	FName								MarkupComponentName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "WarpType == ELevelType::Level", EditConditionHides, ToolTip = ""))
	FName								LevelName;

	UPROPERTY(VisibleAnywhere)
	TSoftObjectPtr<class UMarkupComponent>	MarkupComponent;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UFUNCTION()
	void __OnParentComponentOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void __OnParentComponentOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


public :
	EWarpType GetWarpType() const;		
};
