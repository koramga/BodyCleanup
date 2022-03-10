//$ Copyright 2015-21, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#include "Core/Editors/ThemeEditor/AppModes/MarkerGenerator/PatternEditor/PatternEditor.h"

#include "Core/Editors/ThemeEditor/AppModes/MarkerGenerator/PatternEditor/Widget/PatternEditorViewportWidget.h"

#define LOCTEXT_NAMESPACE "SMGPatternEditor"

void SMGPatternEditor::Construct(const FArguments& InArgs) {
	PropertyEditor = InArgs._PropertyEditor;

	ChildSlot
	[
		SNew(SPatternEditorViewport)
	];
}

void SMGPatternEditor::Tick(const FGeometry& AllottedGeometry, double InCurrentTime, float InDeltaTime) {
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
	
}


#undef LOCTEXT_NAMESPACE

