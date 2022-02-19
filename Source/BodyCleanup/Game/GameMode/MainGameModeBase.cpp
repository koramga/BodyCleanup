// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameModeBase.h"
#include "../../UI/Screen/MainScreenWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../../Controller/Player/BasePlayerController.h"
#include "BodyCleanup/Actor/Ragdoll/RobotCorpseActor.h"
#include "BodyCleanup/UI/Screen/PauseMenuScreenWidget.h"

void AMainGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AMainGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(BaseScreenWidget))
	{
		MainScreenWidget = Cast<UMainScreenWidget>(BaseScreenWidget);
	}
	
	if(IsValid(PauseMenuScreenWidgetClass))
	{
		PauseMenuScreenWidget = CreateWidget<UPauseMenuScreenWidget>(GetWorld(), PauseMenuScreenWidgetClass);
		
		if (PauseMenuScreenWidget)
		{
			PauseMenuScreenWidget->AddToViewport();
			PauseMenuScreenWidget->SetHiddenInGame(true);
		}			
	}
}

void AMainGameModeBase::__OnRobotCorpseActorDestroyed(AActor* Actor, EEndPlayReason::Type EndPlayReason)
{
	if(IsValid(MainScreenWidget))
	{
		if(RobotCorpseActors.Remove(Actor) >= 0)
		{
			MainScreenWidget->AddCorpseCount();
		}		
	}
}

TSoftObjectPtr<UMainScreenWidget> AMainGameModeBase::GetMainScreenWidget() const
{
	return Cast<UMainScreenWidget>(MainScreenWidget);
}

TSoftObjectPtr<UPauseMenuScreenWidget> AMainGameModeBase::GetPauseMenuScreenWidget() const
{
	return Cast<UPauseMenuScreenWidget>(PauseMenuScreenWidget);
}

void AMainGameModeBase::TogglePauseMenu()
{
	SetEnablePauseMenu(!IsEnablePauseMenu());
}

bool AMainGameModeBase::IsEnablePauseMenu()
{
	return UGameplayStatics::IsGamePaused(GetWorld());;
}

void AMainGameModeBase::SetEnablePauseMenu(bool bIsEnable)
{
	const bool bIsPauseGame = UGameplayStatics::IsGamePaused(GetWorld());

	if(bIsPauseGame != bIsEnable)
	{
		if(IsValid(PauseMenuScreenWidget))
		{
			PauseMenuScreenWidget->SetHiddenInGame(bIsPauseGame);
		}
	
		UGameplayStatics::SetGamePaused(GetWorld(), !bIsPauseGame);		
	}
}

void AMainGameModeBase::SetRobotCorpse(const TArray<TSoftObjectPtr<ARobotCorpseActor>>& InRobotCorpseActors)
{
	for(const TSoftObjectPtr<ARobotCorpseActor>& RobotCorpseActor : RobotCorpseActors)
	{
		if(RobotCorpseActor.IsValid())
		{
			RobotCorpseActor->OnEndPlay.RemoveDynamic(this, &AMainGameModeBase::__OnRobotCorpseActorDestroyed);
		}
	}
	
	for(const TSoftObjectPtr<ARobotCorpseActor>& RobotCorpseActor : InRobotCorpseActors)
	{
		if(RobotCorpseActor.IsValid())
		{
			RobotCorpseActors.Add(RobotCorpseActor);

			RobotCorpseActor->OnEndPlay.AddDynamic(this, &AMainGameModeBase::__OnRobotCorpseActorDestroyed);
		}		
	}

	if(IsValid(MainScreenWidget))
	{
		MainScreenWidget->SetMaxCorpseCount(RobotCorpseActors.Num());
		MainScreenWidget->ResetCorpseCount();
	}
w}
