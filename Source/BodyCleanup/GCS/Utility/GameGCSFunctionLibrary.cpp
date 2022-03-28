// Fill out your copyright notice in the Description page of Project Settings.


#include "GameGCSFunctionLibrary.h"

const FGameplayTag UGameGCSFunctionLibrary::GeneralAttackGameplayTag = FGameplayTag::RequestGameplayTag("Player.Attack.General");
const FGameplayTag UGameGCSFunctionLibrary::ChargingAttackGameplayTag = FGameplayTag::RequestGameplayTag("Player.Attack.Charge");
const FGameplayTag UGameGCSFunctionLibrary::SpecialAttackGameplayTag = FGameplayTag::RequestGameplayTag("Player.Attack.Special");
const FGameplayTag UGameGCSFunctionLibrary::PlayerAttackGameplayTag = FGameplayTag::RequestGameplayTag("Player.Attack");
const FGameplayTag UGameGCSFunctionLibrary::DamageRootTag = FGameplayTag::RequestGameplayTag("Damage");
const FGameplayTag UGameGCSFunctionLibrary::MeleeDamageTag = FGameplayTag::RequestGameplayTag("Damage.Melee");