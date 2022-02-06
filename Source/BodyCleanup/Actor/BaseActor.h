// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ExDefines.h"
#include "GameFramework/Actor.h"
#include "../Components/Actor/GameActorSettingsComponent.h"
#include "LevelDesignerTools/Actor/LevelToolsActorInterface.h"
#include "BodyCleanup/GAS/Ability/BaseGameplayAbility.h"
#include "CapabilitySystemInterface.h"
#include "../GCS/Interface/GCSActorInterface.h"
#include "../GCS/Component/BaseCapabilitySystemComponent.h"
#include "BaseActor.generated.h"

UCLASS()
class BODYCLEANUP_API ABaseActor : public AActor, public ILevelToolsActorInterface, public ICapabilitySystemInterface, public IGCSActorInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseActor();

protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ULevelTriggerActorAssist*		LevelTriggerActorAssist;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UGameActorSettingsComponent*	GameActorSettingsComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBaseCapabilitySystemComponent* CapabilitySystemComponent;
	
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//class UAbilitySystemComponent*	AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsDeath = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private :
	void __SetEnabledCollisions(USceneComponent* SceneComponent, ECollisionEnabled::Type CollisionEnabledType);
	void __SetCollisionProfileNames(USceneComponent* SceneComponent, const FName& ProfileName);
	void __OnGCSAttributeChanged(const FOnCAPAttributeChangeData& Data);

public :
	void SetEnabledCollisions(bool bIsEnableCollision);
	void SetCollisionProfileNames(const FName& ProfileName);
	virtual void AddAttributeSet(TSubclassOf<class UCAPAttributeSet> CAPAttributeSetClass) override;
	virtual void AddAbility(TSubclassOf<class UCAPAbility> CAPAbilityClass) override;
	virtual bool IsDeath() const override;
	//virtual void AddAbility(const FGameplayAbilitySpec& GameplayAbilitySpec) override;
	//virtual void AddAttributeSet(const TSubclassOf<class UBaseAttributeSet>& AttributeSet) override;
	 
	
public :
	virtual UCapabilitySystemComponent* GetCapabilitySystemComponent() const override;
	virtual class ULevelTriggerActorAssist* GetLevelTriggerActorAssist() const override;
};
