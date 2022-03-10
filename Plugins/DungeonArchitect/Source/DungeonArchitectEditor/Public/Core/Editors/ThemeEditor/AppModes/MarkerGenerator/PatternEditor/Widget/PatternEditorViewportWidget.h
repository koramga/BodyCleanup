//$ Copyright 2015-21, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#pragma once
#include "CoreMinimal.h"
#include "SEditorViewport.h"

class SPatternEditorViewport : public SEditorViewport, public FGCObject {
public:
	SLATE_BEGIN_ARGS(SPatternEditorViewport) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	virtual ~SPatternEditorViewport() override;
	
	// FGCObject interface
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	// End of FGCObject interface
	
	/** Set the parent tab of the viewport for determining visibility */
	void SetParentTab(TSharedRef<SDockTab> InParentTab) { ParentTab = InParentTab; }

	// SWidget Interface
	virtual void Tick(const FGeometry& AllottedGeometry, double InCurrentTime, float InDeltaTime) override;
	// End of SWidget Interface
	
	EVisibility GetToolbarVisibility() const;

	TSharedPtr<class FPreviewScene> GetAdvancedPreview() const { return PreviewScene; }
	
	virtual UWorld* GetWorld() const override;
	
protected:
	/** SEditorViewport interface */
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;
	virtual EVisibility OnGetViewportContentVisibility() const override;
	virtual void BindCommands() override;
	virtual void OnFocusViewportToSelection() override;

	void OnToggleDebugData();

private:
	/** Determines the visibility of the viewport. */
	virtual bool IsVisible() const override;

private:
	/** The parent tab where this viewport resides */
	TWeakPtr<SDockTab> ParentTab;
	
	/** Level viewport client */
	TSharedPtr<class FPatternEditorViewportClient> EditorViewportClient;

	/** The scene for this viewport. */
	TSharedPtr<FPreviewScene> PreviewScene;
	USkyAtmosphereComponent* AtmosphericFog = nullptr;
};

