// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ExDefines.h"
#include "GameFramework/Character.h"
#include "../Components/Actor/GameActorSettingsComponent.h"
#include "LevelDesignerTools/Actor/LevelToolsActorInterface.h"
#include "CapabilitySystemInterface.h"
#include "../GCS/Interface/GCSActorInterface.h"
#include "../GAS/Ability/BaseGameplayAbility.h"
#include "../BT/Interface/BTCharacterInterface.h"
#include "../GCS/Component/BaseCapabilitySystemComponent.h"
#include "BaseCharacter.generated.h"

UCLASS()
class BODYCLEANUP_API ABaseCharacter : public ACharacter, public ILevelToolsActorInterface, public ICapabilitySystemInterface, public IBTCharacterInterface, public IGCSActorInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	UPROPERTY(VisibleAnywhere)
	class UBaseAnimInstance* BaseAnimInstance;

	UPROPERTY(VisibleAnywhere)
	FName BodyCollisionProfileName;

	UPROPERTY(VisibleAnywhere)
	AController* BaseController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ULevelTriggerActorAssist*		LevelTriggerActorAssist;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBaseCapabilitySystemComponent*		CapabilitySystemComponent;

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
	void __OnGCSAttributeChanged(const FOnCAPAttributeChangeData& Data);

public :
	void SetEnableCapsuleCollision(bool bIsEnable);
	void SetAnimationType(EAnimationType AnimationType, UAnimMontage* AnimMontage = nullptr);
	bool IsPlayingMontage(UAnimMontage* AnimMontage);
	bool IsActivateMontage(UAnimMontage* AnimMontage);
	void SetStopMontage(UAnimMontage* AnimMontage);
	EAnimationType GetAnimationType() const;
	//virtual void AddAbility(const FGameplayAbilitySpec& GameplayAbilitySpec) override;
	virtual void AddAttributeSet(TSubclassOf<class UCAPAttributeSet> CAPAttributeSetClass) override;
	virtual bool IsDeath() const override;
	
public :
	virtual void SetTextToSpeechBubble(const FString& Text);
	virtual void SetHiddenInGameSpeechBubble(bool bIsHidden);
	
public:
	virtual UCapabilitySystemComponent* GetCapabilitySystemComponent() const override;
	virtual class ULevelTriggerActorAssist* GetLevelTriggerActorAssist() const override;
};