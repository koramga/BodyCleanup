// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ExDefines.h"
#include "GameFramework/Character.h"
#include "../Components/Actor/GameActorSettingsComponent.h"
#include "LevelDesignerTools/Actor/LevelToolsActorInterface.h"
#include "CapabilitySystemInterface.h"
#include "../GCS/Interface/GCSActorInterface.h"
#include "../GAS/Ability/BaseGameplayAbility.h"
#include "Interface/BTCharacterInterface.h"
#include "../GCS/Component/BaseCapabilitySystemComponent.h"
#include "AnimationDesignerTools/Public/Interface/Actor/AnimationToolsActorInterface.h"
#include "MetaTools/VariableGroup/MaterialInstanceVariable.h"
#include "BaseCharacter.generated.h"

UCLASS()
class BODYCLEANUP_API ABaseCharacter : public ACharacter, public ILevelToolsActorInterface, public ICapabilitySystemInterface, public IBTCharacterInterface, public IGCSActorInterface, public IAnimationToolsActorInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	UPROPERTY(VisibleAnywhere)
	class UBaseAnimInstance* BaseAnimInstance;

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

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|Hit")
	//FCharacterHitInformation		CharacterHitInformation;

	UPROPERTY(VisibleAnywhere)
	bool bIsDeath = false;

	float MoveBlendRatio;

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
	virtual void LeftAnimationType(EAnimationType AnimationType);

private :
	void __OnGCSAttributeChanged(const FOnCAPAttributeChangeData& Data);

protected:
	virtual void UpdateDeath(bool bInIsDeath);
	virtual void OnHit(const FOnCAPAttributeChangeData& Data);

public :
	void SetAnimationType(EAnimationType AnimationType, UAnimMontage* AnimMontage = nullptr);
	bool CanUpdateAnimationType(EAnimationType InAnimationType) const;
	bool CanMove() const;
	bool IsPlayingMontage(UAnimMontage* AnimMontage);
	bool IsActivateMontage(UAnimMontage* AnimMontage);
	void SetStopMontage(UAnimMontage* AnimMontage);
	EAnimationType GetAnimationType() const;
	//virtual void AddAbility(const FGameplayAbilitySpec& GameplayAbilitySpec) override;
	virtual void AddAttributeSet(TSubclassOf<class UCAPAttributeSet> CAPAttributeSetClass) override;
	virtual void AddAbility(TSubclassOf<class UCAPAbility> CAPAbilityClass) override;
	virtual void RemoveAbility(TSubclassOf<class UCAPAbility> CAPAbilityClass) override;
	virtual bool IsDeath() const override;
	virtual void SetDestroyFromTrigger() override;
	virtual void SetEnableAttack(bool bIsEnableAttack, const TArray<FString>& ComponentNames);
	
public :
	virtual void SetTextToSpeechBubble(const FString& Text);
	virtual void SetHiddenInGameSpeechBubble(bool bIsHidden);
	
public:
	virtual UCapabilitySystemComponent* GetCapabilitySystemComponent() const override;
	virtual class ULevelTriggerActorAssist* GetLevelTriggerActorAssist() const override;
	virtual FBTAbilityInfo GetAbilityInfoByTag(const struct FGameplayTag& Tag) const override;
	virtual bool ActivateAbilityByTag(const FGameplayTag& Tag) override;
	virtual bool DeActivateAbilityByTag(const struct FGameplayTag& Tag) override;
	virtual EBTPatrolType GetPatrolType() const override;
	virtual class IBTPatrolActorInterface* GetPatrolActorInterface() const override;
	virtual FBTPatrolInfo GetPatrolInfo() const override;
	virtual void SetNextPatrol() override;
	virtual void OnChangeOfStateFromNotify(FAnimNotify_ChangeOfStateStruct& InNotifyStruct) override;
	virtual void OnCreateActorFromNotify(TWeakObjectPtr<AActor> Actor) override;
	virtual void SetFocusOn(bool bIsFocusOn);
};