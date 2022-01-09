// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLevelActor.h"
#include "../../Components/LevelComponent.h"

ABaseLevelActor::ABaseLevelActor()
{
	LevelComponent = CreateDefaultSubobject<ULevelComponent>(TEXT("LevelComponent"));
}