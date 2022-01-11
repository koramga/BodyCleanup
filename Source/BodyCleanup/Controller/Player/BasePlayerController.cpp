// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "../../Character/PlayerCharacter/Characters/Morse.h"
#include "../../Character/PlayerCharacter/Characters/Tank.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/CharacterMovementComponent.h"

ABasePlayerController::ABasePlayerController()
{
	bShowMouseCursor = true;

	
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAction("InputMouseLeftClick", IE_Pressed, this, &ABasePlayerController::__InputPressedMouseLeftClick);
	InputComponent->BindAction("InputMouseLeftClick", IE_Released, this, &ABasePlayerController::__InputReleasedMouseLeftClick);
	InputComponent->BindAction("InputMouseRightClick", IE_Pressed, this, &ABasePlayerController::__InputPressedMouseRightClick);
	InputComponent->BindAction("InputMouseRightClick", IE_Released, this, &ABasePlayerController::__InputReleasedMouseRightClick);
	InputComponent->BindAction("InputSwapCharacter", IE_Pressed, this, &ABasePlayerController::__InputPressedSwapCharacter);
	InputComponent->BindAction("InputReturnToTank", IE_Pressed, this, &ABasePlayerController::__InputPressedReturnToTank);
	InputComponent->BindAction("InputJump", IE_Pressed, this, &ABasePlayerController::__InputPressedJump);
	InputComponent->BindAction("InputJump", IE_Released, this, &ABasePlayerController::__InputReleasedJump);
	InputComponent->BindAxis("MoveForward", this, &ABasePlayerController::__InputMoveForward);
	InputComponent->BindAxis("MoveRight", this, &ABasePlayerController::__InputMoveRight);

}

void ABasePlayerController::__InputMoveForward(float InputAxis)
{
	ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->MoveForward(InputAxis);
	}
}

void ABasePlayerController::__InputMoveRight(float InputAxis)
{
	ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->MoveRight(InputAxis);
	}
}

void ABasePlayerController::__InputPressedMouseLeftClick()
{
	ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->InputPressedMouseLeftClick();
	}
}

void ABasePlayerController::__InputReleasedMouseLeftClick()
{
	ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->InputReleasedMouseLeftClick();
	}
}

void ABasePlayerController::__InputPressedMouseRightClick()
{
	ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->InputPressedMouseRightClick();
	}
}

void ABasePlayerController::__InputReleasedMouseRightClick()
{
	ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->InputReleasedMouseRightClick();
	}
}

void ABasePlayerController::__InputPressedSwapCharacter()
{
	ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

	if (IsValid(PlayerCharacter))
	{
		if (Morse == PlayerCharacter)
		{
			Possess(Tank);
			//if (false == Tank->IsFlyMode())
			//{
			//	Tank->SetFlyMode(Morse);
			//}

			if (Tank->IsFlyMode())
			{
				Tank->SetFlyMode(nullptr);
			}

		}
		else
		{
			Possess(Morse);

			//Tank->SetFlyMode(Morse);
		}
	}
}

void ABasePlayerController::__InputPressedReturnToTank()
{
	ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

	if (Tank == PlayerCharacter)
	{
		if (false == Tank->IsFlyMode())
		{
			Tank->SetFlyMode(Morse);
		}
	}

}

void ABasePlayerController::__InputPressedJump()
{
	UE_LOG(LogTemp, Display, TEXT("Jump"));

	ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->InputJump();
	}
}

void ABasePlayerController::__InputReleasedJump()
{
	ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->InputStopJumping();
	}
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	AActor* PlayerStartActor = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass());

	if (IsValid(PlayerStartActor))
	{
		APlayerStart* PlayerStart = Cast<APlayerStart>(PlayerStartActor);

		FActorSpawnParameters ActorSpawnParam;

		ActorSpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		ActorSpawnParam.Owner = this;

		if (IsValid(MorseCharacterClass.Get()))
		{
			Morse = GetWorld()->SpawnActor<AMorse>(MorseCharacterClass, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation(), ActorSpawnParam);

			if (IsValid(Morse))
			{
				Possess(Morse);
			}
		}

		if (IsValid(TankCharacterClass.Get()))
		{
			Tank = GetWorld()->SpawnActor<ATank>(TankCharacterClass, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation(), ActorSpawnParam);

			if (IsValid(Tank))
			{
				Tank->SetFlyMode(Morse);
			}
		}
	}

}

void ABasePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	SetControlRotation(FRotator(0.f, QUARTER_VIEW_ANGLE, 0.f));

	UpdateRotation(DeltaTime);
}