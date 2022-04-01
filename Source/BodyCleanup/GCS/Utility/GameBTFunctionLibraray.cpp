// Fill out your copyright notice in the Description page of Project Settings.


#include "GameBTFunctionLibraray.h"

#include "Interface/BTControllerInterface.h"


ETeamType UGameBTFunctionLibraray::GetTeamType(AActor* Actor)
{
	if(IsValid(Actor))
	{
		if(Actor->IsA(ACharacter::StaticClass()))
		{
			ACharacter* Character = Cast<ACharacter>(Actor);

			if(IsValid(Character->GetController()))
			{
				if(Character->GetController()->GetClass()->ImplementsInterface(UBTControllerInterface::StaticClass()))
				{
					IBTControllerInterface* BTControllerInterface = Cast<IBTControllerInterface>(Character->GetController());

					return BTControllerInterface->GetTeamType();
				}
			}
		}	
	}	

	return ETeamType::None;
}

bool UGameBTFunctionLibraray::IsEnemy(ETeamType LTeamType, ETeamType RTeamType)
{
	if(ETeamType::None == LTeamType
		|| ETeamType::None == RTeamType)
	{
		return true;
	}

	if(LTeamType != RTeamType)
	{
		return true;
	}

	return false;
}

bool UGameBTFunctionLibraray::IsEnemy(AActor* LActor, AActor* RActor)
{	
	return IsEnemy(GetTeamType(LActor), GetTeamType(RActor));
}
