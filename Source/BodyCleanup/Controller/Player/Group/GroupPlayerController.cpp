// Fill out your copyright notice in the Description page of Project Settings.


#include "GroupPlayerController.h"
#include "../../../Character/PlayerCharacter/Characters/Morse.h"
#include "../../../Character/PlayerCharacter/Characters/Tank.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../AI/Player/BasePlayerAIController.h"
#include "BodyCleanup/Game/GameMode/MainGameModeBase.h"
#include "BodyCleanup/UI/Screen/MainScreenWidget.h"

AGroupPlayerController::AGroupPlayerController()
{

}

void AGroupPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AGroupPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void AGroupPlayerController::OnStartMatch()
{
	Super::OnStartMatch();
	
	AActor* PlayerStartActor = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass());

	if (IsValid(PlayerStartActor))
	{
		APlayerStart* PlayerStart = Cast<APlayerStart>(PlayerStartActor);

		if (IsValid(AISubCharacterControllerClass.Get()))
		{
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.Instigator = GetInstigator();
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnInfo.OverrideLevel = GetLevel();
			SpawnInfo.ObjectFlags |= RF_Transient;	// We never want to save AI controllers into a map
			SubPlayerController = GetWorld()->SpawnActor<ABasePlayerAIController>(AISubCharacterControllerClass, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation(), SpawnInfo);

			//if (SubPlayerController != nullptr)
			//{
			//	// if successful will result in setting this->Controller 
			//	// as part of possession mechanics
			//	SubPlayerController->Possess(Tank.Get());
			//}
		}

		FActorSpawnParameters ActorSpawnParam;

		ActorSpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		ActorSpawnParam.Owner = this;

		if (IsValid(MorseCharacterClass.Get()))
		{
			Morse = GetWorld()->SpawnActor<AMorse>(MorseCharacterClass, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation(), ActorSpawnParam);

			if (Morse.IsValid())
			{
				Possess(Morse.Get());
			}
		}

		if (IsValid(TankCharacterClass.Get()))
		{
			Tank = GetWorld()->SpawnActor<ATank>(TankCharacterClass, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation(), ActorSpawnParam);

			if (Tank.IsValid())
			{
				SubPlayerController->Possess(Tank.Get());
				Tank->SetFlyMode(Morse);
			}
		}
	}
}

void AGroupPlayerController::InputPressedSwapCharacter()
{
	ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());
	
	if (IsValid(PlayerCharacter))
	{
		if (Morse == PlayerCharacter)
		{
			Possess(Tank.Get());
			Tank->SetAnimationType(EAnimationType::Idle);
			SubPlayerController->Possess(Morse.Get());
			Morse->SetAnimationType(EAnimationType::Wait);

			if (Tank->IsFlyMode())
			{
				Tank->SetFlyMode(nullptr);
			}
		}
		else
		{
			Possess(Morse.Get());
			Morse->SetAnimationType(EAnimationType::Idle);
			SubPlayerController->Possess(Tank.Get());
			Tank->SetAnimationType(EAnimationType::Wait);
		}
	}
}

void AGroupPlayerController::InputPressedReturnToCharacter()
{
	ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

	if (Tank == PlayerCharacter)
	{
		if (false == Tank->IsFlyMode())
		{
			Possess(Morse.Get());
			Morse->SetAnimationType(EAnimationType::Idle);
			SubPlayerController->Possess(Tank.Get());
			Tank->SetAnimationType(EAnimationType::Return);
			Tank->SetFlyMode(Morse);
		}
	}
}