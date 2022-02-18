// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelDescriptionDataAsset.h"

ELevelRoleType ULevelDescriptionDataAsset::GetLevelRoleType() const
{
	return LevelRoleType;
}

FName ULevelDescriptionDataAsset::GetUELevelName() const
{
	return UELevelName;
}

FName ULevelDescriptionDataAsset::GetLevelName() const
{
	return LevelName;
}

UDataTable* ULevelDescriptionDataAsset::GetScriptDataTable() const
{
	return ScriptDataTable;
}
