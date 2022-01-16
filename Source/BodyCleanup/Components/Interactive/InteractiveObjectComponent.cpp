// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObjectComponent.h"
#include "../../Utilities/FunctionLibraries/FindFunctionLibrary.h"

UInteractiveObjectComponent::UInteractiveObjectComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	InteractiveType = EInteractiveType::Junk;
}

void UInteractiveObjectComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (EInteractiveComponentToType::Parent == InteractiveComponentToType)
	{
		UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(GetAttachParent());

		if (IsValid(PrimitiveComponent))
		{
			AffectInteractiveComponents.Add(PrimitiveComponent);
		}
	}
	else if (EInteractiveComponentToType::Setup == InteractiveComponentToType)
	{
		if (ENameType::Name == NameType)
		{
			UPrimitiveComponent* PrimitiveComopnent = UFindFunctionLibrary::FindPrimitiveComponentByName(GetOwner()->GetRootComponent(), InteractiveName);

			if (IsValid(PrimitiveComopnent))
			{
				AffectInteractiveComponents.Add(PrimitiveComopnent);
			}
		}
		else if (ENameType::Tag == NameType)
		{
			UFindFunctionLibrary::FindPrimitiveComponentsByTagName(AffectInteractiveComponents, GetOwner(), InteractiveName);
		}
	}
}

void UInteractiveObjectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (InteractiveComponent.IsValid())
	{
		const FTransform& ComponentTransform = InteractiveComponent->GetComponentTransform();

		if (EInteractiveAction::Absorbing == InteractiveAction)
		{
			for (TSoftObjectPtr<UPrimitiveComponent> AffectInteractiveComponent : AffectInteractiveComponents)
			{
				if (AffectInteractiveComponent.IsValid())
				{
					const FTransform& Transform = AffectInteractiveComponent->GetComponentTransform();
					FVector NextLocation = FMath::VInterpTo(Transform.GetLocation(), ComponentTransform.GetLocation(), DeltaTime, AbsorbingInterpValue);
					AffectInteractiveComponent->SetWorldLocation(NextLocation);
				}
			}

		}
		else if (EInteractiveAction::Holding == InteractiveAction)
		{
			for (TSoftObjectPtr<UPrimitiveComponent> AffectInteractiveComponent : AffectInteractiveComponents)
			{
				if (AffectInteractiveComponent.IsValid())
				{
					const FTransform& Transform = AffectInteractiveComponent->GetComponentTransform();
					AffectInteractiveComponent->SetWorldLocation(ComponentTransform.GetLocation());
					AffectInteractiveComponent->SetWorldRotation(ComponentTransform.GetRotation());
				}
			}
		}
		else if (EInteractiveAction::Shooting == InteractiveAction)
		{
			for (TSoftObjectPtr<UPrimitiveComponent> AffectInteractiveComponent : AffectInteractiveComponents)
			{
				if (AffectInteractiveComponent.IsValid())
				{
					FVector LinearVelocity = AffectInteractiveComponent->GetPhysicsLinearVelocity();

					if (LinearVelocity.Size() <= 10.f)
					{
						SetInteractiveAction(EInteractiveAction::None);
					}
				}
			}
		}
	}
}

void UInteractiveObjectComponent::UpdateInteractiveAction(EInteractiveAction NextInteractiveAction, EInteractiveAction BeforeInteractiveAction)
{
	Super::UpdateInteractiveAction(NextInteractiveAction, BeforeInteractiveAction);

	if (EInteractiveAction::None == NextInteractiveAction)
	{
		for (TSoftObjectPtr<UPrimitiveComponent> AffectInteractiveComponent : AffectInteractiveComponents)
		{
			if (AffectInteractiveComponent.IsValid())
			{
				AffectInteractiveComponent->SetSimulatePhysics(true);
			}
		}
	}
	else if (EInteractiveAction::Shooting == NextInteractiveAction)
	{
		if (InteractiveComponent.IsValid())
		{
			for (TSoftObjectPtr<UPrimitiveComponent> AffectInteractiveComponent : AffectInteractiveComponents)
			{
				if (InteractiveComponent.IsValid())
				{
					FTransform Transform = InteractiveComponent->GetComponentToWorld();

					FVector startLoc = Transform.GetLocation();
					FVector targetLoc = Transform.GetLocation() + InteractiveComponent->GetOwner()->GetActorForwardVector() * ShootingPowerValue;
					float arcValue = 0.9f;
					FVector outVelocity = FVector::ZeroVector;

					if (UGameplayStatics::SuggestProjectileVelocity_CustomArc(this, outVelocity, startLoc, targetLoc, GetWorld()->GetGravityZ(), arcValue))
					{
						AffectInteractiveComponent->SetPhysicsLinearVelocity(outVelocity);
					}

					AffectInteractiveComponent->SetSimulatePhysics(true);
				}
			}
		}
	}
	else if (EInteractiveAction::Holding == NextInteractiveAction)
	{
		if (EInteractiveType::Junk == InteractiveType)
		{
			GetOwner()->Destroy();
		}
	}
	else
	{
		for (TSoftObjectPtr<UPrimitiveComponent> AffectInteractiveComponent : AffectInteractiveComponents)
		{
			if (AffectInteractiveComponent.IsValid())
			{
				AffectInteractiveComponent->SetSimulatePhysics(false);
			}
		}
	}
}

bool UInteractiveObjectComponent::CanUpdateInteractive(EInteractiveAction NextInteractiveAction, EInteractiveAction CurrentInteractiveAction)
{
	if (EInteractiveType::None == InteractiveType)
	{
		return false;
	}

	if (EInteractiveAction::Shooting == NextInteractiveAction)
	{
		if (EInteractiveAction::Holding == CurrentInteractiveAction)
		{
			return true;
		}

		return false;
	}
	else if (EInteractiveAction::None == NextInteractiveAction)
	{
		if (EInteractiveAction::Shooting == CurrentInteractiveAction)
		{
			return false;
		}
	}

	return Super::CanUpdateInteractive(NextInteractiveAction, CurrentInteractiveAction);
}