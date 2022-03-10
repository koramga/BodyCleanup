//$ Copyright 2015-21, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#include "Core/Editors/ThemeEditor/AppModes/MarkerGenerator/MarkerGeneratorAppMode.h"

#include "Core/Editors/ThemeEditor/AppModes/Common/ThemeEditorAppTabFactoryMacros.h"
#include "Core/Editors/ThemeEditor/AppModes/MarkerGenerator/PatternEditor/PatternEditor.h"
#include "Core/Editors/ThemeEditor/DungeonArchitectThemeEditor.h"
#include "Core/Editors/ThemeEditor/Widgets/SThemePreviewViewport.h"
#include "Frameworks/MarkerGenerator/MarkerGenModel.h"
#include "Frameworks/MarkerGenerator/MarkerGenPattern.h"

#define LOCTEXT_NAMESPACE "FMarkerGeneratorAppMode"

namespace MarkerGeneratorAppModeTabs {
	static const FName TabID_Layers(TEXT("Layers"));
	static const FName TabID_Pattern(TEXT("Pattern"));
	static const FName TabID_PatternRuleGraph(TEXT("PatternRuleGraph"));
	static const FName TabID_Preview(TEXT("Preview"));
	static const FName TabID_Preview2D(TEXT("Preview2D"));
	static const FName TabID_Details(TEXT("Details"));
	
	DEFINE_THEME_EDITOR_TAB_FACTORY(Layers,
				LOCTEXT("Caption_Layers", "Layers"),
				"LevelEditor.Tabs.Layers",
				LOCTEXT("TooltipMenu_Layers", "Generate markers in the scene through different layered passes"),
				LOCTEXT("TooltipTab_Layers", "Generate markers in the scene through different layered passes"))

	DEFINE_THEME_EDITOR_TAB_FACTORY(Pattern,
				LOCTEXT("Caption_Pattern", "Pattern"),
				"LevelEditor.Tabs.Viewports",
				LOCTEXT("TooltipMenu_Pattern", "Define the patter for your marker generation / deletion rules"),
				LOCTEXT("TooltipTab_Pattern", "Define the patter for your marker generation / deletion rules"))
	
	DEFINE_THEME_EDITOR_TAB_FACTORY(PatternRuleGraph,
				LOCTEXT("Caption_PatternNodeRule", "Pattern Node Rule"),
				"LevelEditor.Tabs.Viewports",
				LOCTEXT("TooltipMenu_PatternRuleGraph", "Define the pattern matching rule for a rule node"),
				LOCTEXT("TooltipTab_PatternRuleGraph", "Define the pattern matching rule for a rule node"))
	
	DEFINE_THEME_EDITOR_TAB_FACTORY(Details,
				LOCTEXT("Caption_Details", "Details"),
				"LevelEditor.Tabs.Details",
				LOCTEXT("TooltipMenu_Details", "Details panel for modifying the node properties"),
				LOCTEXT("TooltipTab_Details", "Details panel for modifying the node properties"))

	
	DEFINE_THEME_EDITOR_TAB_FACTORY_CUSTOM_SPAWNER(Preview,
				LOCTEXT("Caption_PreviewViewport", "Preview"),
				"LevelEditor.Tabs.Viewports",
				LOCTEXT("TooltipMenu_Preview", "Preview the generated dungeon in a 3D viewport"),
				LOCTEXT("TooltipTab_Preivew", "Preview the generated dungeon in a 3D viewport"))

	
	DEFINE_THEME_EDITOR_TAB_FACTORY(Preview2D,
				LOCTEXT("Caption_Preview2DViewport", "Preview2D"),
				"LevelEditor.Tabs.Viewports",
				LOCTEXT("TooltipMenu_Preview2D", "Preview the generated dungeon in a 2D viewport"),
				LOCTEXT("TooltipTab_Preivew2D", "Preview the generated dungeon in a 2D viewport"))

	
	TSharedRef<SDockTab> FThemeEditorTabFactory_Preview::SpawnTab(const FWorkflowTabSpawnInfo& Info) const {
		TSharedRef<SDockTab> DockTab = FWorkflowTabFactory::SpawnTab(Info);
		const TSharedPtr<SThemePreviewViewport> PreviewViewport = StaticCastSharedPtr<SThemePreviewViewport>(WidgetPtr.Pin());
		if (PreviewViewport.IsValid()) {
			PreviewViewport->SetParentTab(FDungeonArchitectThemeEditor::AppModeID_MarkerGenerator, DockTab);
		}
		return DockTab;;
	}
	
	
}

