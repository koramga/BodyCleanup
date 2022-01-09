// Fill out your copyright notice in the Description page of Project Settings.


#include "Morse.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../../Animation/PlayerCharacter/PlayerCharacterAnimInstance.h"
#include "../../../Actor/Level/BaseLevelActor.h"
#include "../../../Character/BaseCharacter.h"
#include "../../../Components/InteractiveMovementComponent.h"
#include "Components/PrimitiveComponent.h"

AMorse::AMorse()
{
}

void AMorse::BeginPlay()
{
	Super::BeginPlay();

	TArray<UActorComponent*> Ranges = GetComponentsByTag(UStaticMeshComponent::StaticClass(), TEXT("VaccumRange"));
	
	for (UActorComponent* ActorComponent : Ranges)
	{
		UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(ActorComponent);

		if (IsValid(PrimitiveComponent))
		{
			UE_LOG(LogTemp, Display, TEXT("VaccumRange PrimitiveComponent : <%s>"), *PrimitiveComponent->GetName());
			PrimitiveComponent->OnComponentBeginOverlap.Clear();
			PrimitiveComponent->OnComponentEndOverlap.Clear();

			PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &AMorse::__OnVaccumRangeOverlapBegin);
			PrimitiveComponent->OnComponentEndOverlap.AddDynamic(this, &AMorse::__OnVaccumRangeOverlapEnd);
		}
	}

	TArray<UActorComponent*> VaccumCollisions = GetComponentsByTag(UPrimitiveComponent::StaticClass(), TEXT("VaccumCollision"));

	if (VaccumCollisions.Num() > 0)
	{
		VaccumPrimitiveComponent = Cast<UPrimitiveComponent>(VaccumCollisions[0]);
		VaccumPrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &AMorse::__OnVaccumOverlapBegin);
	}
}

void AMorse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(BaseController))
	{
		FHitResult Hit;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursor(ECC_WorldStatic, false, Hit);

		if (Hit.bBlockingHit)
		{
			if (Hit.Actor != this)
			{
				//Look Mouse
				//UE_LOG(LogTemp, Display, TEXT("HitActor : <%s>"), *Hit.Actor->GetName());
				FRotator tempRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Hit.ImpactPoint);
				tempRot.Pitch = 0;
				tempRot.Roll = 0;
				SetActorRotation(tempRot);
			}
		}
	}

	if (IsValid(PlayerCharacterAnimInstance))
	{
		EAnimationType AnimationType = PlayerCharacterAnimInstance->GetAnimationType();

		if (EAnimationType::Shot == AnimationType)
		{
			if (IsValid(VaccumPrimitiveComponent))
			{
				const FTransform& WorldTransform = VaccumPrimitiveComponent->GetComponentToWorld();

				UInteractiveMovementComponent* InputInteractiveMovementComponent = nullptr;

				for (AActor* VaccumActor : VaccumOverlapActors)
				{
					InputInteractiveMovementComponent = nullptr;

					if (VaccumActor->IsA(ABaseLevelActor::StaticClass()))
					{
						InputInteractiveMovementComponent = Cast<ABaseActor>(VaccumActor)->GetInteractiveMovementComponent();
					}
					else if (VaccumActor->IsA(ABaseCharacter::StaticClass()))
					{
						InputInteractiveMovementComponent = Cast<ABaseCharacter>(VaccumActor)->GetInteractiveMovementComponent();
					}

					if (IsValid(InputInteractiveMovementComponent))
					{
						InputInteractiveMovementComponent->SetInteractiveTransform(WorldTransform);

						if (EInteractiveAction::None == InputInteractiveMovementComponent->GetInteractiveAction())
						{
							InputInteractiveMovementComponent->SetInteractiveAction(EInteractiveAction::Absorbing);
						}
					}
				}
			}
		}
	}
}

void AMorse::MoveForward(float InputAxis)
{
	Super::MoveForward(InputAxis);
}

void AMorse::MoveRight(float InputAxis)
{
	Super::MoveRight(InputAxis);
}

void AMorse::InputPressedMouseLeftClick()
{
	if (IsValid(PlayerCharacterAnimInstance))
	{
		PlayerCharacterAnimInstance->SetAnimationType(EAnimationType::Shot);
	}
}

