// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CAPAffect.h"
#include "CAPAttributeSet.h"
#include "Components/ActorComponent.h"
#include "CAPTypes.h"
#include "CapabilitySystemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMECAPABILITYSYSTEM_API UCapabilitySystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCapabilitySystemComponent();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UCAPAttributeSet*>		CAPAttributeSets;

	//영향을 준 것
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UCAPAffect*>				OwnCAPAffects;	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public :
	TSoftObjectPtr<UCAPAttributeSet> AddAttribute(TSubclassOf<class UCAPAttributeSet> CAPAttributeSetClass);
	void ApplyGameplayEffectToTarget(class UCAPEffect* CAPEffect, UCapabilitySystemComponent* Target, int32 Ability);
	bool AffectFrom(const FName& AttributeName, ECAPModifierOp ModifierOp, float Value);
	void AffectTo();
};
