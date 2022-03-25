// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../Animation/PlayerCharacter/PlayerCharacterAnimInstance.h"
#include "BodyCleanup/Game/GameMode/MainGameModeBase.h"
#include "BodyCleanup/UI/Screen/MainScreenWidget.h"
#include "GameFramework/GameModeBase.h"

// Sets default values
ABasePlayerCharacter::ABasePlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	//Arm을 Root에 붙여준다.
	SpringArmComponent->SetupAttachment(RootComponent);

	//Camera를 Arm에 붙여준다.
	CameraComponent->SetupAttachment(SpringArmComponent);
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	//bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	
	SpringArmComponent->SetRelativeRotation(FRotator(-30, 0, 0)); // The camera follows at this distance behind the character	
	SpringArmComponent->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	SpringArmComponent->bInheritPitch = false; // Rotate the arm based on the controller	
	SpringArmComponent->bInheritRoll = false; // Rotate the arm based on the controller	
	SpringArmComponent->bInheritYaw = false; // Rotate the arm based on the controller	
	SpringArmComponent->TargetArmLength = 2000;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->CameraLagSpeed = 10.0f;
	SpringArmComponent->bDoCollisionTest = false;

	// Create a follow camera
	CameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	CameraComponent->FieldOfView = 45;

}

// Called when the game starts or when spawned
void ABasePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(BaseAnimInstance))
	{
		PlayerCharacterAnimInstance = Cast<UPlayerCharacterAnimInstance>(BaseAnimInstance);
	}
}

// Called every frame
void ABasePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePlayerCharacter::UpdateDeath(bool bInIsDeath)
{
	Super::UpdateDeath(bInIsDeath);

	if (true == bInIsDeath)
	{
		AGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode();

		if(IsValid(GameModeBase))
		{
			FString LevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
			UGameplayStatics::OpenLevel(GetWorld(), *LevelName);			
		}
	}
}

void ABasePlayerCharacter::SetKeyboardControlType(EKeyboardControlType KeyboardControlType)
{
	AMainGameModeBase* MainGameModeBase = Cast<AMainGameModeBase>(GetWorld()->GetAuthGameMode());
	TSoftObjectPtr<UMainScreenWidget> MainScreenWidget;
	
	if(nullptr != MainGameModeBase)
	{
		MainScreenWidget = MainGameModeBase->GetMainScreenWidget();

		if(MainScreenWidget.IsValid())
		{
			MainScreenWidget->SetKeyboardControlType(KeyboardControlType);
		}
	}
}

void ABasePlayerCharacter::SetEnableAttack(bool bIsEnableAttack)
{
	Super::SetEnableAttack(bIsEnableAttack);
}

bool ABasePlayerCharacter::IsPressedLeftMouse() const
{
	return bIsPressedLeftMouse;
}

bool ABasePlayerCharacter::IsPressedRightMouse() const
{
	return bIsPressedRightMouse;
}

bool ABasePlayerCharacter::IsPressedWheelMouse() const
{
	return bIsPressedWheelMouse;
}

bool ABasePlayerCharacter::IsPressedInteractive() const
{
	return bIsPressedInteractive;
}

void ABasePlayerCharacter::InputMoveForward(float InputAxis)
{
	if (IsValid(PlayerCharacterAnimInstance))
	{
		if (PlayerCharacterAnimInstance->CanMove())
		{
			if (InputAxis == 0)
			{
				MoveOffset &= ~MOVE_FORWARD;
				MoveOffset &= ~MOVE_BACK;
				return;
			}
			else if (InputAxis > 0.f)
			{
				MoveOffset |= MOVE_FORWARD;
			}
			else if (InputAxis < 0.f)
			{
				MoveOffset |= MOVE_BACK;
			}

			if (IsValid(Controller))
			{
				//if (Cast<ACPlayerController>(Controller)->bOnClick) return;
				// find out which way is forward
				//const FRotator Rotation = Controller->GetControlRotation();
				//const FRotator YawRotation(0, Rotation.Yaw, 0);
				const FRotator YawRotation(0, QUARTER_VIEW_ANGLE, 0);

				// get forward vector
				const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
				AddMovementInput(Direction, InputAxis);
			}

			if (IsValid(PlayerCharacterAnimInstance))
			{
				PlayerCharacterAnimInstance->SetMoveOffset(MoveOffset);
			}
		}
	}
}

void ABasePlayerCharacter::InputMoveRight(float InputAxis)
{
	if (IsValid(PlayerCharacterAnimInstance))
	{
		if (PlayerCharacterAnimInstance->CanMove())
		{
			if (InputAxis == 0.f)
			{
				MoveOffset &= ~MOVE_RIGHT;
				MoveOffset &= ~MOVE_LEFT;
				return;
			}
			else if (InputAxis > 0.f)
			{
				MoveOffset |= MOVE_RIGHT;
			}
			else if (InputAxis < 0.f)
			{
				MoveOffset |= MOVE_LEFT;
			}

			if (IsValid(Controller))
			{
				//	if (Cast<ACPlayerController>(Controller)->bOnClick) return;
					// find out which way is right
				//const FRotator Rotation = Controller->GetControlRotation();
				const FRotator YawRotation(0, QUARTER_VIEW_ANGLE, 0.f);

				// get right vector 
				const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
				// add movement in that direction
				AddMovementInput(Direction, InputAxis);
			}

			if (IsValid(PlayerCharacterAnimInstance))
			{
				PlayerCharacterAnimInstance->SetMoveOffset(MoveOffset);
			}
		}
	}
}

void ABasePlayerCharacter::InputMouseWheel(float InputAxis)
{

}

void ABasePlayerCharacter::InputJump()
{
	Jump();
}

void ABasePlayerCharacter::InputStopJumping()
{
	StopJumping();
}

void ABasePlayerCharacter::InputPressedMouseLeftClick()
{
	bIsPressedLeftMouse = true;
}

void ABasePlayerCharacter::InputReleasedMouseLeftClick()
{
	bIsPressedLeftMouse = false;
}

void ABasePlayerCharacter::InputPressedMouseRightClick()
{
	bIsPressedRightMouse = true;
}

void ABasePlayerCharacter::InputReleasedMouseRightClick()
{
	bIsPressedRightMouse = false;
}

void ABasePlayerCharacter::InputPressedMouseWheelClick()
{
	bIsPressedWheelMouse = true;
}

void ABasePlayerCharacter::InputReleasedMouseWheelClick()
{
	bIsPressedWheelMouse = false;
}

void ABasePlayerCharacter::InputPressedInteractive()
{
	bIsPressedInteractive = true;
}

void ABasePlayerCharacter::InputReleasedInteractive()
{
	bIsPressedInteractive = false;
}

void ABasePlayerCharacter::InputPressedToggleMoving()
{
	if(FMath::IsNearlyEqual(MoveBlendRatio, 1.f))
	{
		MoveBlendRatio = 0.5f;
	}
	else
	{
		MoveBlendRatio = 1.f;
	}
}
