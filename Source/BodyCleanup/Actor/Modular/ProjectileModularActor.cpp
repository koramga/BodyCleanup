// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileModularActor.h"


// Sets default values
AProjectileModularActor::AProjectileModularActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
}

// Called when the game starts or when spawned
void AProjectileModularActor::BeginPlay()
{
	Super::BeginPlay();

	if(DeathTime > 0.f)
	{
		SetLifeSpan(DeathTime);
	}
}


void AProjectileModularActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	UE_LOG(LogTemp, Display, TEXT("Overlap Actor <%s>"), *OtherActor->GetName());

	TSoftObjectPtr<UCAPAbility> CAPAbility = CapabilitySystemComponent->GetAbilityFromIndex(0);

	if(CAPAbility.IsValid())
	{
		if(OtherActor->GetClass()->ImplementsInterface(UCapabilitySystemInterface::StaticClass()))
		{
			UCapabilitySystemComponent* TargetCapabilitySystemComponent = Cast<ICapabilitySystemInterface>(OtherActor)->GetCapabilitySystemComponent();
			
			TargetCapabilitySystemComponent->ApplyGameplayEffectFromSource(CAPAbility->GetAbilityCAPEffect()
				, CapabilitySystemComponent, CAPAbility->GetAbilityLevel(), CAPAbility->GetWeight());
		}		
	}

	Destroy();
	//SetEnableCollision(false);
	//SetActorHiddenInGame(true);
	//SetLifeSpan(0.1f);
}

// Called every frame
void AProjectileModularActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * (DeltaTime * SpeedPerSecond));
}
