//$ Copyright 2015-21, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#include "Core/Editors/ThemeEditor/AppModes/ThemeEditorAppModeBase.h"

#include "Core/Editors/ThemeEditor/DungeonArchitectThemeEditor.h"

FThemeEditorAppModeBase::FThemeEditorAppModeBase(TSharedPtr<FDungeonArchitectThemeEditor> InThemeEditor, FName InModeName)
	: FApplicationMode(InModeName, FDungeonArchitectThemeEditor::GetLocalizedMode)
	, ThemeEditorPtr(InThemeEditor)
{	
}

TSharedRef<class IDetailsView> FThemeEditorAppModeBase::CreatePropertyEditorWidget() const {
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	const FDetailsViewArgs DetailsViewArgs(false, false, true, FDetailsViewArgs::HideNameArea, true);
	TSharedRef<IDetailsView> PropertyEditorRef = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	return PropertyEditorRef;
}

