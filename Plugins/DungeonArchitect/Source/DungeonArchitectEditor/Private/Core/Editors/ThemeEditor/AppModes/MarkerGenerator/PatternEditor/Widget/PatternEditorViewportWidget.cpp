//$ Copyright 2015-21, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#include "Core/Editors/ThemeEditor/AppModes/MarkerGenerator/PatternEditor/Widget/PatternEditorViewportWidget.h"

#include "Core/Editors/ThemeEditor/AppModes/MarkerGenerator/PatternEditor/Widget/PatternEditorViewportClient.h"

#include "Components/DirectionalLightComponent.h"
#include "Components/SkyAtmosphereComponent.h"
#include "Components/SkyLightComponent.h"
#include "EditorViewportClient.h"
#include "Widgets/Docking/SDockTab.h"

#define LOCTEXT_NAMESPACE "SPatternEditorViewport"


void SPatternEditorViewport::Construct(const FArguments& InArgs) {
    {
        FPreviewScene::ConstructionValues CVS;
        CVS.bCreatePhysicsScene = false;
        CVS.LightBrightness = 3;
        CVS.SkyBrightness = 1;
        PreviewScene = MakeShareable(new FPreviewScene(CVS));
    }

    SEditorViewport::Construct(SEditorViewport::FArguments());

    UWorld* World = PreviewScene->GetWorld();

    AtmosphericFog = NewObject<USkyAtmosphereComponent>();
    PreviewScene->AddComponent(AtmosphericFog, FTransform::Identity);

    PreviewScene->DirectionalLight->SetMobility(EComponentMobility::Movable);
    PreviewScene->DirectionalLight->CastShadows = true;
    PreviewScene->DirectionalLight->CastStaticShadows = true;
    PreviewScene->DirectionalLight->CastDynamicShadows = true;
    PreviewScene->SetSkyBrightness(1.0f);

    // TODO: Create default scene
    
}


SPatternEditorViewport::~SPatternEditorViewport() {
    FCoreUObjectDelegates::OnObjectPropertyChanged.RemoveAll(this);
    if (EditorViewportClient.IsValid()) {
        EditorViewportClient->Viewport = nullptr;
    }
}

void SPatternEditorViewport::AddReferencedObjects(FReferenceCollector& Collector) {
    Collector.AddReferencedObject(AtmosphericFog);

    // TODO: Add any managed actors here
}


void SPatternEditorViewport::OnToggleDebugData() {

}

void SPatternEditorViewport::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime,
                                               const float InDeltaTime) {
    SEditorViewport::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);

}

EVisibility SPatternEditorViewport::GetToolbarVisibility() const {
    return EVisibility::Visible;
}

TSharedRef<FEditorViewportClient> SPatternEditorViewport::MakeEditorViewportClient() {
    EditorViewportClient = MakeShareable(new FPatternEditorViewportClient(*PreviewScene));

    EditorViewportClient->bSetListenerPosition = false;
    EditorViewportClient->SetRealtime(true); // TODO: Check if real-time is needed
    EditorViewportClient->VisibilityDelegate.BindSP(this, &SPatternEditorViewport::IsVisible);

    return EditorViewportClient.ToSharedRef();
}

EVisibility SPatternEditorViewport::OnGetViewportContentVisibility() const {
    return EVisibility::Visible;
}

void SPatternEditorViewport::BindCommands() {
    SEditorViewport::BindCommands();

}

void SPatternEditorViewport::OnFocusViewportToSelection() {
    SEditorViewport::OnFocusViewportToSelection();
}

bool SPatternEditorViewport::IsVisible() const {
    return ViewportWidget.IsValid() && (!ParentTab.IsValid() || ParentTab.Pin()->IsForeground());
}

UWorld* SPatternEditorViewport::GetWorld() const {
    return PreviewScene->GetWorld();
}

#undef LOCTEXT_NAMESPACE


