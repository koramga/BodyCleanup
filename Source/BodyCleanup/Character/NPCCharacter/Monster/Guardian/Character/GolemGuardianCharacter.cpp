// Fill out your copyright notice in the Description page of Project Settings.


#include "GolemGuardianCharacter.h"

#include "BTGameFunctionLibrary.h"
#include "BodyCleanup/Game/GameInstance/BaseGameInstance.h"
#include "GameFramework/GameModeBase.h"
#include "Interface/BTControllerInterface.h"


// Sets default values
AGolemGuardianCharacter::AGolemGuardianCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
}

// Called when the game starts or when spawned
void AGolemGuardianCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGolemGuardianCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//void AGolemGuardianCharacter::OnHit(const FOnCAPAttributeChangeData& Data)
//{
//	Super::OnHit(Data);
//	
//	UBaseGameInstance* BaseGameInstance = Cast<UBaseGameInstance>(GetWorld()->GetAuthGameMode()->GetGameInstance());
//
//	if(IsValid(BaseGameInstance))
//	{
//		FName StatTypeName = BaseGameInstance->GetStatTypeToName(EGameStatType::MaxHP);
//
//		FCAPAttributeData* AttributeData = CapabilitySystemComponent->GetAttributeDataByAttributeName(StatTypeName);
//
//		if(nullptr != AttributeData)
//		{
//			float MaxHP = AttributeData->GetCurrentValue();
//			float HP = Data.NewValue;
//			int CalcPhase = 0;
//			
//			if(MaxHP * 0.3f > HP)
//			{
//				CalcPhase = 2;
//			}
//			else if(MaxHP * 0.5f > HP)
//			{
//				CalcPhase = 1;
//			}
//
//			if(CurrentPhase < CalcPhase)
//			{
//				//Phase 변경!
//				CurrentPhase = CalcPhase;
//
//				UMaterialInstanceDynamic* MaterialInstanceDynamic = GetMesh()->CreateDynamicMaterialInstance(0);
//
//				if(IsValid(MaterialInstanceDynamic))
//				{
//					if(CurrentPhase == 1)
//					{
//						MaterialInstanceDynamic->SetVectorParameterValue("BaseColor", FLinearColor(0.f, 0.f, 1.f, 1.f));	
//					}
//					else if(CurrentPhase == 2)
//					{
//						MaterialInstanceDynamic->SetVectorParameterValue("BaseColor", FLinearColor(1.f, 0.f, 0.f, 1.f));
//					}
//				}
//				
//				if(Controller->GetClass()->ImplementsInterface(UBTControllerInterface::StaticClass()))
//				{
//					IBTControllerInterface* BTControllerInterface = Cast<IBTControllerInterface>(Controller);
//
//					if(nullptr != BTControllerInterface)
//					{						
//						TBlackboardVariable PhaseVariable;
//						PhaseVariable.Set<int32>(CurrentPhase);
//						
//						BTControllerInterface->SetBlackboardVariable(UBTGameFunctionLibrary::PhaseName, PhaseVariable);
//					}
//				}
//			}
//		}
//	}
//}

