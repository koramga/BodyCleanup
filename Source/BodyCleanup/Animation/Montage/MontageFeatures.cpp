#include "MontageFeatures.h"

FName UMontageSectionFlow::GetNextSectionName() const
{
	return NextSectionName;
}

FName UMontageSectionFlow::GetPressedSectionName() const
{
	return PressedSectionName;
}

FName UMontageSectionFlow::GetReleasedSectionName() const
{
	return ReleasedSectionName;
}

EMontageNextSectionType UMontageSectionFlow::GetNextSectionType() const
{
	return NextSectionType;
}

EMontageSectionType UMontageSectionFlow::GetSectionType() const
{
	return SectionType;
}

UMontageSectionFlowSupporter::UMontageSectionFlowSupporter()
{
	ChargeTime = 0.f;
}

void UMontageSectionFlowSupporter::StartMontage(UAnimMontage* Montage)
{
	ChargeTime = 0.f;
	AnimMontage = Montage;
	bIsEnableComobo = false;
}

void UMontageSectionFlowSupporter::UpdateMontage(UAnimInstance* AnimInstance, float Tick)
{
	
}

void UMontageSectionFlowSupporter::EndMontage()
{

}

float UMontageSectionFlowSupporter::GetChargeTime() const
{
	return ChargeTime;
}
