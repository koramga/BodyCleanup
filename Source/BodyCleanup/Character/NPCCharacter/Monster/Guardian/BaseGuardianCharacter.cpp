// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGuardianCharacter.h"

#include "BTGameFunctionLibrary.h"
#include "BodyCleanup/Game/GameInstance/BaseGameInstance.h"
#include "GameFramework/GameModeBase.h"
#include "Interface/BTControllerInterface.h"


// Sets default values
ABaseGuardianCharacter::ABaseGuardianCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
}

// Called when the game starts or when spawned
void ABaseGuardianCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	UpdatePhaseToBlackboard(CurrentPhase);
}

// Called every frame
void ABaseGuardianCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseGuardianCharacter::UpdatePhaseToBlackboard(int32 InUpdatePhase)
{
	if(Controller->GetClass()->ImplementsInterface(UBTControllerInterface::StaticClass()))
	{
		IBTControllerInterface* BTControllerInterface = Cast<IBTControllerInterface>(Controller);

		if(nullptr != BTControllerInterface)
		{						
			TBlackboardVariable PhaseVariable;
			PhaseVariable.Set<int32>(InUpdatePhase);
						
			BTControllerInterface->SetBlackboardVariable(UBTGameFunctionLibrary::PhaseName, PhaseVariable);
		}
	}
}

void ABaseGuardianCharacter::OnHit(const FOnCAPAttributeChangeData& Data)
{
	Super::OnHit(Data);
	
	UBaseGameInstance* BaseGameInstance = Cast<UBaseGameInstance>(GetWorld()->GetAuthGameMode()->GetGameInstance());

	if(IsValid(BaseGameInstance))
	{
		FName StatTypeName = BaseGameInstance->GetStatTypeToName(EGameStatType::MaxHP);

		FCAPAttributeData* AttributeData = CapabilitySystemComponent->GetAttributeDataByAttributeName(StatTypeName);

		if(nullptr != AttributeData)
		{
			float MaxHP = AttributeData->GetCurrentValue();
			float HP = Data.NewValue;

			for(int i = CurrentPhase; i < PhaseInformations.Num(); ++i)
			{
				if(MaxHP * PhaseInformations[i].HPPercent > HP)
				{
					CurrentPhase = i + 1;

					UpdataPhase(CurrentPhase, PhaseInformations[i]);
				}
			}
		}
	}
}

void ABaseGuardianCharacter::UpdataPhase(int32 InUpdatePhase, const FPhaseInformation& PhaseInformation)
{
	for(const FMaterialInstanceVariable& MaterialInstanceVariable : PhaseInformation.MaterialInstanceVariables)
	{
		MaterialInstanceVariable.SetMaterialInstanceParameter(GetMesh());
	}
	
	UpdatePhaseToBlackboard(InUpdatePhase);
}

