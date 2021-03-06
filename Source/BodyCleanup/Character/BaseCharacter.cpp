// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Animation/BaseAnimInstance.h"
#include "AbilitySystemComponent.h"
#include "Components/Widget.h"
#include "Components/WidgetComponent.h"
#include "../UI/Script/BubbleScriptUserWidget.h"
#include "BodyCleanup/Actor/Modular/ProjectileModularActor.h"
#include "BodyCleanup/Actor/Modular/WeaponModularActor.h"
#include "BodyCleanup/Game/GameInstance/BaseGameInstance.h"
#include "BodyCleanup/Game/GameMode/BaseGameModeBase.h"
#include "BodyCleanup/GCS/Utility/GameGCSFunctionLibrary.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GameActorSettingsComponent = CreateDefaultSubobject<UGameActorSettingsComponent>(TEXT("GameActorSettingsComponent"));
	CapabilitySystemComponent = CreateDefaultSubobject<UBaseCapabilitySystemComponent>("CapabilitySystemComponent");
	SpeechBubbleWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("SpeechBubbleWidget");

	SpeechBubbleWidgetComponent->SetupAttachment(GetMesh());
	SpeechBubbleWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);

	MoveBlendRatio = 0.5f;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	//Super::BeginPlay를 호출하면 Actor의 Component의 BeginPlay가 진행이 된다. Component에서 호출해야할 특정 Object들은 Super::BeginPlay이전에 생성해야 한다.
	LevelTriggerActorAssist = NewObject<ULevelTriggerActorAssist>();
	
	Super::BeginPlay();
	
	BaseAnimInstance = Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance());

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	SetHiddenInGameSpeechBubble(true);
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	BaseController = NewController;
}

void ABaseCharacter::UnPossessed()
{
	Super::UnPossessed();

	BaseController = nullptr;
}

void ABaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	FVector Forward = GetActorForwardVector();
	FVector Velocity = Movement->Velocity;
	float Speed = Velocity.Size();
	float Angle = 0.f;

	if (Movement->IsMovingOnGround())
	{
		if (Speed > 0)
		{
			//https://amored8701.tistory.com/132

			//if (IsLockOn())
			//{
			//	FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), LockOnBaseCharacter->GetActorLocation());
			//
			//	SetActorRotation(Rotator.Quaternion());
			//
			//	vForward = Rotator.RotateVector(FVector::ForwardVector);
			//}

			Forward.Z = 0.f;
			Velocity.Z = 0.f;

			Forward.Normalize();
			Velocity.Normalize();

			float fDot = FVector::DotProduct(Forward, Velocity);
			float fAcosAngle = FMath::Acos(fDot);
			float fAngle = FMath::RadiansToDegrees(fAcosAngle);

			FVector vCross = FVector::CrossProduct(Forward, Velocity);

			if (vCross.Z < 0)
			{
				//fAngle *= -1.f;
				fAngle = 360 - fAngle;
			}

			//Angle = fAngle + QUARTER_VIEW_ANGLE;

			//UE_LOG(LogTemp, Display, TEXT("Angle : %.2f"), fAngle);
		}

		if (IsValid(BaseAnimInstance))
		{
			//if (EMoveType::Run == MoveType)
			//{
			//	Ratio = 1.f;
			//}
			//else if (EMoveType::Sprint == MoveType)
			//{
			//	Ratio = 1.5f;
			//}

			if (IsValid(BaseAnimInstance))
			{
				BaseAnimInstance->SetMoveBlendSpeed(Speed / GetCharacterMovement()->GetMaxSpeed() * MoveBlendRatio);
				BaseAnimInstance->SetMoveBlendAngle(Angle);
			}
		}
	}

	if (IsValid(BaseAnimInstance))
	{
		BaseAnimInstance->SetMovementMode(GetCharacterMovement()->MovementMode);
	}

	//if(CharacterHitInformation.MaterialTickTime >= 0.f)
	//{
	//	if(CharacterHitInformation.MaterialTickTime > CharacterHitInformation.MaterialUpdateKeepTime)
	//	{
	//		//경과 종료!
	//		CharacterHitInformation.MaterialTickTime = -1.f;
//
	//		for(int i = 0; i < CharacterHitInformation.MaterialInstanceVariables.Num(); ++i)
	//		{
	//			const FMaterialInstanceVariable& MaterialInstanceVariable = CharacterHitInformation.MaterialInstanceVariables[i];
	//			MaterialInstanceVariable.SetMaterialInstanceParameter(GetMesh(), CharacterHitInformation.BackupMetaVariables[i]);
	//		}
	//		
	//		CharacterHitInformation.BackupMetaVariables.Reset();
	//	}
	//	
	//	if(CharacterHitInformation.MaterialTickTime == 0.f
	//		&& CharacterHitInformation.BackupMetaVariables.Num() == 0)
	//	{
	//		//최초 구간!
	//		
	//		for(const FMaterialInstanceVariable& MaterialInstanceVariable : CharacterHitInformation.MaterialInstanceVariables)
	//		{
	//			CharacterHitInformation.BackupMetaVariables.Add(MaterialInstanceVariable.GetMaterialInstanceParameter(GetMesh()));
	//			MaterialInstanceVariable.SetMaterialInstanceParameter(GetMesh());
	//		}
	//	}
	//	
