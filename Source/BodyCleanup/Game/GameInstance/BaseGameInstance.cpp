// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameInstance.h"
#include "../../Data/TableRow/TableRows.h"

void UBaseGameInstance::Init()
{
	Super::Init();

	StatTypeNames.Empty();

	if(IsValid(StatNameDataTable))
	{
		for(auto iter : StatNameDataTable->GetRowMap())
		{
			FGameStatNameTableRow* TableRow =  (FGameStatNameTableRow*)(iter.Value);

			if(nullptr != TableRow)
			{
				StatTypeNames.Add(TableRow->GameStatType, TableRow->Name);
			}
		}
	}
}

FName UBaseGameInstance::GetStatTypeToName(EGameStatType StatType)
{
	FName* Name = StatTypeNames.Find(StatType);

	if(nullptr == Name)
	{
		return FName("");
	}

	return *Name;
}
