// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "../../Character/PlayerCharacter/Characters/Morse.h"
#include "../../Character/PlayerCharacter/Characters/Tank.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../AI/Player/BasePlayerAIController.h"
#include "../../Game/GameMode/MainGameModeBase.h"
#include "../../UI/Screen/MainScreenWidget.h"
#include "../../Game/GameMode/BaseGameModeBase.h"
#include "BodyCleanup/Components/Actor/LevelComponent.h"
#include "BodyCleanup/UI/Screen/PauseMenuScreenWidget.h"
#include "GameFramework/HUD.h"

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
	//InputComponent->BindAction("InputJump", IE_Pressed, this, &ABasePlayerController::__InputPressedJump);
	//InputComponent->BindAction("InputJump", IE_Released, this, &ABasePlayerController::__InputReleasedJump);
	InputComponent->BindAxis("InputMouseWheel", this, &ABasePlayerController::__InputMouseWheel);
	InputComponent->BindAxis("InputMoveForward", this, &ABasePlayerController::__InputMoveForward);
	InputComponent->BindAxis("InputMoveRight", this, &ABasePlayerController::__InputMoveRight);
	InputComponent->BindAction("InputInteractive", IE_Pressed, this, &ABasePlayerController::__InputPressedInteractive);
	InputComponent->BindAction("InputInteractive", IE_Released, this, &ABasePlayerController::__InputReleasedInteractive);
	InputComponent->BindAction("InputUITestKey", IE_Pressed, this, &ABasePlayerController::__InputPressedUITestKey);
	InputComponent->BindAction("InputUIUp", IE_Pressed, this, &ABasePlayerController::__InputPressedUIUp);
	InputComponent->BindAction("InputUIDown", IE_Pressed, this, &ABasePlayerController::__InputPressedUIDown);
	InputComponent->BindAction("InputEnter", IE_Pressed, this, &ABasePlayerController::__InputPressedEnter);
	InputComponent->BindAction("InputToggleMoving", IE_Pressed, this, &ABasePlayerController::__InputPressedToggleMoving);
	InputComponent->BindAction("InputMouseWheelClick", IE_Pressed, this, &ABasePlayerController::__InputPressedMouseWheelClick);
	InputComponent->BindAction("InputMouseWheelClick", IE_Released, this, &ABasePlayerController::__InputReleasedMouseWheelClick);
	InputComponent->BindAction("InputSpacebar", IE_Pressed, this, &ABasePlayerController::__InputPressedSpacebar);
	InputComponent->BindAction("InputSpacebar", IE_Released, this, &ABasePlayerController::__InputReleasedSpacebar);
	
	FInputActionBinding& PauseActionBinding = InputComponent->BindAction("InputPauseMenu", IE_Pressed, this, &ABasePlayerController::__InputPressedPauseMenu);

	PauseActionBinding.bExecuteWhenPaused = true;
}

void ABasePlayerController::InputPressedSwapCharacter()
{
}

void ABasePlayerController::InputPressedReturnToCharacter()
{
}

void ABasePlayerController::__InputMoveForward(float InputAxis)
{
	if(bIsFocusOnCharacter)
	{
		ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->InputMoveForward(InputAxis);
		}		
	}
}

void ABasePlayerController::__InputMoveRight(float InputAxis)
{
	if(bIsFocusOnCharacter)
	{
		ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->InputMoveRight(InputAxis);
		}
	}
}

void ABasePlayerController::__InputMouseWheel(float InputAxis)
{
	if(bIsFocusOnCharacter)
	{
		ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->InputMouseWheel(InputAxis);
		}
	}
}

void ABasePlayerController::__InputPressedMouseLeftClick()
{
	if(bIsFocusOnCharacter)
	{
		ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->InputPressedMouseLeftClick();
		}
	}
}

void ABasePlayerController::__InputReleasedMouseLeftClick()
{
	if(bIsFocusOnCharacter)
	{
		ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->InputReleasedMouseLeftClick();
		}
	}
}

void ABasePlayerController::__InputPressedMouseRightClick()
{
	if(bIsFocusOnCharacter)
	{
		ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->InputPressedMouseRightClick();
		}
	}
	else
	{
		ABaseGameModeBase* BaseGameModeBase = Cast<ABaseGameModeBase>(GetWorld()->GetAuthGameMode());

		if(IsValid(BaseGameModeBase))
		{
			TSoftObjectPtr<UBaseScreenWidget> BaseScreenWidget = BaseGameModeBase->GetBaseScreenWidget();

			if(BaseScreenWidget.IsValid())
			{
				BaseScreenWidget->InputEnter();
			}
		}		
	}
}

