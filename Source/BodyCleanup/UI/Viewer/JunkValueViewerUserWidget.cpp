// Fill out your copyright notice in the Description page of Project Settings.


#include "JunkValueViewerUserWidget.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"

void UJunkValueViewerUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	TextBlockJunkValue = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlockJunkValue")));
	BorderJunkValue = Cast<UBorder>(GetWidgetFromName(TEXT("BorderJunkValue")));
}

void UJunkValueViewerUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UJunkValueViewerUserWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UJunkValueViewerUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UJunkValueViewerUserWidget::SetJunkValue(int32 InJunkValue)
{
	if(InJunkValue <= 0)
	{
		SetHiddenInGame(true);
	}
	else
	{
		SetHiddenInGame(false);
	
		if(IsValid(BorderJunkValue))
		{
			float Percent = (InJunkValue % 4) / 4.f;

			UMaterialInstanceDynamic* MaterialInstanceDynamic = BorderJunkValue->GetDynamicMaterial();

			if(IsValid(MaterialInstanceDynamic))
			{
				MaterialInstanceDynamic->SetScalarParameterValue("ComplateRange", Percent);
			}		
		}

		if(IsValid(TextBlockJunkValue))
		{
			int32 UIJunkValue = InJunkValue / 4.f;
		
			if(InJunkValue >= 10000)
			{
				UIJunkValue = 9999;
			}
		
			TextBlockJunkValue->SetText(FText::FromString(FString::Printf(TEXT("%d"), UIJunkValue)));
		}
	}
}
