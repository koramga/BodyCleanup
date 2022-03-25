#pragma once

#include "Animation/AnimMetaData.h"
#include "UObject/NoExportTypes.h"
#include "MontageFeatures.generated.h"

UENUM(BlueprintType)
enum class EMontageNextSectionType : uint8
{
	Self,
	Pressed,
	Next,
	Released,
};

UENUM(BlueprintType)
enum class EMontageSectionType : uint8
{
	Normal,
	Energy,
	Charge,
};

UCLASS(BlueprintType, Blueprintable)
class BODYCLEANUP_API UMontageSectionFlow
	: public UAnimMetaData
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Section")
	EMontageSectionType			SectionType = EMontageSectionType::Normal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Section")
	FName					NextSectionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Section")
	FName					PressedSectionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Section")
	FName					ReleasedSectionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Section")
	EMontageNextSectionType		NextSectionType = EMontageNextSectionType::Next;

public:
	FName	GetNextSectionName() const;
	FName	GetPressedSectionName() const;
	FName	GetReleasedSectionName() const;
	EMontageNextSectionType	GetNextSectionType() const;
	EMontageSectionType		GetSectionType() const;
};

UCLASS(BlueprintType, Blueprintable)
class BODYCLEANUP_API UMontageSectionFlowSupporter
	: public UObject
{
	GENERATED_BODY()

public :
	UMontageSectionFlowSupporter();

protected :
	UPROPERTY()
	UAnimMontage*	AnimMontage;

	bool			bIsEnableComobo;
	float			ChargeTime;

public :
	void StartMontage(UAnimMontage* Montage);
	void UpdateMontage(UAnimInstance* AnimInstance, float Tick);
	void EndMontage();

public :
	float GetChargeTime() const;
};