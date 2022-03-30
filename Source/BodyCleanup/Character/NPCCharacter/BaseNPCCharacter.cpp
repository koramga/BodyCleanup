// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseNPCCharacter.h"
#include "Interface/BTPatrolActorInterface.h"
#include "../../Actor/Level/Patrol/BasePatrolActor.h"
#include "Components/CapsuleComponent.h"
#include "LevelDesignerTools/Utility/LevelSupportFunctionLibrary.h"

ABaseNPCCharacter::ABaseNPCCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	PatrolType = EBTPatrolType::None;
}

void ABaseNPCCharacter::BeginPlay()
{
	Super::BeginPlay();

	TArray<UActorComponent*> ActorComponents = GetComponentsByTag(UPrimitiveComponent::StaticClass(), TEXT("Attack"));

	for(UActorComponent* ActorComponent : ActorComponents)
	{
		UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(ActorComponent);

		if(IsValid(PrimitiveComponent))
		{
			AttackPrimitiveComponents.Add(PrimitiveComponent);
			PrimitiveComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseNPCCharacter::__OnAttackOverlapBegin);
			AttackPrimitiveComponentOverlapMap.Add(PrimitiveComponent);
		}
	}
}

void ABaseNPCCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	AttackPrimitiveComponentOverlapMap.Reset();
}

void ABaseNPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseNPCCharacter::__OnAttackOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor != this
		&& IsValid(OtherActor))
	{
		TArray<TWeakObjectPtr<AActor>>* BeginOverlapActors = AttackPrimitiveComponentOverlapMap.Find(OverlappedComp);

		if(BeginOverlapActors != nullptr)
		{
			if(false == BeginOverlapActors->Contains(OtherActor))
			{
				BeginOverlapActors->Add(OtherActor);

				TSoftObjectPtr<UCAPAbility> CAPAbility = CapabilitySystemComponent->GetActivateAbility();

				if(CAPAbility.IsValid())
				{
					if(OtherActor->GetClass()->ImplementsInterface(UCapabilitySystemInterface::StaticClass()))
					{
						UCapabilitySystemComponent* TargetCapabilitySystemComponent = Cast<ICapabilitySystemInterface>(OtherActor)->GetCapabilitySystemComponent();

						if(IsValid(TargetCapabilitySystemComponent))
						{
							CAPAbility->AffectAbility(TargetCapabilitySystemComponent);
						}
					}					
				}						
			}
		}
	}	
}

void ABaseNPCCharacter::UpdateDeath(bool bInIsDeath)
{
	Super::UpdateDeath(bInIsDeath);

	if(true == bInIsDeath)
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->SetPhysicsLinearVelocity(FVector::ZeroVector);

		TArray<TSoftObjectPtr<UPrimitiveComponent>> PrimitiveComponents;
		
		ULevelSupportFunctionLibrary::FindPrimitiveComponets(PrimitiveComponents, this);
	}
}

void ABaseNPCCharacter::OnChangeOfStateFromNotify(FAnimNotify_ChangeOfStateStruct& InNotifyStruct)
{
	Super::OnChangeOfStateFromNotify(InNotifyStruct);

	if(EAnimNotify_ChangeOfStateType::EnableCollision == InNotifyStruct.Type)
	{
		TArray<UActorComponent*> ActorComponents;
		
		GetComponents(UPrimitiveComponent::StaticClass(), ActorComponents);

		for(UActorComponent* ActorComponent : ActorComponents)
		{
			if(InNotifyStruct.CollisionNames.Contains( FName(*ActorComponent->GetName())))
			{
				UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(ActorComponent);

				if(IsValid(PrimitiveComponent))
				{
					if(InNotifyStruct.bIsEnabled)
					{
						PrimitiveComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
					}
					else
					{
						PrimitiveComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

						TArray<TWeakObjectPtr<AActor>>* BeginOverlapActors = AttackPrimitiveComponentOverlapMap.Find(PrimitiveComponent);

						if(nullptr != BeginOverlapActors)
						{
							BeginOverlapActors->Reset();
						}						
					}
				}						
			}
		}
	}
}

EBTPatrolType ABaseNPCCharacter::GetPatrolType() const
{
	if(EBTPatrolType::Point == PatrolType)
	{
		if(PatrolActors.Num() <= 1)
		{
			return EBTPatrolType::None;
		}		
	}
	else if(EBTPatrolType::Space == PatrolType)
	{
		if(PatrolActors.Num() <= 0)
		{
			return EBTPatrolType::None;
		}
	}
		
	return PatrolType;
}

IBTPatrolActorInterface* ABaseNPCCharacter::GetPatrolActorInterface() const
{
	if(EBTPatrolType::None == PatrolType)
	{
		return nullptr;
	}
	else if(EBTPatrolType::Point == PatrolType)
	{
		if(PatrolActors.Num() <= 1)
		{
			return nullptr;
		}		
	}
	else if(EBTPatrolType::Space == PatrolType)
	{
		if(PatrolActors.Num() <= 0)
		{
			return nullptr;
		}
	}

	return Cast<IBTPatrolActorInterface>(PatrolActors[PatrolActorIndex]);
}

void ABaseNPCCharacter::SetNextPatrol()
{
	if(EBTPatrolType::Point == PatrolType)
	{
		if(PatrolActors.Num() >= 2)
		{
			PatrolActorIndex += PatrolActorDirection;

			if(PatrolActorDirection < 0)
			{
				if(PatrolActorIndex < 0)
				{
					PatrolActorIndex = 1;
					PatrolActorDirection *= -1;
				}
			}
			else if(PatrolActorDirection > 0)
			{
				if(PatrolActorIndex >= PatrolActors.Num())
				{
					PatrolActorIndex = PatrolActors.Num() - 2;
					PatrolActorDirection *= -1;
				}
			}
		}		
	}
}

FBTPatrolInfo ABaseNPCCharacter::GetPatrolInfo() const
{
	FBTPatrolInfo PatrolInfo = Super::GetPatrolInfo();

	PatrolInfo.MinDistance = MinPatrolDistance.GetMetaVariable().Get<float>();
	PatrolInfo.MaxDistance = MaxPatrolDistance.GetMetaVariable().Get<float>();

	return PatrolInfo;
}