void AMorse::InputReleasedMouseLeftClick()
{
	if (IsValid(PlayerCharacterAnimInstance))
	{
		PlayerCharacterAnimInstance->SetAnimationType(EAnimationType::Idle);
	}
}

void AMorse::__OnVaccumRangeOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (false == VaccumOverlapActors.Contains(OtherActor))
	{
		if (OtherActor->IsA(ABaseActor::StaticClass()))
		{
			ABaseActor* BaseActor = Cast<ABaseActor>(OtherActor);

			if (IsValid(BaseActor))
			{
				if (BaseActor->IsInteractiveActor())
				{
					UE_LOG(LogTemp, Display, TEXT("BeginOverlap <%s> : <%s>"), *OverlappedComp->GetName(), *OtherActor->GetName());
					VaccumOverlapActors.Add(OtherActor);
				}
			}
		}
		else if (OtherActor->IsA(ABaseCharacter::StaticClass()))
		{
			ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(OtherActor);

			if (IsValid(BaseCharacter))
			{
				if (BaseCharacter->IsInteractiveCharacter())
				{
					UE_LOG(LogTemp, Display, TEXT("BeginOverlap <%s> : <%s>"), *OverlappedComp->GetName(), *OtherActor->GetName());
					VaccumOverlapActors.Add(OtherActor);
				}
			}
		}
	}
}

void AMorse::__OnVaccumRangeOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (VaccumOverlapActors.Contains(OtherActor))
	{
		VaccumOverlapActors.Remove(OtherActor);

		//UE_LOG(LogTemp, Display, TEXT("EndOverlap <%s> : <%s>"), *OverlappedComp->GetName(), *OtherActor->GetName());

		UInteractiveMovementComponent* InputInteractiveMovementComponent = nullptr;

		if (OtherActor->IsA(ABaseLevelActor::StaticClass()))
		{
			InputInteractiveMovementComponent = Cast<ABaseActor>(OtherActor)->GetInteractiveMovementComponent();
		}
		else if (OtherActor->IsA(ABaseCharacter::StaticClass()))
		{
			InputInteractiveMovementComponent = Cast<ABaseCharacter>(OtherActor)->GetInteractiveMovementComponent();
		}

		if (IsValid(InputInteractiveMovementComponent))
		{
			if (EInteractiveAction::None != InputInteractiveMovementComponent->GetInteractiveAction())
			{
				InputInteractiveMovementComponent->SetInteractiveAction(EInteractiveAction::None);
			}
		}
	}	
}

void AMorse::__OnVaccumOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ABaseActor::StaticClass()))
	{
		ABaseActor* BaseActor = Cast<ABaseActor>(OtherActor);

		if (IsValid(BaseActor))
		{
			if (BaseActor->IsInteractiveActor())
			{
				UInteractiveMovementComponent* InputInteractiveMovementComponent = BaseActor->GetInteractiveMovementComponent();

				if (EInteractiveAction::Absorbing == InputInteractiveMovementComponent->GetInteractiveAction())
				{
					if (EInteractiveType::Junk == InputInteractiveMovementComponent->GetInteractiveType())
					{
						//해당 Actor는 소멸되어야한다.
						VaccumOverlapActors.Remove(BaseActor);
						BaseActor->Destroy();
					}
					else if (EInteractiveType::Rigid == InputInteractiveMovementComponent->GetInteractiveType())
					{
						InputInteractiveMovementComponent->SetInteractiveAction(EInteractiveAction::Holding);
					}
				}
			}
		}
	}
	//else if (OtherActor->IsA(ABaseCharacter::StaticClass()))
	//{
	//	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(OtherActor);
	//
	//	if (IsValid(BaseCharacter))
	//	{
	//		if (BaseCharacter->IsInteractiveCharacter())
	//		{
	//			UE_LOG(LogTemp, Display, TEXT("BeginOverlap <%s> : <%s>"), *OverlappedComp->GetName(), *OtherActor->GetName());
	//			VaccumOverlapActors.Add(OtherActor);
	//		}
	//	}
	//}
}
