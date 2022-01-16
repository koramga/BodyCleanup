// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DestructibleComponent.h"
#include "DestructibleMesh.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
/**
 * 
 */

#define QUARTER_VIEW_ANGLE	-45

#define	MOVE_FORWARD	0x01
#define MOVE_RIGHT		0x02
#define MOVE_BACK		0x04
#define MOVE_LEFT		0x08

UENUM(BlueprintType)
enum class EAnimationType : uint8
{
	Idle,
	Shot,
	Vacuum,
	Death,
	Return,
	Wait,
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
	//어떤 동작도 되지 않습니다.
	None,
	//당겨지고 홀딩되어집니다.
	Rigid,
	//당겨지고 먹혀집니다.
	Junk,
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
	//Warp를 이용하여 Level을 이동합니다.
	Level,
	//Warp를 이용하여 위치를 이동합니다.
	Location,
};

UENUM(BlueprintType)
enum class EMarkupType : uint8
{
	Point,
};

UENUM(BlueprintType)
enum class ENameType : uint8
{
	Name,
	Tag,
};

UENUM(BlueprintType)
enum class ETriggerComponentFromType : uint8
{
	//부모 Component로부터 Trigger가 설정됩니다.
	Parent,
	//사용자가 설정한 Setup에 맞게 Trigger가 설정됩니다.
	Setup,
	//사용자가 설정할 수 없습니다. 만약 사용자가 강제로 설정한다면 Trigger가 동작되지 않습니다.
	Action,
};

UENUM(BlueprintType)
enum class EActionComponentToType : uint8
{
	//부모 Component를 Action 합니다.
	Parent,
	//Component Setup으로 부터 결정됩니다.
	Setup,
};

UENUM(BlueprintType)
enum class EInteractiveComponentToType : uint8
{
	//부모 Component를 Action 합니다.
	Parent,
	//Component Setup으로 부터 결정됩니다.
	Setup,
};

UENUM(BlueprintType)
enum class ESpawnComponentType : uint8
{
	Hidden,
	Spawn,
};

UENUM(BlueprintType)
enum class EActionComponentActionType : uint8
{
	//한 번의 Trigger에만 반응합니다.
	On,
	//여러 번의 Trigger에 반응합니다.
	OnOff,					
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
