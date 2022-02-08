// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

struct FBTAbilityInfo
{
	bool	CanActivate;
	bool	IsActivate;
	float	Range;

	FBTAbilityInfo()
		: CanActivate(false), IsActivate(false), Range(0.f) {}
};

UENUM(BlueprintType)
enum class EBTPatrolType : uint8
{
	None,
	Point,
	Space,	
};