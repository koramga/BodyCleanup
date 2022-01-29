// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ExDefines.h"
#include "GameFramework/Actor.h"
#include "../Components/Actor/GameActorSettingsComponent.h"
#include "LevelDesignerTools/Actor/LevelToolsActor.h"
#include "AbilitySystemInterface.h"
#include "BodyCleanup/GAS/Ability/BaseGameplayAbility.h"
#include "../GAS/Interface/Actor/GASActorInterface.h"
#include "BaseActor.generated.h"

UCLASS()
class BODYCLEANUP_API ABaseActor : public AActor, public ILevelToolsActor, public IAbilitySystemInterface, public IGASActorInterface
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
	class UAbilitySystemComponent*	AbilitySystemComponent;

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
	void __OnGASAttributeChanged(const FOnAttributeChangeData& Data);

public :
	void SetEnabledCollisions(bool bIsEnableCollision);
	void SetCollisionProfileNames(const FName& ProfileName);
	virtual void AddAbility(const TSubclassOf<class UBaseGameplayAbility>& AbilityToGet, int32 AbilityLevel) override;
	virtual void AddAttributeSet(const TSubclassOf<class UBaseAttributeSet>& AttributeSet) override;
	
public :
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual class ULevelTriggerActorAssist* GetLevelTriggerActorAssist() const override;
};
