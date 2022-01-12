// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ActionComponent.h"
#include "ParentMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BODYCLEANUP_API UParentMovementComponent : public UActionComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UParentMovementComponent();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float	InterpSpeed = 1.f;

	UPROPERTY(VisibleAnywhere)
	FTransform	SourceTransform;

	UPROPERTY(VisibleAnywhere)
	FTransform	DestinationTransform;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool	bIsUpdateLocation = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool	bIsUpdateRotator = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool	bIsUpdateScale = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EParentMovementAction							MovementAction = EParentMovementAction::OnOff;

	UPROPERTY(VisibleAnywhere)
	bool											bIsOn = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSoftObjectPtr<class ABaseActor>>		InteractiveActors;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName											InteractiveComponentTagName;

	UPROPERTY(VisibleAnywhere)
	int32											InteractiveComponentCount;

	UPROPERTY(VisibleAnywhere)
	TSet<TSoftObjectPtr<UPrimitiveComponent>>		InteractiveOverlappedComponents;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private :
	UFUNCTION()
	void __OnInteractiveComponentOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void __OnInteractiveComponentOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
		
private :
	void __UpdateToDestination(float DeltaTime);
	void __UpdateToSource(float DeltaTime);
	bool __CheckIsOn();

public :
	bool IsOn() const;
	const TArray<TSoftObjectPtr<class ABaseActor>>& GetInteractiveActors() const;
};
