// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStatsAttributeSet.h"

void UBaseStatsAttributeSet::PostInitProperties()
{
	Super::PostInitProperties();

	//UE_LOG(LogTemp, Display, TEXT("koramga PostInitProperties"));
	Health.SetBaseValue(__Health__);
	Health.SetCurrentValue(__Health__);

	MaxHealth.SetBaseValue(__MaxHealth__);
	MaxHealth.SetCurrentValue(__MaxHealth__);
}
