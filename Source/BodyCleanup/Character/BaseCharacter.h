// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ExDefines.h"
#include "GameFramework/Character.h"
#include "../Components/Actor/GameActorSettingsComponent.h"
#include "LevelDesignerTools/Actor/LevelToolsActorInterface.h"
#include "AbilitySystemInterface.h"
#include "../GAS/Interface/Actor/GASActorInterface.h"
#include "BodyCleanup/GAS/Ability/BaseGameplayAbility.h"
#include "BaseCharacter.generated.h"

UCLASS()
class BODYCLEANUP_API ABaseCharacter : public ACharacter, public ILevelToolsActorInterface, public IAbilitySystemInterface, public IGASActorInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected :
	UPROPERTY(VisibleAnywhere)
	class UBaseAnimInstance* BaseAnimInstance;

	UPROPERTY(VisibleAnywhere)
	FName BodyCollisionProfileName;

	UPROPERTY(VisibleAnywhere)
	AController* BaseController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ULevelTriggerActorAssist*		LevelTriggerActorAssist;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UAbilitySystemComponent*	AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UGameActorSettingsComponent*	GameActorSettingsComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UWidgetComponent*			SpeechBubbleWidgetComponent;

	UPROPERTY(VisibleAnywhere)
	bool bIsDeath = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public :
	virtual void UpdateAnimationType(EAnimationType AnimationType, EAnimationType BeforeAnimationType);

private :
	void __OnGASAttributeChanged(const FOnAttributeChangeData& Data);

public :
	void SetEnableCapsuleCollision(bool bIsEnable);
	void SetAnimationType(EAnimationType AnimationType);
	EAnimationType GetAnimationType() const;
	virtual void AddAbility(const FGameplayAbilitySpec& GameplayAbilitySpec) override;
	virtual void AddAttributeSet(const TSubclassOf<class UBaseAttributeSet>& AttributeSet) override;
	virtual bool IsDeath() const override;

public :
	virtual void SetTextToSpeechBubble(const FString& Text);
	virtual void SetVisibleSpeechBubble(bool bIsVisible);
	
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual class ULevelTriggerActorAssist* GetLevelTriggerActorAssist() const override;
};