// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActor.h"
#include "AbilitySystemComponent.h"
#include "../GAS/Effect/BaseGameplayEffect.h"
#include "../GAS/AttributeSet/BaseAttributeSet.h"
#include  "../GAS/AttributeSet/BaseStatsAttributeSet.h"

// Sets default values
ABaseActor::ABaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GameActorSettingsComponent = CreateDefaultSubobject<UGameActorSettingsComponent>(TEXT("GameActorSettingsComponent"));
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
}

// Called when the game starts or when spawned
void ABaseActor::BeginPlay()
{
	//Super::BeginPlay를 호출하면 Actor의 Component의 BeginPlay가 진행이 된다. Component에서 호출해야할 특정 Object들은 Super::BeginPlay이전에 생성해야 한다.
	LevelTriggerActorAssist = NewObject<ULevelTriggerActorAssist>();
	
	Super::BeginPlay();
}

void ABaseActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called every frame
void ABaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseActor::__SetEnabledCollisions(USceneComponent* SceneComponent, ECollisionEnabled::Type CollisionEnabledType)
{
	UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(SceneComponent);

	if (IsValid(PrimitiveComponent))
	{
		PrimitiveComponent->SetCollisionEnabled(CollisionEnabledType);
	}

	TArray<USceneComponent*> ChildrenComponents;

	SceneComponent->GetChildrenComponents(false, ChildrenComponents);

	for (USceneComponent* ChildComponent : ChildrenComponents)
	{
		__SetEnabledCollisions(ChildComponent, CollisionEnabledType);
	}
}

void ABaseActor::__SetCollisionProfileNames(USceneComponent* SceneComponent, const FName& ProfileName)
{
	UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(SceneComponent);

	if (IsValid(PrimitiveComponent))
	{
		PrimitiveComponent->SetCollisionProfileName(ProfileName);
	}

	TArray<USceneComponent*> ChildrenComponents;

	SceneComponent->GetChildrenComponents(false, ChildrenComponents);

	for (USceneComponent* ChildComponent : ChildrenComponents)
	{
		__SetCollisionProfileNames(ChildComponent, ProfileName);
	}
}

void ABaseActor::__OnGASAttributeChanged(const FOnAttributeChangeData& Data)
{
	TArray<FGameplayAttribute> Attributes;
	
	AbilitySystemComponent->GetAllAttributes(Attributes);

	for(FGameplayAttribute& Attribute : Attributes)
	{
		if(Data.Attribute == Attribute)
		{
			if(TEXT("Health") == Attribute.AttributeName)
			{
				if(Data.NewValue <= 0.f)
				{
					LevelTriggerActorAssist->SetLevelTriggerState(ELevelTriggerActorState::Death, true);
					bIsDeath = true;
				}
				 
				UE_LOG(LogTemp, Display, TEXT("koramga %.2f -> %.2f"), Data.OldValue, Data.NewValue);
			}
		}
	}
}

void ABaseActor::SetEnabledCollisions(bool bIsEnableCollision)
{
	ECollisionEnabled::Type CollisionEnabledType;

	if (bIsEnableCollision)
	{
		CollisionEnabledType = ECollisionEnabled::Type::QueryAndPhysics;
	}
	else
	{
		CollisionEnabledType = ECollisionEnabled::Type::NoCollision;
	}

	__SetEnabledCollisions(GetRootComponent(), CollisionEnabledType);
}

void ABaseActor::SetCollisionProfileNames(const FName& ProfileName)
{
	__SetCollisionProfileNames(GetRootComponent(), ProfileName);
}

void ABaseActor::AddAbility(const FGameplayAbilitySpec& GameplayAbilitySpec)
{
	if (IsValid(AbilitySystemComponent))
	{
		if (HasAuthority() && IsValid(GameplayAbilitySpec.Ability))
		{
			AbilitySystemComponent->GiveAbility(GameplayAbilitySpec);
		}

		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void ABaseActor::AddAttributeSet(const TSubclassOf<UBaseAttributeSet>& AttributeSet)
{
	UBaseAttributeSet* BaseAttribute = NewObject<UBaseAttributeSet>(this, AttributeSet);
	
	AbilitySystemComponent->AddAttributeSetSubobject(BaseAttribute);

	TArray<FGameplayAttribute> Attributes;
	BaseAttribute->GetAttributes(Attributes);

	for(const FGameplayAttribute& Attribute : Attributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &ABaseActor::__OnGASAttributeChanged);
	}
}

bool ABaseActor::IsDeath() const
{
	return bIsDeath;
}

UAbilitySystemComponent* ABaseActor::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

ULevelTriggerActorAssist* ABaseActor::GetLevelTriggerActorAssist() const
{
	return LevelTriggerActorAssist;
}