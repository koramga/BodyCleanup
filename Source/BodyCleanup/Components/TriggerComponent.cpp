// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

// Sets default values for this component's properties
UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (ETriggerComponentFromType::ParentComponent == TriggerComponentFromType)
	{
		UPrimitiveComponent* AttachParentComponent = Cast<UPrimitiveComponent>(GetAttachParent());

		AttachParentComponent->OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::__OnTriggerComponentOverlapBegin);
		AttachParentComponent->OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::__OnTriggerComponentOverlapEnd);
	}
	else if (ETriggerComponentFromType::ComponentTagName == TriggerComponentFromType)
	{

	}
	else if (ETriggerComponentFromType::ComponentName == TriggerComponentFromType)
	{

	}
	else if (ETriggerComponentFromType::Actor == TriggerComponentFromType)
	{

	}
	else if (ETriggerComponentFromType::ActorComponentName == TriggerComponentFromType)
	{

	}
	else if (ETriggerComponentFromType::ActorComponentTagName == TriggerComponentFromType)
	{

	}
}


// Called every frame
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTriggerComponent::__OnTriggerComponentOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TriggerTickComponents.is(OtherComp)
}

void UTriggerComponent::__OnTriggerComponentOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

bool UTriggerComponent::IsOnTrigger() const
{
	return false;
}