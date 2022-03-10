//$ Copyright 2015-21, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#pragma once
#include "CoreMinimal.h"
#include "Core/Editors/ThemeEditor/AppModes/MarkerGenerator/Preview2D/Preview2DViewportWidget.h"
#include "Core/Editors/ThemeEditor/AppModes/ThemeEditorAppModeBase.h"
#include "Frameworks/GraphGrammar/Editor/SEditableListView.h"
#include "Frameworks/MarkerGenerator/MarkerGenLayer.h"

#include "WorkflowOrientedApp/WorkflowTabManager.h"

class SThemePreviewViewport;
class SMGPatternEditor;
class UMarkerGenLayer;
class UMarkerGenModel;

class FMarkerGeneratorAppMode : public FThemeEditorAppModeBase {
public:
	FMarkerGeneratorAppMode(TSharedPtr<FDungeonArchitectThemeEditor> InThemeEditor, TSharedPtr<SThemePreviewViewport> InPreviewViewport);

	virtual void Init() override;
	virtual void RegisterTabFactories(TSharedPtr<class FTabManager> InTabManager) override;
	
	////////// Layer ListView Handlers //////////
	void OnLayerSelectionChanged(UMarkerGenLayer* Item, ESelectInfo::Type SelectInfo);
	FText GetLayerListRowText(UMarkerGenLayer* InItem) const;
	const TArray<UMarkerGenLayer*>* GetLayerList() const;
	void OnLayerDelete(UMarkerGenLayer* InItem);
	void OnLayerAdd() const;
	void OnLayerReordered(UMarkerGenLayer* Source, UMarkerGenLayer* Dest) const;
	////////// End of ListView Handlers //////////

private:
	UMarkerGenLayer* CreateNewLayer(UObject* InOuter, const FText& InLayerName) const;
	UMarkerGenModel* GetMarkerGenerationModel() const;
	void SetActiveLayer(UMarkerGenLayer* InLayer);
	
private:
	TSharedPtr<IDetailsView> PropertyEditor;
	TSharedPtr<SMGPatternEditor> PatternEditor;
	TSharedPtr<SEditableListView<UMarkerGenLayer*>> LayerList;
	TSharedPtr<SMGPreview2DViewport> PreviewViewport2D;
	TWeakPtr<SThemePreviewViewport> PreviewViewportPtr;	
	
	FWorkflowAllowedTabSet TabFactories;
	TWeakObjectPtr<UMarkerGenLayer> ActiveLayer;
};

