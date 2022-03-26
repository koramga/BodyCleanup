// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseModularActor.h"

#include "BodyCleanup/Character/PlayerCharacter/BasePlayerCharacter.h"
#include "Components/BoxComponent.h"


// Sets default values
ABaseModularActor::ABaseModularActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	BoxComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseModularActor::BeginPlay()
{
	Super::BeginPlay();

	BasePlayerCharacter = Cast<ABasePlayerCharacter>(GetOwner());

	if(false == BasePlayerCharacter.IsValid())
	{		
		BasePlayerCharacter = Cast<ABasePlayerCharacter>(GetAttachParentActor());
	}

	if(IsValid(BoxComponent))
	{
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseModularActor::ABaseModularActor::__OnOverlapBegin);
	}

	SetEnableCollision(false);
}

// Called every frame
void ABaseModularActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseModularActor::SetEnableCollision(bool bIsEnableCollision)
{
	if(bIsEnableCollision)
	{
		BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	OverlapActors.Reset();
}

void ABaseModularActor::SetDuplicateOverlap(bool bInIsDuplicateOverlap)
{
	bIsDuplicateOverlap = bInIsDuplicateOverlap;
}

void ABaseModularActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Display, TEXT("OnOverlapBegin : <%s>"), *OtherComp->GetName());
}

void ABaseModularActor::__OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	if(OtherActor != BasePlayerCharacter)
	{
		bool bIsAdd = false;
		
		if(INDEX_NONE == OverlapActors.Find(OtherActor))
		{
			OverlapActors.Add(OtherActor);
			bIsAdd = true;
		}

		if(bIsDuplicateOverlap)
		{
			OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
		}
		else
		{
			if(bIsAdd)
			{
				OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
			}
		}
	}
}
