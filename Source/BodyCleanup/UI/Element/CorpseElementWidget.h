// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseElementWidget.h"
#include "CorpseElementWidget.generated.h"

/**
 * 
 */
UCLASS()
class BODYCLEANUP_API UCorpseElementWidget : public UBaseElementWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	class UTextBlock*	TextCorpseCount;

	UPROPERTY()
	class UBorder*		BorderBackground;

	int32				MaxCorpseCount;
	int32				CurrentCorpseCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor		SuccessBackgroundColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundWave*			SuccessSoundWave;

	UPROPERTY()
	FLinearColor		DefaultBackgroundColor;
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void __SetCorpseText();

public :
	void SetMaxCorpseCount(int32 CorpseCount);
	void AddCorpseCount();
	void ResetCorpseCount();
};
