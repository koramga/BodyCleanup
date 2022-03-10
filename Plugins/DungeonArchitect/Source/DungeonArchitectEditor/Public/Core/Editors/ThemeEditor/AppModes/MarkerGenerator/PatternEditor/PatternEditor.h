//$ Copyright 2015-21, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#pragma once
#include "CoreMinimal.h"

class IMGPatternEditor {
public:
	
};

class SMGPatternEditor : public SCompoundWidget, public IMGPatternEditor {
public:
	SLATE_BEGIN_ARGS(SMGPatternEditor) {}
		SLATE_ARGUMENT(TWeakPtr<IDetailsView>, PropertyEditor)
	SLATE_END_ARGS()
	
public:
	/** SCompoundWidget functions */
	void Construct(const FArguments& InArgs);
	virtual void Tick(const FGeometry& AllottedGeometry, double InCurrentTime, float InDeltaTime) override;
	
private:
    TWeakPtr<IDetailsView> PropertyEditor;
};

