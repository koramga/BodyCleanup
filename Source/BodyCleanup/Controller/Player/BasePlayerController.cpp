// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "../../Character/PlayerCharacter/Characters/Morse.h"
#include "../../Character/PlayerCharacter/Characters/Tank.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../AI/Player/BasePlayerAIController.h"

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
	InputComponent->BindAxis("InputMouseWheel", this, &ABasePlayerController::__InputMouseWheel);
	InputComponent->BindAxis("InputMoveForward", this, &ABasePlayerController::__InputMoveForward);
	InputComponent->BindAxis("InputMoveRight", this, &ABasePlayerController::__InputMoveRight);

}

void ABasePlayerController::InputPressedSwapCharacter()
{
}

void ABasePlayerController::InputPressedReturnToCharacter()
{
}

void ABasePlayerController::__InputMoveForward(float InputAxis)
{
	ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->InputMoveForward(InputAxis);
	}
}

void ABasePlayerController::__InputMoveRight(float InputAxis)
{
	ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->InputMoveRight(InputAxis);
	}
}

void ABasePlayerController::__InputMouseWheel(float InputAxis)
{
	ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->InputMouseWheel(InputAxis);
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
	InputPressedSwapCharacter();
}

void ABasePlayerController::__InputPressedReturnToTank()
{
	InputPressedReturnToCharacter();
}

void ABasePlayerController::__InputPressedJump()
{
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
}

void ABasePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}