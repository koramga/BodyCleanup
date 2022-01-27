// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ExDefines.h"
#include "GameFramework/Actor.h"
#include "../Components/Actor/GameActorSettingsComponent.h"
#include "LevelDesignerTools/Actor/LevelToolsActor.h"
#include "AbilitySystemInterface.h"
#include "BaseActor.generated.h"

UCLASS()
class BODYCLEANUP_API ABaseActor : public AActor, public ILevelToolsActor, public IAbilitySystemInterface
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

public :
	void SetEnabledCollisions(bool bIsEnableCollision);
	void SetCollisionProfileNames(const FName& ProfileName);

public :
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual class ULevelTriggerActorAssist* GetLevelTriggerActorAssist() const override;
};
