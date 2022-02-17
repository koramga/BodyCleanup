// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameModeBase.h"
#include "BodyCleanup/UI/Screen/MainMenuScreenWidget.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

void AMainMenuGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AMainMenuGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(BaseScreenWidget))
	{
		MainMenuScreenWidget = Cast<UMainMenuScreenWidget>(BaseScreenWidget);
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if(IsValid(PlayerController))
	{
		PlayerController->SetShowMouseCursor(true);
	}

	TArray<AActor*> Actors;
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), Actors);

	if(Actors.Num() > 0)
	{
		if(IsValid(Actors[0]))
		{
			PlayerController->SetViewTargetWithBlend(Actors[0], 0.f);
		}		
	}
}