void ABasePlayerController::__InputReleasedMouseRightClick()
{
	if(bIsFocusOnCharacter)
	{
		ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->InputReleasedMouseRightClick();
		}
	}
}

void ABasePlayerController::__InputPressedMouseWheelClick()
{
	if(bIsFocusOnCharacter)
	{
		ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->InputPressedMouseWheelClick();
		}
	}
}

void ABasePlayerController::__InputReleasedMouseWheelClick()
{
	if(bIsFocusOnCharacter)
	{
		ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->InputReleasedMouseWheelClick();
		}
	}
}

void ABasePlayerController::__InputPressedSwapCharacter()
{
	if(bIsFocusOnCharacter)
	{
		InputPressedSwapCharacter();
	}
}

void ABasePlayerController::__InputPressedReturnToTank()
{
	if(bIsFocusOnCharacter)
	{
		InputPressedReturnToCharacter();
	}
}

void ABasePlayerController::__InputPressedJump()
{
	if(bIsFocusOnCharacter)
	{
		ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->InputJump();
		}
	}
}

void ABasePlayerController::__InputReleasedJump()
{
	if(bIsFocusOnCharacter)
	{
		ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->InputStopJumping();
		}
	}
}

void ABasePlayerController::__InputPressedInteractive()
{
	if(bIsFocusOnCharacter)
	{
		ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->InputPressedInteractive();
		}
	}
}

void ABasePlayerController::__InputReleasedInteractive()
{
	if(bIsFocusOnCharacter)
	{
		ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->InputReleasedInteractive();
		}
	}
}

void ABasePlayerController::__InputPressedSpacebar()
{
	if(bIsFocusOnCharacter)
	{
		ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->InputPressedSpacebar();
		}
	}
}

void ABasePlayerController::__InputReleasedSpacebar()
{
	if(bIsFocusOnCharacter)
	{
		ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->InputReleasedSpacebar();
		}
	}
}

void ABasePlayerController::__InputPressedUITestKey()
{
	float Range = FMath::RandRange(0.f, 10.f);

	if(Range < 5.f)
	{
		AMainGameModeBase* MainGameMode = Cast<AMainGameModeBase>(GetWorld()->GetAuthGameMode());
	
		if(IsValid(MainGameMode))
		{
			TSoftObjectPtr<UMainScreenWidget> MainScreenWidget = MainGameMode->GetMainScreenWidget();

			if(MainScreenWidget.IsValid())
			{
				MainScreenWidget->SetScreenScriptText("koramga", "Test Text");
				MainScreenWidget->SetHiddenInGameScreenScript(false);
			}
		}
	}
	else
	{
		AMainGameModeBase* MainGameMode = Cast<AMainGameModeBase>(GetWorld()->GetAuthGameMode());
	
		if(IsValid(MainGameMode))
		{
			TSoftObjectPtr<UMainScreenWidget> MainScreenWidget = MainGameMode->GetMainScreenWidget();

			if(MainScreenWidget.IsValid())
			{
				TArray<FString> SelectTexts;
				SelectTexts.Add(TEXT("첫 번째 선택 조항"));
				SelectTexts.Add(TEXT("두 번째 선택 조항"));
				SelectTexts.Add(TEXT("세 번째 선택 조항"));
				SelectTexts.Add(TEXT("네 번째 선택 조항"));
				SelectTexts.Add(TEXT("다섯 번째 선택 조항"));
				SelectTexts.Add(TEXT("여섯 번째 선택 조항"));
		
				MainScreenWidget->SetScreenSelectScriptTexts(FMath::RandRange(1.f, 10.f), SelectTexts);
				MainScreenWidget->SetHiddenInGameScreenSelectScript(false);
		
				ABasePlayerController* BasePlayerController = Cast<ABasePlayerController>( UGameplayStatics::GetPlayerController(GetWorld(), 0));

				if(IsValid(BasePlayerController))
				{
					BasePlayerController->SetFocusOnCharacter(false);
				}
			}
		}		
	}	
}

