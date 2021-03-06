// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

/**
 * 
 */
class SCRIPTDESIGNEREDITOR_API FScriptGraphEditorStyle
{
public :
	static void Initialize();
	static void Shutdown();

	static const FName& GetStyleSetName();

private :
	static TSharedPtr<FSlateStyleSet> StyleSet;
};
