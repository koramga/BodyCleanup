// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyboardElementWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UKeyboardElementWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	TextHelp = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextHelp")));
	ImageHelp = Cast<UImage>(GetWidgetFromName(TEXT("ImageHelp")));
}

void UKeyboardElementWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UKeyboardElementWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UKeyboardElementWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UKeyboardElementWidget::SetText(const FString& Text) const
{
	TextHelp->SetText(FText::FromString(Text));
}

void UKeyboardElementWidget::SetImagePath(const FString& Path)
{
	if(false == bIsSetImage)
	{
		bIsSetImage = true;
		UTexture2D* Texture2D = LoadObject<UTexture2D>(nullptr, *Path);
		ImageHelp->SetBrushFromTexture(Texture2D);		
	}	
}
