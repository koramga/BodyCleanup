// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseScriptUserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "ScreenSelectScriptUserWidget.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType, Blueprintable)
struct FScreenSelectScript
{
	GENERATED_BODY()

public :
	FScreenSelectScript()
		: TextBlock(nullptr), Border(nullptr)
	{}
	FScreenSelectScript(class UTextBlock* TextBlock, class UBorder* Border)
		: TextBlock(TextBlock), Border(Border)
	{
		
	}
	
public :
	UPROPERTY()
	class UTextBlock* TextBlock;

	UPROPERTY()
	class UBorder* Border;
};

UCLASS()
class BODYCLEANUP_API UScreenSelectScriptUserWidget : public UBaseScriptUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TArray<FScreenSelectScript>	ScreenSelectScripts;

	UPROPERTY()
	UProgressBar*				LimitProgressBar;
	
	float						LimitTime = 0.f;
	float						CurrentTime;
	int32						SelectCount = 0;
	int32						SelectIndex = 0;
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public :
	void SetText(float InLimitTime, const TArray<FString>& Texts);
	int32 GetSelectCount() const;
	void SetSelectIndex(int Index);
	int32 GetSelectIndex() const;
	void UpSelect();
	void DownSelect();
};
