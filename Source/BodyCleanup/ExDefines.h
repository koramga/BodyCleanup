// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
enum class ETriggerComponentFromType : uint8
{
	//부모 Component로부터 Trigger가 설정됩니다.
	ParentComponent,		
	//Component TagName으로 부터 Trigger가 설정됩니다.
	ComponentTagName,		
	//Component 이름으로부터 Trigger가 설정됩니다.
	ComponentName,			
	//Actor의 모든 Trigger로부터 Trigger가 설정됩니다.
	Actor,					
	//Actor의 Component Name으로부터 Trigger가 설정됩니다.
	ActorComponentName,		
	//Actor의 Component Tag Name으로부터 Trigger가 설정됩니다.
	ActorComponentTagName,	
};

UENUM(BlueprintType)
enum class EActionComponentToType : uint8
{
	//부모 Component를 Action 합니다.
	ParentComponent,
	//Component TagName으로 부터 Action이 결정됩니다.
	ComponentTagName,
	//Component 이름으로부터 Action이 결정됩니다.
	ComponentName,
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