//
	//	CharacterHitInformation.MaterialTickTime += DeltaTime;
	//}
}

void ABaseCharacter::UpdateAnimationType(EAnimationType AnimationType, EAnimationType BeforeAnimationType)
{

}

void ABaseCharacter::LeftAnimationType(EAnimationType AnimationType)
{
	if(IsValid(CapabilitySystemComponent))
	{
		CapabilitySystemComponent->LeftAnimationType(AnimationType);
	}
}

void ABaseCharacter::__OnGCSAttributeChanged(const FOnCAPAttributeChangeData& Data)
{
	UBaseGameInstance* BaseGameInstance = Cast<UBaseGameInstance>(GetWorld()->GetAuthGameMode()->GetGameInstance());

	if(IsValid(BaseGameInstance))
	{
		FName StatTypeName = BaseGameInstance->GetStatTypeToName(EGameStatType::HP);
		
		if(StatTypeName == Data.AttributeName)
		{
			UE_LOG(LogTemp, Display, TEXT("<%s> HP : %.2f : %.2f"), *GetName(), Data.OldValue, Data.NewValue);
			
			if(Data.NewValue <= 0.f)
			{
				UpdateDeath(true);
			}

			OnHit(Data);
		}
	}
}

void ABaseCharacter::UpdateDeath(bool bInIsDeath)
{
	LevelTriggerActorAssist->SetLevelTriggerState(ELevelTriggerActorState::Death, true);
	bIsDeath = bInIsDeath;	
}

void ABaseCharacter::OnHit(const FOnCAPAttributeChangeData& Data)
{
	LevelTriggerActorAssist->SetLevelTriggerStateOnce(ELevelTriggerActorState::Hit);
	//CharacterHitInformation.MaterialTickTime = 0.f;
}

void ABaseCharacter::SetAnimationType(EAnimationType AnimationType, UAnimMontage* Montage)
{
	if (IsValid(BaseAnimInstance))
	{
		BaseAnimInstance->SetAnimationType(AnimationType);

		if(IsValid(Montage))
		{			
			BaseAnimInstance->SetAnimationMontage(Montage);
		}
	}	
}

bool ABaseCharacter::CanUpdateAnimationType(EAnimationType InAnimationType) const
{
	if (IsValid(BaseAnimInstance))
	{
		return BaseAnimInstance->CanUpdateAnimationType(InAnimationType);
	}

	return false;
}

bool ABaseCharacter::CanMove() const
{
	if(IsValid(BaseAnimInstance))
	{
		return BaseAnimInstance->CanMove();
	}

	return false;
}

bool ABaseCharacter::IsPlayingMontage(UAnimMontage* AnimMontage)
{
	if (IsValid(BaseAnimInstance))
	{
		return BaseAnimInstance->IsPlayingMontage(AnimMontage);
	}

	return false;	
}

bool ABaseCharacter::IsActivateMontage(UAnimMontage* AnimMontage)
{	
	if (IsValid(BaseAnimInstance))
	{
		return BaseAnimInstance->IsActivateMontage(AnimMontage);
	}

	return false;
}

void ABaseCharacter::SetStopMontage(UAnimMontage* AnimMontage)
{
	if(IsValid(BaseAnimInstance))
	{
		BaseAnimInstance->SetStopAnimationMontage(AnimMontage);
	}
}

EAnimationType ABaseCharacter::GetAnimationType() const
{
	if (IsValid(BaseAnimInstance))
	{
		return BaseAnimInstance->GetAnimationType();
	}

	return EAnimationType::Idle;
}

void ABaseCharacter::AddAttributeSet(TSubclassOf<UCAPAttributeSet> CAPAttributeSetClass)
{
	if(IsValid(CapabilitySystemComponent))
	{
		TSoftObjectPtr<UCAPAttributeSet> CAPAttributeSet = CapabilitySystemComponent->AddAttribute(CAPAttributeSetClass);

		if(CAPAttributeSet.IsValid())
		{
			CAPAttributeSet->SetCallbackOnAttributeChanged(this, &ABaseCharacter::__OnGCSAttributeChanged);
		}
	}
}

void ABaseCharacter::AddAbility(TSubclassOf<UCAPAbility> CAPAbilityClass)
{
	if(IsValid(CapabilitySystemComponent))
	{
		TSoftObjectPtr<UCAPAbility> CAPAbility = CapabilitySystemComponent->AddAbility(CAPAbilityClass, 0);

		if(CAPAbility.IsValid())
		{
			
		}
	}
}

void ABaseCharacter::RemoveAbility(TSubclassOf<UCAPAbility> CAPAbilityClass)
{
	if(IsValid(CapabilitySystemComponent))
	{
		CapabilitySystemComponent->RemoveAbility(CAPAbilityClass);
	}	
}

bool ABaseCharacter::IsDeath() const
{
	return bIsDeath;
}

