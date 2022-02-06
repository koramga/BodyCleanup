// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Animation/BaseAnimInstance.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "../GAS/Ability/BaseGameplayAbility.h"
#include "../GAS/AttributeSet/BaseAttributeSet.h"
#include "Components/Widget.h"
#include "Components/WidgetComponent.h"
#include "../UI/Script/BubbleScriptUserWidget.h"
#include "BodyCleanup/Game/GameInstance/BaseGameInstance.h"
#include "BodyCleanup/Game/GameMode/BaseGameModeBase.h"

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
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	//Super::BeginPlay를 호출하면 Actor의 Component의 BeginPlay가 진행이 된다. Component에서 호출해야할 특정 Object들은 Super::BeginPlay이전에 생성해야 한다.
	LevelTriggerActorAssist = NewObject<ULevelTriggerActorAssist>();
	
	Super::BeginPlay();
	
	BaseAnimInstance = Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance());

	BodyCollisionProfileName = GetCapsuleComponent()->GetCollisionProfileName();
	
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
			float Ratio = 0.5f;

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
				BaseAnimInstance->SetMoveBlendSpeed(Speed / GetCharacterMovement()->GetMaxSpeed() * Ratio);
				BaseAnimInstance->SetMoveBlendAngle(Angle);
			}
		}
	}

	if (IsValid(BaseAnimInstance))
	{
		BaseAnimInstance->SetMovementMode(GetCharacterMovement()->MovementMode);
	}
}

void ABaseCharacter::UpdateAnimationType(EAnimationType AnimationType, EAnimationType BeforeAnimationType)
{
}

void ABaseCharacter::__OnGCSAttributeChanged(const FOnCAPAttributeChangeData& Data)
{
	UBaseGameInstance* BaseGameInstance = Cast<UBaseGameInstance>(GetWorld()->GetAuthGameMode()->GetGameInstance());

	if(IsValid(BaseGameInstance))
	{
		FName StatTypeName = BaseGameInstance->GetStatTypeToName(EGameStatType::HP);
		
		if(StatTypeName == Data.AttributeName)
		{
			if(Data.NewValue <= 0.f)
			{
				if(IsValid(BaseAnimInstance))
				{
					BaseAnimInstance->SetAnimationType(EAnimationType::Death);
				}
				LevelTriggerActorAssist->SetLevelTriggerState(ELevelTriggerActorState::Death, true);
				bIsDeath = true;
			}
		}
	}
}

//void ABaseCharacter::__OnGASAttributeChanged(const FOnAttributeChangeData& Data)
//{	
//	TArray<FGameplayAttribute> Attributes;
//	
//	AbilitySystemComponent->GetAllAttributes(Attributes);
//
//	for(FGameplayAttribute& Attribute : Attributes)
//	{
//		if(Data.Attribute == Attribute)
//		{
//			if(TEXT("Health") == Attribute.AttributeName)
//			{
//				if(Data.NewValue <= 0.f)
//				{
//					LevelTriggerActorAssist->SetLevelTriggerState(ELevelTriggerActorState::Death, true);
//					bIsDeath = true;
//				}
//				 
//				UE_LOG(LogTemp, Display, TEXT("koramga %.2f -> %.2f"), Data.OldValue, Data.NewValue);
//			}
//		}
//	}
//}

void ABaseCharacter::SetEnableCapsuleCollision(bool bIsEnable)
{
	if (false == bIsEnable)
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	}
	else
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
		GetCapsuleComponent()->SetCollisionProfileName(BodyCollisionProfileName);
	}
}

void ABaseCharacter::SetAnimationType(EAnimationType AnimationType)
{
	if (IsValid(BaseAnimInstance))
	{
		BaseAnimInstance->SetAnimationType(AnimationType);
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

//void ABaseCharacter::AddAbility(const FGameplayAbilitySpec& GameplayAbilitySpec)
//{
//	if (IsValid(AbilitySystemComponent))
//	{
//		if (HasAuthority() && IsValid(GameplayAbilitySpec.Ability))
//		{
//			FGameplayAbilitySpecHandle GameplayAbilitySpecHandle = AbilitySystemComponent->GiveAbility(GameplayAbilitySpec);
//		}
//
//		AbilitySystemComponent->InitAbilityActorInfo(this, this);
//	}
//}

//void ABaseCharacter::AddAttributeSet(const TSubclassOf<UBaseAttributeSet>& AttributeSet)
//{
//	UBaseAttributeSet* BaseAttribute = NewObject<UBaseAttributeSet>(this, AttributeSet);
//	
//	AbilitySystemComponent->AddAttributeSetSubobject(BaseAttribute);
//
//	TArray<FGameplayAttribute> Attributes;
//	BaseAttribute->GetAttributes(Attributes);
//
//	for(const FGameplayAttribute& Attribute : Attributes)
//	{
//		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &ABaseCharacter::__OnGASAttributeChanged);
//	}
//}

bool ABaseCharacter::IsDeath() const
{
	return bIsDeath;
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