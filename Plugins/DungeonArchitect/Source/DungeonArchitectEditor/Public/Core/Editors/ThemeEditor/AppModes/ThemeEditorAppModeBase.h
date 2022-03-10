//$ Copyright 2015-21, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#pragma once
#include "CoreMinimal.h"
#include "WorkflowOrientedApp/ApplicationMode.h"

class FDungeonArchitectThemeEditor;

class FThemeEditorAppModeBase : public FApplicationMode {
public:
	explicit FThemeEditorAppModeBase(TSharedPtr<FDungeonArchitectThemeEditor> InThemeEditor, FName InModeName);
	virtual void Init() {}
	virtual void Tick(float DeltaTime) {}
	virtual void OnBuilderClassChanged(TSubclassOf<class UDungeonBuilder> InBuilderClass) {}
	virtual void ShowObjectDetails(UObject* ObjectProperties, bool bForceRefresh = false) const {}

protected:
	TSharedRef<class IDetailsView> CreatePropertyEditorWidget() const;
	
protected:
	TWeakPtr<FDungeonArchitectThemeEditor> ThemeEditorPtr;
};

