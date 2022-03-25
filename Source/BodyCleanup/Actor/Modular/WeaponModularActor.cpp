// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponModularActor.h"

#include "BodyCleanup/Character/PlayerCharacter/BasePlayerCharacter.h"


// Sets default values
AWeaponModularActor::AWeaponModularActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
}

// Called when the game starts or when spawned
void AWeaponModularActor::BeginPlay()
{
	Super::BeginPlay();

	ABasePlayerCharacter* BasePlayerCharacter = Cast<ABasePlayerCharacter>(GetOwner());

	if(false == IsValid(BasePlayerCharacter))
	{		
		BasePlayerCharacter = Cast<ABasePlayerCharacter>(GetAttachParentActor());

		//if(IsValid(ChildActorComponent))
		//{
		//	BasePlayerCharacter = Cast<ABasePlayerCharacter>(ChildActorComponent->GetOwner());
		//}
	}

	if(IsValid(BasePlayerCharacter))
	{
		if(IsValid(GeneralAttackCAPAbilityClass))
		{
			BasePlayerCharacter->AddAbility(GeneralAttackCAPAbilityClass);			
		}

		if(IsValid(ChargeAttackCAPAbilityClass))
		{
			BasePlayerCharacter->AddAbility(ChargeAttackCAPAbilityClass);			
		}		
	}	
}

void AWeaponModularActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	ABasePlayerCharacter* BasePlayerCharacter = Cast<ABasePlayerCharacter>(GetOwner());

	if(IsValid(BasePlayerCharacter))
	{
		if(IsValid(GeneralAttackCAPAbilityClass))
		{
			BasePlayerCharacter->RemoveAbility(GeneralAttackCAPAbilityClass);			
		}

		if(IsValid(ChargeAttackCAPAbilityClass))
		{
			BasePlayerCharacter->RemoveAbility(ChargeAttackCAPAbilityClass);			
		}		
	}
}

// Called every frame
void AWeaponModularActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

