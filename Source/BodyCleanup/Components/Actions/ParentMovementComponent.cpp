// Fill out your copyright notice in the Description page of Project Settings.


#include "ParentMovementComponent.h"
#include "../../Actor/BaseActor.h"


// Sets default values for this component's properties
UParentMovementComponent::UParentMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	InteractiveComponentCount = 0;

	// ...
}

// Called when the game starts
void UParentMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//DestinationTransform =  GetTransform()

	USceneComponent* AttachParentComponent = GetAttachParent();

	if (IsValid(AttachParentComponent))
	{
		AttachParentComponent->Mobility = EComponentMobility::Type::Movable;

		SourceTransform = AttachParentComponent->GetRelativeTransform();
		DestinationTransform = AttachParentComponent->GetRelativeTransform() + GetRelativeTransform();
		DestinationTransform.SetRotation((AttachParentComponent->GetRelativeRotation() + GetRelativeRotation()).Quaternion());
	}

	if (!InteractiveComponentTagName.IsNone())
	{
		//������ � ���� �����Ѵ�.
		AActor* Owner = GetOwner();

		TArray<UActorComponent*> InteractiveComponents = Owner->GetComponentsByTag(UPrimitiveComponent::StaticClass(), InteractiveComponentTagName);

		for (UActorComponent* ActorComponent : InteractiveComponents)
		{
			UPrimitiveComponent* InteractiveComponent = Cast<UPrimitiveComponent>(ActorComponent);

			InteractiveComponent->OnComponentBeginOverlap.AddDynamic(this, &UParentMovementComponent::__OnInteractiveComponentOverlapBegin);
			InteractiveComponent->OnComponentEndOverlap.AddDynamic(this, &UParentMovementComponent::__OnInteractiveComponentOverlapEnd);

			InteractiveComponentCount++;
		}
	}
}


// Called every frame
void UParentMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (MovementAction == EParentMovementAction::On)
	{
		if (false == bIsOn)
		{
			if (__CheckIsOn())
			{
				bIsOn = true;
			}
		}
	}
	else
	{
		if (__CheckIsOn())
		{
			bIsOn = true;
		}
		else
		{
			bIsOn = false;
		}
	}

	if (bIsOn)
	{
		__UpdateToDestination(DeltaTime);
	}
	else
	{
		__UpdateToSource(DeltaTime);
	}
}

void UParentMovementComponent::__OnInteractiveComponentOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != GetOwner())
	{
		if (false == InteractiveOverlappedComponents.Contains(OtherComp))
		{
			InteractiveOverlappedComponents.Add(OtherComp);
			
			//UE_LOG(LogTemp, Display, TEXT("BeginOverlapped <%s> : <%s>"), *OtherActor->GetName(), *OtherComp->GetName());
		}
	}
}

void UParentMovementComponent::__OnInteractiveComponentOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != GetOwner())
	{
		if (true == InteractiveOverlappedComponents.Contains(OtherComp))
		{
			InteractiveOverlappedComponents.Remove(OtherComp);

			//UE_LOG(LogTemp, Display, TEXT("EndOverlapped <%s> : <%s>"), *OtherActor->GetName(), *OtherComp->GetName());
		}
	}
}

void UParentMovementComponent::__UpdateToDestination(float DeltaTime)
{
	USceneComponent* AttachParentComponent = GetAttachParent();

	if (IsValid(AttachParentComponent))
	{
		FTransform Source = AttachParentComponent->GetRelativeTransform();

		if (bIsUpdateScale)
		{
			AttachParentComponent->SetRelativeScale3D(FMath::VInterpTo(Source.GetScale3D(), DestinationTransform.GetScale3D(), DeltaTime, InterpSpeed));
		}

		if (bIsUpdateRotator)
		{
			AttachParentComponent->SetRelativeRotation(FQuat::FastLerp(Source.GetRotation(), Source.GetRotation() + DestinationTransform.GetRotation(), DeltaTime * InterpSpeed));
		}

		if (bIsUpdateScale)
		{
			AttachParentComponent->SetRelativeLocation(FMath::VInterpTo(Source.GetLocation(), DestinationTransform.GetLocation(), DeltaTime, InterpSpeed));
		}
	}
}

void UParentMovementComponent::__UpdateToSource(float DeltaTime)
{
	USceneComponent* AttachParentComponent = GetAttachParent();

	if (IsValid(AttachParentComponent))
	{
		FTransform Source = AttachParentComponent->GetRelativeTransform();

		if (bIsUpdateScale)
		{
			AttachParentComponent->SetRelativeScale3D(FMath::VInterpTo(Source.GetScale3D(), SourceTransform.GetScale3D(), DeltaTime, InterpSpeed));
		}

		if (bIsUpdateRotator)
		{
			AttachParentComponent->SetRelativeRotation(FQuat::FastLerp(Source.GetRotation(), SourceTransform.GetRotation(), DeltaTime * InterpSpeed));
		}

		if (bIsUpdateScale)
		{
			AttachParentComponent->SetRelativeLocation(FMath::VInterpTo(Source.GetLocation(), SourceTransform.GetLocation(), DeltaTime, InterpSpeed));
		}
	}
}

bool UParentMovementComponent::__CheckIsOn()
{
	if (InteractiveComponentCount <= InteractiveOverlappedComponents.Num())
	{
		for (TSoftObjectPtr<ABaseActor> InteractiveActor : InteractiveActors)
		{
			const TSet<UActorComponent*>& ParentMovementComponents = InteractiveActor->GetComponents();

			for (UActorComponent* ActorComponent : ParentMovementComponents)
			{
				UParentMovementComponent* ParentMovementComponent = Cast<UParentMovementComponent>(ActorComponent);

				if (IsValid(ParentMovementComponent))
				{
					if (false == ParentMovementComponent->IsOn())
					{
						return false;
					}
				}
			}
		}

		return true;
	}

	return false;
}

bool UParentMovementComponent::IsOn() const
{
	return bIsOn;
}

const TArray<TSoftObjectPtr<class ABaseActor>>& UParentMovementComponent::GetInteractiveActors() const
{
	return InteractiveActors;
}