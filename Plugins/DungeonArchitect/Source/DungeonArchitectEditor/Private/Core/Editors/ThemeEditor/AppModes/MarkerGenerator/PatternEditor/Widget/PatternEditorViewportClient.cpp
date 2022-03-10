//$ Copyright 2015-21, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#include "Core/Editors/ThemeEditor/AppModes/MarkerGenerator/PatternEditor/Widget/PatternEditorViewportClient.h"


FPatternEditorViewportClient::FPatternEditorViewportClient(FPreviewScene& InPreviewScene)
	: FEditorViewportClient(nullptr, &InPreviewScene)
{
	static constexpr float GridSize = 2048.0f;
	static constexpr int32 CellSize = 16;
	
	// Setup defaults for the common draw helper.
	DrawHelper.bDrawPivot = false;
	DrawHelper.bDrawWorldBox = false;
	DrawHelper.bDrawKillZ = false;
	DrawHelper.bDrawGrid = false;
	DrawHelper.GridColorAxis = FColor(160, 160, 160);
	DrawHelper.GridColorMajor = FColor(144, 144, 144);
	DrawHelper.GridColorMinor = FColor(128, 128, 128);
	DrawHelper.PerspectiveGridSize = GridSize;
	DrawHelper.NumCells = DrawHelper.PerspectiveGridSize / (CellSize * 2);

	FEditorViewportClient::SetViewMode(VMI_Lit);

	//EngineShowFlags.DisableAdvancedFeatures();
	EngineShowFlags.SetSnap(false);
	EngineShowFlags.CompositeEditorPrimitives = true;
	OverrideNearClipPlane(1.0f);
	bUsingOrbitCamera = true;

	// Set the initial camera position
	FRotator OrbitRotation(-40, 10, 0);
	SetCameraSetup(
		FVector::ZeroVector,
		OrbitRotation,
		FVector(0.0f, 100, 0.0f),
		FVector::ZeroVector,
		FVector(300, 400, 500),
		FRotator(-10, 0, 0)
	);
	SetViewLocation(FVector(500, 300, 500));
	//SetLookAtLocation(FVector(0, 0, 0));
}

void FPatternEditorViewportClient::Tick(float DeltaSeconds) {
	FEditorViewportClient::Tick(DeltaSeconds);
	
	// Tick the preview scene world.
	if (!GIntraFrameDebuggingGameThread) {
		PreviewScene->GetWorld()->Tick(LEVELTICK_All, DeltaSeconds);
	}
}
