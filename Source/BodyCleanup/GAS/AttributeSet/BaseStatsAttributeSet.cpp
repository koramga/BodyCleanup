// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStatsAttributeSet.h"

void UBaseStatsAttributeSet::PostInitProperties()
{
	Super::PostInitProperties();

	//UE_LOG(LogTemp, Display, TEXT("koramga PostInitProperties"));
	Health.SetBaseValue(SetupHealth);
	Health.SetCurrentValue(SetupHealth);

	MaxHealth.SetBaseValue(SetupMaxHealth);
	MaxHealth.SetCurrentValue(SetupMaxHealth);
}
