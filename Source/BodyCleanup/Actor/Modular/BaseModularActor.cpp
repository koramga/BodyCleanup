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

	BaseCharacter = Cast<ABaseCharacter>(GetOwner());

	if(false == BaseCharacter.IsValid())
	{		
		BaseCharacter = Cast<ABaseCharacter>(GetAttachParentActor());
	}

	if(IsValid(BoxComponent))
	{
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseModularActor::__OnOverlapBegin);
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

void ABaseModularActor::AddIgnoreActor(AActor* IgnoreActor)
{
	BoxComponent->IgnoreActorWhenMoving(IgnoreActor, true);
	
	IgnoreActors.Add(IgnoreActor);
}

void ABaseModularActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Display, TEXT("OnOverlapBegin : <%s>"), *OtherComp->GetName());
}

void ABaseModularActor::__OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	if(OtherActor != BaseCharacter)
	{
		bool bIsAdd = false;
		
		if(false == OverlapActors.Contains(OtherActor))
		{
			OverlapActors.Add(OtherActor);
			bIsAdd = true;
		}

		if(IgnoreActors.Contains(OtherActor))
		{
			return;
		}

		TArray<FHitResult> AllResults; 
		GetWorld()->SweepMultiByObjectType(
		AllResults,
		GetActorLocation(),
		GetActorLocation(),
		FQuat::Identity,
	0,
		FCollisionShape::MakeBox(BoxComponent->GetScaledBoxExtent()),  
		FCollisionQueryParams::DefaultQueryParam);

		FHitResult HitResult;
		
		for(FHitResult InputHitResult : AllResults)
		{
			if(InputHitResult.GetActor() == OtherActor
				&& InputHitResult.GetComponent() == OtherComp)
			{
				HitResult = InputHitResult;
				break;
			}
		}

		if(bIsDuplicateOverlap)
		{
			OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, HitResult);
		}
		else
		{
			if(bIsAdd)
			{
				OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, HitResult);
			}
		}
	}
}
