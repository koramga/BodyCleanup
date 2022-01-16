// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ExDefines.h"
#include "GameFramework/Actor.h"
#include "BaseActor.generated.h"

UCLASS()
class BODYCLEANUP_API ABaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private :
	void __SetEnabledCollisions(USceneComponent* SceneComponent, ECollisionEnabled::Type CollisionEnabledType);
	void __SetCollisionProfileNames(USceneComponent* SceneComponent, const FName& ProfileName);

public :
	void SetEnabledCollisions(bool bIsEnableCollision);
	void SetCollisionProfileNames(const FName& ProfileName);
};
