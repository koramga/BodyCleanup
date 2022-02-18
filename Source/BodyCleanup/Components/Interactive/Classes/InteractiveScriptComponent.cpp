// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveScriptComponent.h"
#include "../../../Game/GameInstance/BaseGameInstance.h"
#include "../../../Game/GameMode/MainGameModeBase.h"
#include "../../../Data/TableRow/TableRows.h"
#include "BodyCleanup/Actor/BaseActor.h"
#include "BodyCleanup/Character/BaseCharacter.h"
#include "BodyCleanup/UI/Screen/MainScreenWidget.h"
#include "LevelDesignerTools/Markup/Classes/CameraMarkupComponent.h"
#include "LevelDesignerTools/Markup/Interfaces/LevelMarkupInterface.h"
#include "LevelDesignerTools/Utility/LevelSupportFunctionLibrary.h"

UInteractiveScriptComponent::UInteractiveScriptComponent()
{
	
}

void UInteractiveScriptComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UInteractiveScriptComponent::UpdateTrigger(const FLevelTriggerUpdateParam& InputLevelTriggerUpdateParam)
{
	Super::UpdateTrigger(InputLevelTriggerUpdateParam);

	if (InputLevelTriggerUpdateParam.bIsOnTrigger)
	{
		//여기서부터 시작합니다.
		//일단 여기가 제대로 들어오는지 봅시다.

		AMainGameModeBase* MainGameModeBase = Cast<AMainGameModeBase>(GetWorld()->GetAuthGameMode());

		if(IsValid(MainGameModeBase))
		{
			UBaseGameInstance* BaseGameInstance = Cast<UBaseGameInstance>(MainGameModeBase->GetGameInstance());

			if(IsValid(BaseGameInstance))
			{
				TArray<FScriptTableRow> ScriptTableRows;
				
				BaseGameInstance->GetScripts(ScriptTableRows, SceneName);

				TSoftObjectPtr<UMainScreenWidget> MainScreenWidget = MainGameModeBase->GetMainScreenWidget();

				if(MainScreenWidget.IsValid())
				{
					//Script는 받아진다. 이 상태에서 이제 시작된다. 모든 포커스는 여기로 잡힐거기때문에
					TMap<FName, FScriptTableRowToMainScript> SceneActors;
					TArray<AActor*> AllActors;
					TArray<FMainScreenWidgetScript> MainScreenWidgetScripts; 
	
					for(const FScriptTableRow& ScriptTableRow: ScriptTableRows)
					{
						FScriptTableRowToMainScript* MainScript = SceneActors.Find(ScriptTableRow.ActorName);
	
						if(nullptr == MainScript)
						{
							//이제 찾아야지
							FScriptTableRowToMainScript AddScript;
							
							for(const FActorDescription& ActorDescription : ActorDescriptions)
							{
								if(ActorDescription.ActorName != ScriptTableRow.ActorName)
								{
									continue;
								}
								
								if(EScriptActorInputType::Actor == ActorDescription.ScriptActorInputType)
								{
									if(ActorDescription.Actor.IsValid())
									{
										AddScript.Actor = ActorDescription.Actor;
									}								
								}
								else if(EScriptActorInputType::Name == ActorDescription.ScriptActorInputType)
								{
									if(AllActors.Num() == 0)
									{
										UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseActor::StaticClass(), AllActors);
										UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseCharacter::StaticClass(), AllActors);									
									}
									
									for(AActor* Actor : AllActors)
									{
										UGameActorSettingsComponent* GameActorSettingsComponent = Actor->FindComponentByClass<UGameActorSettingsComponent>();
	
										if(IsValid(GameActorSettingsComponent))
										{
											if(ActorDescription.Name == GameActorSettingsComponent->GetActorName())
											{
												AddScript.Actor = Actor;
												break;
											}
										}
									}
								}
	
								if(AddScript.Actor.IsValid())
								{
									TArray<UActorComponent*> CameraComponents = AddScript.Actor->GetComponentsByClass(UCameraComponent::StaticClass());

									if(ActorDescription.CameraName.IsNone())
									{
										if(CameraComponents.Num() > 0)
										{
											AddScript.CameraComponent = CameraComponents[0];											
										}
									}
									else
									{
										for(UActorComponent* CameraComponent : CameraComponents)
										{
											if(*CameraComponent->GetName() == ActorDescription.CameraName)
											{
												AddScript.CameraComponent = CameraComponent;
												break;
											}
										}
									}
									
									if(AddScript.CameraComponent.IsValid())
									{
										SceneActors.Add(ScriptTableRow.ActorName, AddScript);
										MainScript = SceneActors.Find(ScriptTableRow.ActorName);
									}
									else
									{
										UE_LOG(LogTemp, Error, TEXT("Script Actor에 카메라를 찾을 수 없습니다. <%s> / <%s>"), *ScriptTableRow.ActorName.ToString(), *ActorDescription.CameraName.ToString());										
									}
									
									break;
								}
							}
	
							
						}
	
						if(nullptr != MainScript)
						{
							//드디어 SceneActor가 Valid한 상태로 왔다.
	
							FMainScreenWidgetScript NewScript;
	
							NewScript.Actor = MainScript->Actor;
							NewScript.Script = ScriptTableRow.Script;
							NewScript.CameraComponent = MainScript->CameraComponent; 
							
							MainScreenWidgetScripts.Add(NewScript);
						}
						else
						{
							UE_LOG(LogTemp, Error, TEXT("Script Actor를 찾을 수 없습니다. <%s>"), *ScriptTableRow.ActorName.ToString());
							return;
						}
					}

					MainScreenWidget->SetScreenScriptScripts(MainScreenWidgetScripts);
					MainScreenWidget->StartScript();
				}				
			}
		}
	}
}
