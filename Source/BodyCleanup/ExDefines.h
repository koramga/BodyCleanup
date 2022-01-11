// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
/**
 * 
 */

#define	MOVE_FORWARD	0x01
#define MOVE_RIGHT		0x02
#define MOVE_BACK		0x04
#define MOVE_LEFT		0x08

UENUM(BlueprintType) 
enum class EAnimationType : uint8
{
	Idle,
	Shot,
	Death,
};

UENUM(BlueprintType)
enum class ELevelType : uint8
{
	Object,
	Wall,
	Stair,
	Floor,
	Junk,
};

UENUM(BlueprintType)
enum class EInteractiveAction : uint8
{
	None,
	Absorbing,
	Holding,
	Shooting,
};

UENUM(BlueprintType)
enum class EInteractiveType : uint8
{
	Rigid,				//당겨지되 먹혀지지는 않는다.
	Junk,				//당겨지되 먹혀지고 먹혀진다.
};

UENUM(BlueprintType)
enum class EInteractiveActive : uint8
{
	Activate,
	DeActivate
};

UENUM(BlueprintType)
enum class EAnimationState : uint8
{
	Enter,
	Left,
	Complete,
};

UENUM(BlueprintType)
enum class EParentMovementAction : uint8
{
	On,
	OnOff,
};

UENUM(BlueprintType)
enum class EWarpType : uint8
{
	Level,
	Point,
};

UENUM(BlueprintType)
enum class EMarkupType : uint8
{
	Point,
};

template <typename Enumeration>
static FORCEINLINE FString GetEnumerationToString(const Enumeration InValue)
{
	return StaticEnum<Enumeration>()->GetNameStringByValue(static_cast<int64>(InValue));
}

template <typename Enumeration>
static FORCEINLINE FName GetEnumerationToName(const Enumeration InValue)
{
	return StaticEnum<Enumeration>()->GetNameByValue(static_cast<int64>(InValue));
}

template <typename Enumeration>
static FORCEINLINE Enumeration GetNameStringToEnumeration(const FString& String)
{
	int64 Value = StaticEnum<Enumeration>()->GetValueByNameString(String);

	if (INDEX_NONE == Value)
	{

	}

	return static_cast<Enumeration>(Value);
}

template <typename Enumeration>
int32 GetMaxEnumValue()
{
	return StaticEnum<Enumeration>()->GetMaxEnumValue();
}

template <typename Enumeration>
static FORCEINLINE Enumeration GetNameToEnumeration(const FName& Name)
{
	int64 Value = StaticEnum<Enumeration>()->GetValueByName(Name);

	if (INDEX_NONE == Value)
	{

	}

	return static_cast<Enumeration>(Value);
}

template <typename Enumeration>
static void GetEnumerationOptions(TArray<FString>& Options)
{
	Options.Empty();

	int32 EnumCount = GetMaxEnumValue<Enumeration>();

	for (int EnumIndex = 0; EnumIndex < EnumCount; ++EnumIndex)
	{
		Enumeration EnumValue = static_cast<Enumeration>(EnumIndex);

		Options.Add(GetEnumerationToString<Enumeration>(EnumValue));
	}
}
