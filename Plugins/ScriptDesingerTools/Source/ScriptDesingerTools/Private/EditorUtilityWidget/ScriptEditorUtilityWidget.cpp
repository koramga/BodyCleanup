// Fill out your copyright notice in the Description page of Project Settings.


#include "EditorUtilityWidget/ScriptEditorUtilityWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Serialization/JsonWriter.h"
#include "Misc/Paths.h"

void UScriptEditorUtilityWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	ButtonWriteJson = Cast<UButton>(GetWidgetFromName(TEXT("ButtonWriteJson")));
	ButtonReadJson = Cast<UButton>(GetWidgetFromName(TEXT("ButtonReadJson")));
}

void UScriptEditorUtilityWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(ButtonWriteJson))
	{
		ButtonWriteJson->OnClicked.AddDynamic(this, &UScriptEditorUtilityWidget::__OnButtonClickedWriteJson);
	}

	if (IsValid(ButtonReadJson))
	{
		ButtonReadJson->OnClicked.AddDynamic(this, &UScriptEditorUtilityWidget::__OnButtonClickedReadJson);
	}
}

void UScriptEditorUtilityWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UScriptEditorUtilityWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

int32 UScriptEditorUtilityWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	int32 NativePaintReturnValue = Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	
	FPaintContext Context(AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	UWidgetBlueprintLibrary::DrawLine(Context, FVector2D(0.f, 0.f), FVector2D(100.f, 100.f), FLinearColor::Blue, true, 1.f);
	
	return NativePaintReturnValue;
}

void UScriptEditorUtilityWidget::__OnButtonClickedWriteJson()
{
	UE_LOG(LogTemp, Display, TEXT("WriteJsonButton"));

	//https://cpp.hotexamples.com/examples/-/TSharedRef/WriteValue/cpp-tsharedref-writevalue-method-examples.html

	FString jsonstr;	// Recive save json text
	TSharedRef<TJsonWriter<TCHAR>> jsonObj = TJsonWriterFactory<>::Create(&jsonstr);
	
	jsonObj->WriteObjectStart();
	{
		jsonObj->WriteValue("Sample1", 1);	// Value type : bool, int, float, string

		//jsonObj->WriteArrayStart(TEXT("SubLevel"));
		{
			jsonObj->WriteObjectStart(TEXT("Hello"));
			{
				jsonObj->WriteValue("SubSample1", 2);
			}
			jsonObj->WriteObjectEnd();
		}
		//jsonObj->WriteArrayEnd();
	}
	jsonObj->WriteObjectEnd();
	
	jsonObj->Close();	// Essential last

	UE_LOG(LogTemp, Display, TEXT("%s"), *jsonstr);

	const FString FilePath = FPaths::ProjectDir() + TEXT("Saved/JsonStr.txt");

	UE_LOG(LogTemp, Display, TEXT("Path : <%s>"), *FilePath);

	if (FFileHelper::SaveStringToFile(*jsonstr, *FilePath))
	{
		UE_LOG(LogTemp, Display, TEXT("Success SaveStringToFile"));
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Failed SaveStringToFile"));
	}
	// Save json to filePath
}

void UScriptEditorUtilityWidget::__OnButtonClickedReadJson()
{
	UE_LOG(LogTemp, Display, TEXT("ReadJsonButton"));

	//https://ballbot.tistory.com/45

	FString jsonStr;

	const FString FilePath = FPaths::ProjectDir() + TEXT("Saved/JsonStr.txt");

	if (FFileHelper::LoadFileToString(jsonStr, *FilePath))
	{
		UE_LOG(LogTemp, Display, TEXT("LoadFileToString Success : <%s>"), *jsonStr);

		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<>::Create(jsonStr);
		TSharedPtr<FJsonObject> RootObject = MakeShareable(new FJsonObject());
		FJsonSerializer::Deserialize(Reader, RootObject);

		if (RootObject.IsValid())
		{
			int Number = 0;
			if (RootObject->TryGetNumberField(TEXT("Sample1"), Number))
			{
				UE_LOG(LogTemp, Display, TEXT("Sample1 : <%d>"), Number);
			}

			TSharedPtr<FJsonObject> HelloObject = RootObject->GetObjectField(TEXT("Hello"));

			if (HelloObject.IsValid())
			{
				if (HelloObject->TryGetNumberField("SubSample1", Number))
				{
					UE_LOG(LogTemp, Display, TEXT("SubSample1 : <%d>"), Number);
				}
			}
		}
	}
}