void ABasePlayerController::__InputPressedUIUp()
{
	if(false == bIsFocusOnCharacter)
	{
		ABaseGameModeBase* BaseGameModeBase = Cast<ABaseGameModeBase>(GetWorld()->GetAuthGameMode());

		if(IsValid(BaseGameModeBase))
		{
			TSoftObjectPtr<UBaseScreenWidget> BaseScreenWidget = BaseGameModeBase->GetBaseScreenWidget();

			if(BaseScreenWidget.IsValid())
			{
				BaseScreenWidget->InputUp();
			}
		}		
	}
}

void ABasePlayerController::__InputPressedUIDown()
{
	if(false == bIsFocusOnCharacter)
	{
		ABaseGameModeBase* BaseGameModeBase = Cast<ABaseGameModeBase>(GetWorld()->GetAuthGameMode());

		if(IsValid(BaseGameModeBase))
		{
			TSoftObjectPtr<UBaseScreenWidget> BaseScreenWidget = BaseGameModeBase->GetBaseScreenWidget();

			if(BaseScreenWidget.IsValid())
			{
				BaseScreenWidget->InputDown();
			}
		}
	}
}

void ABasePlayerController::__InputPressedEnter()
{
	if(false == bIsFocusOnCharacter)
	{
		ABaseGameModeBase* BaseGameModeBase = Cast<ABaseGameModeBase>(GetWorld()->GetAuthGameMode());

		if(IsValid(BaseGameModeBase))
		{
			TSoftObjectPtr<UBaseScreenWidget> BaseScreenWidget = BaseGameModeBase->GetBaseScreenWidget();

			if(BaseScreenWidget.IsValid())
			{
				BaseScreenWidget->InputEnter();
			}
		}		
	}
}

void ABasePlayerController::__InputPressedPauseMenu()
{
	AMainGameModeBase* MainGameModeBase = Cast<AMainGameModeBase>(GetWorld()->GetAuthGameMode());

	if(IsValid(MainGameModeBase))
	{
		MainGameModeBase->TogglePauseMenu();
	}
}

void ABasePlayerController::__InputPressedToggleMoving()
{
	if(bIsFocusOnCharacter)
	{
		ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->InputPressedToggleMoving();
		}
	}
}

void ABasePlayerController::SetFocusOnCharacter(bool bInIsFocusOnCharacter)
{
	bIsFocusOnCharacter = bInIsFocusOnCharacter;
	
	if(bIsFocusOnCharacter)
	{
		ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

		if(IsValid(PlayerCharacter))
		{
			PlayerCharacter->SetFocusOn(true);		
		}
	}
	else
	{
		ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

		if(IsValid(PlayerCharacter))
		{
			PlayerCharacter->SetFocusOn(false);		
		}
	}
}

bool ABasePlayerController::IsFocusOnCharacter() const
{
	return bIsFocusOnCharacter;
}

bool ABasePlayerController::GetHitResultsAtScreenPosition(TArray<FHitResult>& HitResults,
	const FVector2D ScreenPosition, const ECollisionChannel TraceChannel,
	const FCollisionQueryParams& CollisionQueryParams) const
{
	// Early out if we clicked on a HUD hitbox
	if (GetHUD() != NULL && GetHUD()->GetHitBoxAtCoordinates(ScreenPosition, true))
	{
		return false;
	}

	FVector WorldOrigin;
	FVector WorldDirection;
	if (UGameplayStatics::DeprojectScreenToWorld(this, ScreenPosition, WorldOrigin, WorldDirection) == true)
	{
		
//#ifdef ENABLE_DRAW_DEBUG
//
//		//FColor DrawColor = bIsGoal ? FColor::Red : FColor::Green;
//		DrawDebugSphere(GetWorld(), WorldOrigin, 20.f, 20, FColor::Yellow, false, 0.5f);
//
//		DrawDebugLine(GetWorld(), WorldOrigin, WorldOrigin + WorldDirection * HitResultTraceDistance, FColor::Green, false, 0.5f);
//	
//#endif 
	
		return GetWorld()->LineTraceMultiByChannel(HitResults, WorldOrigin, WorldOrigin + WorldDirection * HitResultTraceDistance, TraceChannel);
	}

	return false;
}

bool ABasePlayerController::GetHitResultsAtScreenPosition(TArray<FHitResult>& HitResults, FVector2D ScreenPosition,
                                                          ECollisionChannel CollisionChannel, bool bTraceComplex)
{
	FCollisionQueryParams CollisionQueryParams(SCENE_QUERY_STAT(ClickableTrace), bTraceComplex );
	
	return GetHitResultsAtScreenPosition( HitResults, ScreenPosition, CollisionChannel, CollisionQueryParams );
}

