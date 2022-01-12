// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ExDefines.h"
#include "Components/SceneComponent.h"
#include "Interfaces/LevelTriggerInterface.h"
#include "TriggerComponent.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FTriggerActorWithName
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSoftObjectPtr<class ABaseActor>>		TriggerActors;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName>									Name;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BODYCLEANUP_API UTriggerComponent: public USceneComponent, public ILevelTriggerInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriggerComponent();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SetupTrigger", meta = (ToolTip = "Trigger Action을 정의합니다."))
	ETriggerComponentFromType					TriggerComponentFromType = ETriggerComponentFromType::ParentComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SetupTrigger")
	ETriggerComponentTickType					TriggerComponentTickType = ETriggerComponentTickType::Tick;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SetupTrigger", meta = (EditCondition = "TriggerComponentFromType == ETriggerComponentFromType::ComponentTagName", EditConditionHides, ToolTip = ""))
	FName										ComponentTagName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SetupTrigger", meta = (EditCondition = "TriggerComponentFromType == ETriggerComponentFromType::ComponentName", EditConditionHides, ToolTip = ""))
	FName										ComponentName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SetupTrigger", meta = (EditCondition = "TriggerComponentFromType == ETriggerComponentFromType::Actor", EditConditionHides, ToolTip = ""))
	TArray<TSoftObjectPtr<class ABaseActor>>	TriggerActors;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SetupTrigger", meta = (EditCondition = "TriggerComponentFromType == ETriggerComponentFromType::ActorComponentName || TriggerComponentFromType == ETriggerComponentFromType::ActorComponentTagName", EditConditionHides, ToolTip = ""))
	TArray<FTriggerActorWithName>				TriggerActorWithName;

protected :
	UPROPERTY(VisibleAnywhere)
	TArray<USceneComponent*>					TriggerComponents;

	UPROPERTY(VisibleAnywhere)
	TArray<USceneComponent*>					TriggerTickComponents;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UFUNCTION()
	void __OnTriggerComponentOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void __OnTriggerComponentOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	virtual bool IsOnTrigger() const;
};
