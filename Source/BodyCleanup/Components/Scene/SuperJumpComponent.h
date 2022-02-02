// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BodyCleanup/Character/BaseCharacter.h"
#include "Components/BoxComponent.h"
#include "SuperJumpComponent.generated.h"

DECLARE_DELEGATE_OneParam(FDoSuperJump, AActor*);

/**
 * 
 */
UCLASS(ClassGroup = (Characters), meta = (BlueprintSpawnableComponent))
class BODYCLEANUP_API USuperJumpComponent : public UBoxComponent
{
	GENERATED_BODY()

public :
	USuperJumpComponent();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|SuperJumpComponent")
	float SuperJumpVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|SuperJumpComponent")
	TArray<TSubclassOf<AActor>>	AllowSuperJumpCharacterClasses;

	FDoSuperJump	CallbackDoSuperJump;
	
private :
	UPROPERTY()
	TArray<AActor*>	OverlapActors;

protected:
	virtual void BeginPlay() override;

public :
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private :
	bool __IsAllowActor(AActor* Actor);
	
	UFUNCTION()
	void __OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void __OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public :
	template <typename T>
	void SetCallbackOverlapSuperJump(T* pObj, void (T::* pFunc)(AActor*))
	{
		CallbackDoSuperJump.BindUObject(pObj, pFunc);
	}
};
