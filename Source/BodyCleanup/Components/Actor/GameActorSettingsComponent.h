// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../ExDefines.h"
#include "Components/ActorComponent.h"
#include "GameActorSettingsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BODYCLEANUP_API UGameActorSettingsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGameActorSettingsComponent();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup")
	EWeightType WeightType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<class UCAPAttributeSet>>	BaseAttributeSetClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<class UCAPAbility>>		BaseAbilityClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName										ActorName;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public :
	EWeightType GetWeightType() const;
	FName GetActorName() const;
	
public :
	void SetWeightType(EWeightType InputWeightType);	
};