// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameModeBase.h"
#include "../../UI/Screen/BaseScreenWidget.h"
#include "../../Controller/Player/BasePlayerController.h"

ABaseGameModeBase::ABaseGameModeBase()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	LevelTriggerManager = NewObject<ULevelTriggerManager>(this);
}

void ABaseGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	if(IsValid(BaseScreenWidgetClass))
	{
		BaseScreenWidget = 	CreateWidget<UBaseScreenWidget>(GetWorld(), BaseScreenWidgetClass);
		
		if (BaseScreenWidget)
			BaseScreenWidget->AddToViewport();
	}
}

void ABaseGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	LevelTriggerManager->Tick(DeltaSeconds);
}

void ABaseGameModeBase::RegisterTrigger(ILevelTriggerInterface* LevelTriggerInterface)
{
	LevelTriggerManager->RegisterTrigger(LevelTriggerInterface);
}

void ABaseGameModeBase::UnRegisterTrigger(ILevelTriggerInterface* LevelTriggerInterface)
{
	LevelTriggerManager->UnRegisterTrigger(LevelTriggerInterface);
}

const ULevelTriggerManager* ABaseGameModeBase::GetLevelTriggerManager() const
{
	return LevelTriggerManager;
}

void ABaseGameModeBase::UpdateTrigger(class ILevelTriggerInterface* LevelTriggerInterface, bool bInputIsOnTrigger)
{
	LevelTriggerManager->UpdateTrigger(LevelTriggerInterface, bInputIsOnTrigger);
}

void ABaseGameModeBase::UpdateTriggerOnce(class ILevelTriggerInterface* LevelTriggerInterface)
{
	LevelTriggerManager->UpdateTriggerOnce(LevelTriggerInterface);
}

TSoftObjectPtr<UBaseScreenWidget> ABaseGameModeBase::GetBaseScreenWidget() const
{
	return BaseScreenWidget;
}

void ABaseGameModeBase::SetFocusOnCharacter(bool bIsFocusOnTheCharacter)
{
	ABasePlayerController* BasePlayerController = Cast<ABasePlayerController>( UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if(IsValid(BasePlayerController))
	{
		BasePlayerController->SetFocusOnCharacter(bIsFocusOnTheCharacter);
	}
}

bool ABaseGameModeBase::IsFocusOnCharacter() const
{
	ABasePlayerController* BasePlayerController = Cast<ABasePlayerController>( UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if(IsValid(BasePlayerController))
	{
		return BasePlayerController->IsFocusOnCharacter();
	}

	return true;
}
