// Fill out your copyright notice in the Description page of Project Settings.


#include "WarpComponent.h"
#include "../../Actor/BaseActor.h"
#include "../MarkupComponent.h"

// Sets default values for this component's properties
UWarpComponent::UWarpComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Static);

	// ...
}


// Called when the game starts
void UWarpComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UPrimitiveComponent* ParentComponent = Cast<UPrimitiveComponent>(GetAttachParent());

	if (IsValid(ParentComponent))
	{
		ParentComponent->OnComponentBeginOverlap.AddDynamic(this, &UWarpComponent::__OnParentComponentOverlapBegin);
		ParentComponent->OnComponentEndOverlap.AddDynamic(this, &UWarpComponent::__OnParentComponentOverlapEnd);
	}

	if (EWarpType::Point == WarpType)
	{
		MarkupComponent = FindMarkupComponent();
	}
}


// Called every frame
void UWarpComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWarpComponent::__OnParentComponentOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (EWarpType::Level == WarpType)
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelName);
	}
	else if (EWarpType::Point == WarpType)
	{
		if (WarpActor.IsValid())
		{
			FVector Location = WarpActor->GetActorLocation();

			if (MarkupComponent.IsValid())
			{
				Location = MarkupComponent->GetComponentTransform().GetLocation();
			}

			OtherActor->SetActorLocation(Location);
		}
	}
}

void UWarpComponent::__OnParentComponentOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

EWarpType UWarpComponent::GetWarpType() const
{
	return WarpType;
}

TSoftObjectPtr<class UMarkupComponent> UWarpComponent::GetMarkupComponent() const
{
	return MarkupComponent;
}

TSoftObjectPtr<class ABaseActor> UWarpComponent::GetWarpActor() const
{
	return WarpActor;
}

TSoftObjectPtr<class UMarkupComponent> UWarpComponent::FindMarkupComponent() const
{
	TSoftObjectPtr<class UMarkupComponent> FindMarkupComponent = nullptr;

	if (EWarpType::Point == WarpType)
	{
		if (WarpActor.IsValid())
		{
			TArray<UActorComponent*> MarkupComponents = WarpActor->GetComponentsByClass(UMarkupComponent::StaticClass());

			if (MarkupComponents.Num() > 0)
			{
				FindMarkupComponent = MarkupComponents[0];

				if (false == MarkupComponentName.IsNone())
				{
					for (UActorComponent* MarkupActorComponent : MarkupComponents)
					{
						if (EMarkupType::Point == Cast<UMarkupComponent>(MarkupActorComponent)->GetMarkupType())
						{
							if (MarkupActorComponent->GetName() == MarkupComponentName.ToString())
							{
								FindMarkupComponent = MarkupActorComponent;
								break;
							}
						}
					}
				}
			}
		}
	}

	return FindMarkupComponent;
}

