#pragma once
#include "AnimationDesignerToolsDefines.generated.h"


UENUM(BlueprintType)
enum class EAnimNotify_ChangeOfStateType : uint8
{
	EnableCollision,		//충돌체 허용 여부
	EnableBeDamaged,		//Damage를 받는 것을 허용하는 상태인가?
};

USTRUCT(BlueprintType)
struct FAnimNotify_ChangeOfStateStruct
{
	GENERATED_BODY()

	FAnimNotify_ChangeOfStateStruct()
		: Type(EAnimNotify_ChangeOfStateType::EnableBeDamaged), bIsEnabled(false)
	{
		
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)	
	EAnimNotify_ChangeOfStateType	Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool							bIsEnabled;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "Type == EAnimNotify_ChangeOfStateType::EnableCollision", EditConditionHides))
	TArray<FName>					CollisionNames;
};