// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperJumpComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

USuperJumpComponent::USuperJumpComponent()
{
	SuperJumpVelocity = 3000.f;
}

void USuperJumpComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &USuperJumpComponent::__OnOverlapBegin);
	OnComponentEndOverlap.AddDynamic(this, &USuperJumpComponent::__OnOverlapEnd);
}

void USuperJumpComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool USuperJumpComponent::__IsAllowActor(AActor* Actor)
{	
	for(const TSubclassOf<AActor>& AllowActors : AllowSuperJumpCharacterClasses)
	{
		if(Actor->IsA(AllowActors))
		{
			return true;
		}
	}

	return false;
}

void USuperJumpComponent::__OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("koramga Overlap Begin in the SuperJump"));
	
	if(IsValid(OtherActor)
		&& OtherActor != GetOwner()
		&& OtherComp != this)
	{
		UCharacterMovementComponent* CharacterMovementComponent = Cast<UCharacterMovementComponent>(OtherActor->GetComponentByClass(UCharacterMovementComponent::StaticClass()));

		if(IsValid(CharacterMovementComponent))
		{
			if(false == OverlapActors.Contains(OtherActor))
			{
				OverlapActors.Add(OtherActor);
				
				if(CallbackDoSuperJump.IsBound())
				{
					CallbackDoSuperJump.Execute(OtherActor);
				}
				
				if(__IsAllowActor(OtherActor))
				{
					if(CharacterMovementComponent->IsFalling())
					{
						CharacterMovementComponent->Velocity.Z = SuperJumpVelocity;
					}
				}
			}			
		}
	}	
}

void USuperJumpComponent::__OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OverlapActors.Remove(OtherActor);
}

