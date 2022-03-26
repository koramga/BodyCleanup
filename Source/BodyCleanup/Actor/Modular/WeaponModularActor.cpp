// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponModularActor.h"

#include "BodyCleanup/Character/PlayerCharacter/BasePlayerCharacter.h"
#include "BodyCleanup/GCS/Utility/GameGCSFunctionLibrary.h"


// Sets default values
AWeaponModularActor::AWeaponModularActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
}

// Called when the game starts or when spawned
void AWeaponModularActor::BeginPlay()
{
	Super::BeginPlay();

	if(BasePlayerCharacter.IsValid())
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
	
	if(BasePlayerCharacter.IsValid())
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

void AWeaponModularActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if(BasePlayerCharacter.IsValid())
	{
		ICapabilitySystemInterface* CapabilitySystemInterface = Cast<ICapabilitySystemInterface>(OtherActor);

		if(CapabilitySystemInterface != nullptr)
		{		
			UCapabilitySystemComponent* TargetCapabilitySystemComponent = CapabilitySystemInterface->GetCapabilitySystemComponent();			

			if(IsValid(TargetCapabilitySystemComponent))
			{				
				UCapabilitySystemComponent* SelfCAPComponent = BasePlayerCharacter->GetCapabilitySystemComponent();
				TSoftObjectPtr<UCAPAbility> CAPAbility;

				if(SelfCAPComponent->IsActivateAbilityByClass(GeneralAttackCAPAbilityClass))
				{
					CAPAbility = SelfCAPComponent->GetAbility(GeneralAttackCAPAbilityClass);
				}
				else if(SelfCAPComponent->IsActivateAbilityByClass(ChargeAttackCAPAbilityClass))
				{
					CAPAbility = SelfCAPComponent->GetAbility(ChargeAttackCAPAbilityClass);					
				}
				
				if(CAPAbility.IsValid())
				{
					CAPAbility->AffectAbility(TargetCapabilitySystemComponent);
				}
			}			
		}
	}
}

