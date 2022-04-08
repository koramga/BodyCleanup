// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameModeBase.h"
#include "../../UI/Screen/MainScreenWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../../Controller/Player/BasePlayerController.h"
#include "BodyCleanup/Actor/Ragdoll/RobotCorpseActor.h"
#include "BodyCleanup/UI/Screen/PauseMenuScreenWidget.h"
#include "GameFramework/PlayerStart.h"

void AMainGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AMainGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	bIsNeedDungeonBuild = true;

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

	BeginPlayForDungeonArchitecture();
}

void AMainGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMainGameModeBase::BeginPlayForDungeonArchitecture()
{
	Dungeon = Cast<ADungeon>(UGameplayStatics::GetActorOfClass(GetWorld(), ADungeon::StaticClass()));

	if(IsValid(Dungeon))
	{
		Dungeon->LevelStreamingModel->OnInitialChunksLoaded.AddDynamic(this, &AMainGameModeBase::OnInitialChunksLoaded);
		BuildDungeon();
	}
}

void AMainGameModeBase::OnInitialChunksLoaded(ADungeon* InDungeon)
{
	bIsDungeonReady = true;
}

void AMainGameModeBase::BuildDungeon()
{
	if(IsValid(Dungeon) && bIsNeedDungeonBuild)
	{
		bIsDungeonReady = false;
		bIsNeedDungeonBuild = !bIsNeedDungeonBuild;
		Dungeon->Config->Seed = UKismetMathLibrary::RandomInteger(10000);
		Dungeon->BuildDungeon();
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
}