FMarkerGeneratorAppMode::FMarkerGeneratorAppMode(TSharedPtr<FDungeonArchitectThemeEditor> InThemeEditor, TSharedPtr<SThemePreviewViewport> InPreviewViewport)
	: FThemeEditorAppModeBase(InThemeEditor, FDungeonArchitectThemeEditor::AppModeID_MarkerGenerator)
	, PreviewViewportPtr(InPreviewViewport)
{
	
}

void FMarkerGeneratorAppMode::Init() {
	const TSharedPtr<FDungeonArchitectThemeEditor> ThemeEditor = ThemeEditorPtr.Pin();
	if (!ThemeEditor.IsValid()) return;
	
	const TSharedPtr<SThemePreviewViewport> PreviewViewport = PreviewViewportPtr.Pin();
	check(PreviewViewport.IsValid());
	
	PatternEditor = SNew(SMGPatternEditor);
	PreviewViewport2D = SNew(SMGPreview2DViewport);

	PropertyEditor = CreatePropertyEditorWidget();
	
	LayerList = SNew(SEditableListView<UMarkerGenLayer*>)
		.GetListSource(this, &FMarkerGeneratorAppMode::GetLayerList)
		.OnSelectionChanged(this, &FMarkerGeneratorAppMode::OnLayerSelectionChanged)
		.OnAddItem(this, &FMarkerGeneratorAppMode::OnLayerAdd)
		.OnDeleteItem(this, &FMarkerGeneratorAppMode::OnLayerDelete)
		.OnReorderItem(this, &FMarkerGeneratorAppMode::OnLayerReordered)
		.GetItemText(this, &FMarkerGeneratorAppMode::GetLayerListRowText)
		.IconBrush(FDungeonArchitectStyle::Get().GetBrush("DA.SnapEd.GraphIcon"))
		.AllowDropOnGraph(true);
	
	TabFactories.RegisterFactory(MakeShareable(new MarkerGeneratorAppModeTabs::FThemeEditorTabFactory_Layers(ThemeEditor, LayerList)));
	TabFactories.RegisterFactory(MakeShareable(new MarkerGeneratorAppModeTabs::FThemeEditorTabFactory_Pattern(ThemeEditor, PatternEditor)));
	TabFactories.RegisterFactory(MakeShareable(new MarkerGeneratorAppModeTabs::FThemeEditorTabFactory_PatternRuleGraph(ThemeEditor)));
	TabFactories.RegisterFactory(MakeShareable(new MarkerGeneratorAppModeTabs::FThemeEditorTabFactory_Details(ThemeEditor, PropertyEditor)));
	TabFactories.RegisterFactory(MakeShareable(new MarkerGeneratorAppModeTabs::FThemeEditorTabFactory_Preview(ThemeEditor, PreviewViewport)));
	TabFactories.RegisterFactory(MakeShareable(new MarkerGeneratorAppModeTabs::FThemeEditorTabFactory_Preview2D(ThemeEditor, PreviewViewport2D)));

	TabLayout = FTabManager::NewLayout(
			"MarkerGeneratorAppMode_Layout_v0.0.7")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->SetHideTabWell(true)
				->AddTab(ThemeEditor->GetToolbarTabId(), ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewSplitter()
					->SetOrientation(Orient_Vertical)
					->SetSizeCoefficient(0.2f)
					->Split
					(
						FTabManager::NewStack()
						->SetSizeCoefficient(0.35f)
						->AddTab(MarkerGeneratorAppModeTabs::TabID_Layers, ETabState::OpenedTab)
					)
					->Split
					(
						FTabManager::NewStack()
						->SetSizeCoefficient(0.65f)
						->AddTab(MarkerGeneratorAppModeTabs::TabID_Details, ETabState::OpenedTab)
					)
				)
				->Split
				(
					FTabManager::NewSplitter()
                	->SetOrientation(Orient_Vertical)
                	->SetSizeCoefficient(0.5f)
                	->Split
                	(
                		FTabManager::NewStack()
                		->SetSizeCoefficient(0.55f)
                		->AddTab(MarkerGeneratorAppModeTabs::TabID_Pattern, ETabState::OpenedTab)
                	)
                	->Split
                	(
                		FTabManager::NewStack()
                		->SetSizeCoefficient(0.45f)
                		->AddTab(MarkerGeneratorAppModeTabs::TabID_PatternRuleGraph, ETabState::OpenedTab)
                	)
					
				)
				->Split
				(
					FTabManager::NewSplitter()
	                ->SetOrientation(Orient_Vertical)
	                ->SetSizeCoefficient(0.5f)
	                ->Split
	                (
	                    FTabManager::NewStack()
	                    ->AddTab(MarkerGeneratorAppModeTabs::TabID_Preview2D, ETabState::OpenedTab)
	                )
	                ->Split
	                (
	                    FTabManager::NewStack()
	                    ->AddTab(MarkerGeneratorAppModeTabs::TabID_Preview, ETabState::OpenedTab)
	                )
				)
			)
		);

	ThemeEditor->GetToolbarBuilder()->AddModesToolbar(ToolbarExtender);
	ThemeEditor->GetToolbarBuilder()->AddMarkerGeneratorToolbar(ToolbarExtender);
}

void FMarkerGeneratorAppMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) {
	const TSharedPtr<FDungeonArchitectThemeEditor> ThemeEditor = ThemeEditorPtr.Pin();

	ThemeEditor->RegisterToolbarTab(InTabManager.ToSharedRef());
	ThemeEditor->PushTabFactories(TabFactories);

	FApplicationMode::RegisterTabFactories(InTabManager);
}

void FMarkerGeneratorAppMode::OnLayerSelectionChanged(UMarkerGenLayer* Item, ESelectInfo::Type SelectInfo) {
	if (PropertyEditor.IsValid()) {
		PropertyEditor->SetObject(Item);
	}

	SetActiveLayer(Item);
}

FText FMarkerGeneratorAppMode::GetLayerListRowText(UMarkerGenLayer* InItem) const {
	return InItem ? InItem->LayerName : LOCTEXT("MissingLayerName", "Unknown");
}

const TArray<UMarkerGenLayer*>* FMarkerGeneratorAppMode::GetLayerList() const {
	UMarkerGenModel* MarkerGenerationModel = GetMarkerGenerationModel();
	return MarkerGenerationModel ? &MarkerGenerationModel->Layers : nullptr;
}

void FMarkerGeneratorAppMode::OnLayerAdd() const {
	static const FText DefaultLayerName = LOCTEXT("DefaultLayerName", "Layer");
	
	if (UMarkerGenModel* Model = GetMarkerGenerationModel()) {
		UMarkerGenLayer* NewLayer = CreateNewLayer(Model, DefaultLayerName);
		Model->Layers.Add(NewLayer);
		Model->Modify();
		
		// TODO: LayerEditor->SetLayer(NewLayer);
	}
}

UMarkerGenLayer* FMarkerGeneratorAppMode::CreateNewLayer(UObject* InOuter, const FText& InLayerName) const {
	UMarkerGenLayer* NewLayer = NewObject<UMarkerGenLayer>(InOuter);
	NewLayer->LayerName = InLayerName;
	NewLayer->Pattern = NewObject<UMarkerGenPattern>(NewLayer);

	NewLayer->Compile();
	
	return NewLayer;
}

void FMarkerGeneratorAppMode::OnLayerDelete(UMarkerGenLayer* InItem) {
	if (!InItem) return;
	
	static const FText Title = LOCTEXT("DADeleteLayerTitle", "Delete Layer?");
	const EAppReturnType::Type ReturnValue = FMessageDialog::Open(EAppMsgType::YesNo, EAppReturnType::No,
															LOCTEXT("DADeleteLayer","Are you sure you want to delete the layer?"),
															&Title);

	if (ReturnValue == EAppReturnType::Yes) {
		// Delete the layer
		if (UMarkerGenModel* MarkerGenerationModel = GetMarkerGenerationModel()) {
			MarkerGenerationModel->Layers.Remove(InItem);
			MarkerGenerationModel->Modify();

			SetActiveLayer(nullptr);
		}
	}
}

void FMarkerGeneratorAppMode::OnLayerReordered(UMarkerGenLayer* Source, UMarkerGenLayer* Dest) const {
	if (UMarkerGenModel* Model = GetMarkerGenerationModel()) {
		int32 DestIndex = -1;
		if (!Model->Layers.Find(Dest, DestIndex)) {
			DestIndex = 0;
		}
		Model->Layers.Remove(Source);
		Model->Layers.Insert(Source, DestIndex);	
	}
}

UMarkerGenModel* FMarkerGeneratorAppMode::GetMarkerGenerationModel() const {
	const TSharedPtr<FDungeonArchitectThemeEditor> ThemeEditor = ThemeEditorPtr.Pin();
	if (ThemeEditor.IsValid()) {
		if (const UDungeonThemeAsset* ThemeAsset = ThemeEditor->GetAssetBeingEdited()) {
			return ThemeAsset->MarkerGenerationModel;
		}
	}
	return nullptr;
}

void FMarkerGeneratorAppMode::SetActiveLayer(UMarkerGenLayer* InLayer) {
	ActiveLayer = InLayer;

	// TODO: Set the pattern model
}


#undef LOCTEXT_NAMESPACE