void ABaseCharacter::SetDestroyFromTrigger()
{
	UpdateDeath(true);
}

void ABaseCharacter::SetEnableAttack(bool bIsEnableAttack, const TArray<FString>& ComponentNames)
{
}

void ABaseCharacter::SetTextToSpeechBubble(const FString& Text)
{
	UBubbleScriptUserWidget* BubbleScriptUserWidget = Cast<UBubbleScriptUserWidget>(SpeechBubbleWidgetComponent->GetWidget());

	if(IsValid(BubbleScriptUserWidget))
	{
		BubbleScriptUserWidget->SetText(Text);
	}
}

void ABaseCharacter::SetHiddenInGameSpeechBubble(bool bIsHidden)
{
	UBaseUserWidget* BaseUserWidget = Cast<UBaseUserWidget>(SpeechBubbleWidgetComponent->GetWidget());

	if(IsValid(BaseUserWidget))
	{
		BaseUserWidget->SetHiddenInGame(bIsHidden);
	}	
}

UCapabilitySystemComponent* ABaseCharacter::GetCapabilitySystemComponent() const
{
	return CapabilitySystemComponent;
}

//UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
//{
//	return AbilitySystemComponent;
//}

ULevelTriggerActorAssist* ABaseCharacter::GetLevelTriggerActorAssist() const
{
	return LevelTriggerActorAssist;
}

FBTAbilityInfo ABaseCharacter::GetAbilityInfoByTag(const FGameplayTag& Tag) const
{
	FBTAbilityInfo AbilityInfo;

	AbilityInfo.CanActivate = CapabilitySystemComponent->CanActivateAbilityByTag(Tag);
	AbilityInfo.IsActivate = CapabilitySystemComponent->IsActivateAbilityByTag(Tag);

	UBaseCapabilitySystemComponent* BaseCapabilitySystemComponent = Cast<UBaseCapabilitySystemComponent>(CapabilitySystemComponent);

	if (IsValid(BaseCapabilitySystemComponent))
	{
		AbilityInfo.Range = BaseCapabilitySystemComponent->GetAbilityRangeByTag(Tag);
	}
	else
	{
		AbilityInfo.Range = 0.f;
	}

	return AbilityInfo;
}

bool ABaseCharacter::ActivateAbilityByTag(const FGameplayTag& Tag)
{
	if(IsValid(CapabilitySystemComponent))
	{
		return CapabilitySystemComponent->TryActivateAbilityByTag(Tag);
	}
	
	return false;
}

bool ABaseCharacter::DeActivateAbilityByTag(const FGameplayTag& Tag)
{
	if(IsValid(CapabilitySystemComponent))
	{
		return CapabilitySystemComponent->TryDeActivateAbilityByTag(Tag);
	}
	
	return false;
}

EBTPatrolType ABaseCharacter::GetPatrolType() const
{
	return EBTPatrolType::None;
}

IBTPatrolActorInterface* ABaseCharacter::GetPatrolActorInterface() const
{
	return nullptr;
}

FBTPatrolInfo ABaseCharacter::GetPatrolInfo() const
{
	return FBTPatrolInfo();
}

void ABaseCharacter::SetNextPatrol()
{
}

void ABaseCharacter::OnChangeOfStateFromNotify(FAnimNotify_ChangeOfStateStruct& InNotifyStruct)
{
	if(EAnimNotify_ChangeOfStateType::EnableBeDamaged == InNotifyStruct.Type)
	{
		if(IsValid(CapabilitySystemComponent))
		{
			if(InNotifyStruct.bIsEnabled)
			{
				//상태 면역 X (일반)
				CapabilitySystemComponent->RemoveBlockGameplayTag(UGameGCSFunctionLibrary::DamageRootTag);
			}
			else
			{
				//상태 면역 (무적)
				CapabilitySystemComponent->AddBlockGameplayTag(UGameGCSFunctionLibrary::DamageRootTag);
			}
		}
	}
}

void ABaseCharacter::OnCreateActorFromNotify(TWeakObjectPtr<AActor> Actor)
{
	if(IsValid(CapabilitySystemComponent)
		&& CapabilitySystemComponent->GetActivateAbility().IsValid())
	{
		if(Actor->IsA(AProjectileModularActor::StaticClass()))
		{
			AProjectileModularActor* ProjectileModularActor = Cast<AProjectileModularActor>(Actor);
			
			ProjectileModularActor->SetOwner(this);
			ProjectileModularActor->AddIgnoreActor(this);
			ProjectileModularActor->AddAbility(CapabilitySystemComponent->GetActivateAbility()->GetClass());
			ProjectileModularActor->SetEnableCollision(true);
		}		
	}
}

void ABaseCharacter::SetFocusOn(bool bIsFocusOn)
{
	if(true == bIsFocusOn)
	{
		SetActorTickEnabled(true);
	}
	else
	{
		SetActorTickEnabled(false);

		//이동했을 경우, 이동을 멈추게 만든다.
		BaseAnimInstance->SetMoveBlendSpeed(0.f);
	}
}
