// Fill out your copyright notice in the Description page of Project Settings.


#include "CAPAttributeSet.h"
#include "CAPAffect.h"

bool UCAPAttributeSet::PreUpdateAttribute(FOnCAPAttributeChangeData& OnCapAttributeChangeData)
{
	return true;
}

void UCAPAttributeSet::PostUpdateAttribute(const FOnCAPAttributeChangeData& OnCapAttributeChangeData)
{
	
}

//bool UCAPAttributeSet::HasAttributeName(const FName& InAttributeName)
//{
//	for (TFieldIterator<UProperty> PropIt(GetClass(), EFieldIteratorFlags::IncludeSuper); PropIt; ++PropIt)
//	{
//		UProperty* Property = *PropIt;
//		// Do something with the property
//	}
//	
//}
bool UCAPAttributeSet::AffectAttribute(TSoftObjectPtr<UCAPAffect> Affect, const FName& AttributeName, ECAPModifierOp Op, float Magnitude)
{
	for(FCAPAttributeData& CAPAttributeData : CAPAttributeDatas)
	{
		if(CAPAttributeData.GetAttributeName() == AttributeName)
		{
			FOnCAPAttributeChangeData AttributeChangeData;
			AttributeChangeData.AttributeName = AttributeName;
			AttributeChangeData.OldValue = CAPAttributeData.GetCurrentValue();
			AttributeChangeData.AttributeSet = this;
			
			switch (Op)
			{
			case ECAPModifierOp::Additive :
				AttributeChangeData.NewValue = AttributeChangeData.OldValue + Magnitude;
				break;
			case ECAPModifierOp::Division :
				AttributeChangeData.NewValue = AttributeChangeData.OldValue / Magnitude;
				break;
			case ECAPModifierOp::Multiply :
				AttributeChangeData.NewValue = AttributeChangeData.OldValue * Magnitude;
				break;
			case ECAPModifierOp::Override :
				AttributeChangeData.NewValue = Magnitude;
				break;
			}

			if(PreUpdateAttribute(AttributeChangeData))
			{
				if(CallbackOnCAPAttirbuteChanged.IsBound())
				{
					CallbackOnCAPAttirbuteChanged.Execute(AttributeChangeData);
				}

				PostUpdateAttribute(AttributeChangeData);

				CAPAttributeData.SetCurrentValue(AttributeChangeData.NewValue);
			}

			return true;
		}
	}

	return false;
}