bool ABasePlayerController::GetHitResultsAtMousePosition(TArray<FHitResult>& HitResults, ETraceTypeQuery TraceChannel,
                                                         bool bTraceComplex)
{
	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	bool bHit = false;
	if (LocalPlayer && LocalPlayer->ViewportClient)
	{
		FVector2D MousePosition;
		if (LocalPlayer->ViewportClient->GetMousePosition(MousePosition))
		{
			return GetHitResultsAtScreenPosition( HitResults, MousePosition, UEngineTypes::ConvertToCollisionChannel( TraceChannel ), bTraceComplex);
		}
	}

	return false;
}

bool ABasePlayerController::GetLevelHitResultAtMousePosition(FHitResult& OutHitResult)
{
	TArray<FHitResult> HitResults;
					
	GetHitResultsAtMousePosition(HitResults, UEngineTypes::ConvertToTraceType( ECC_GameTraceChannel4 ), true);
	
//#ifdef ENABLE_DRAW_DEBUG
//	
//	UE_LOG(LogTemp, Display, TEXT("<%d>"), HitResults.Num());
//	
//	for(const FHitResult& HitResult : HitResults)
//	{
//		UE_LOG(LogTemp, Display, TEXT("HitResult : <%s>"), *HitResult.Actor->GetName());
//		//FColor DrawColor = bIsGoal ? FColor::Red : FColor::Green;
//		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 20.f, 20, FColor::Red, false, 0.5f);
//
//		DrawDebugLine(GetWorld(), HitResult.ImpactPoint - HitResult.ImpactNormal * 200, HitResult.ImpactPoint + HitResult.ImpactNormal * 200, FColor::Blue, false, 0.5f);
//	
//	}
//	
//#endif
	
	for(const FHitResult& HitResult : HitResults)
	{
		if(HitResult.Actor.IsValid()
			&& HitResult.Actor != this)
		{
			ULevelComponent* LevelComponent = HitResult.Actor->FindComponentByClass<ULevelComponent>();

			if(IsValid(LevelComponent))
			{
				OutHitResult = HitResult;
				return true;
			}
		}
	}
	
	return false;
}

ETeamType ABasePlayerController::GetTeamType() const
{
	return ETeamType::Player;
}

TBlackboardVariable ABasePlayerController::GetBlackboardVariable(const FName& Name, EBlackboardVariableType BlackboardVariableType) const
{
	return TBlackboardVariable();
}

bool ABasePlayerController::SetBlackboardVariable(const FName& Name, const TBlackboardVariable& Variable)
{
	return false;
}

bool ABasePlayerController::IsDeathPossessActor() const
{
	ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

	if (IsValid(PlayerCharacter))
	{
		return PlayerCharacter->IsDeath();
	}

	return true;
}

FVector ABasePlayerController::GetCharacterLocation() const
{	
	ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

	if (IsValid(PlayerCharacter))
	{
		return PlayerCharacter->GetActorLocation();
	}

	return FVector();
}

AActor* ABasePlayerController::GetPossessActor() const
{
	ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(GetCharacter());

	if (IsValid(PlayerCharacter))
	{
		return PlayerCharacter;
	}

	return nullptr;
}

bool ABasePlayerController::CanMovePossessActor() const
{
	return false;
}

bool ABasePlayerController::CanUpdateAnimationPossessActor(uint8 InAnimationType) const
{
	return false;
}

FBTAbilityInfo ABasePlayerController::GetAbilityInfoByTag(const FGameplayTag& Tag) const
{
	return FBTAbilityInfo();
}

bool ABasePlayerController::ActivateAbilityByTag(const FGameplayTag& Tag)
{
	return false;
}

bool ABasePlayerController::DeActivateAbilityByTag(const FGameplayTag& Tag)
{
	return false;
}

EBTPatrolType ABasePlayerController::GetPatrolType() const
{
	return EBTPatrolType::None;
}

IBTPatrolActorInterface* ABasePlayerController::GetPatrolActorInterface() const
{
	return nullptr;
}

void ABasePlayerController::SetNextPatrol()
{
	
}

FBTPatrolInfo ABasePlayerController::GetPatrolInfo() const
{
	return FBTPatrolInfo();
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}
