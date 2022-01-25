// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObjectComponent.h"
#include "../../Utilities/FunctionLibraries/FindFunctionLibrary.h"
#include "../../Character/BaseCharacter.h"

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

	for (const TSoftObjectPtr<UPrimitiveComponent>& AffectInteractiveComponent : AffectInteractiveComponents)
	{
		if (AffectInteractiveComponent->IsA(UDestructibleComponent::StaticClass()))
		{
			UDestructibleComponent* DestructibleMeshComponent = Cast<UDestructibleComponent>(AffectInteractiveComponent.Get());

			DestructibleMeshComponent->WakeRigidBody(NAME_None);
			DestructibleMeshComponent->SetSimulatePhysics(true);

			//FBodyInstance* BodyInstance = DestructibleMeshComponent->GetBodyInstance();
			//
			//if (nullptr != BodyInstance)
			//{
			//	BodyInstance->SetInstanceSimulatePhysics(true);
			//}

			DestructibleMeshComponent->OnComponentFracture.AddDynamic(this, &UInteractiveObjectComponent::__OnComponentFracture);
		}
		else
		{
			AffectInteractiveComponent->SetSimulatePhysics(true);
		}
	}
}

void UInteractiveObjectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (InteractiveComponent.IsValid())
	{
		const FTransform& ComponentTransform = InteractiveComponent->GetComponentTransform();

		if (EInteractiveAction::Sucking == InteractiveAction)
		{
			for (TSoftObjectPtr<UPrimitiveComponent> AffectInteractiveComponent : AffectInteractiveComponents)
			{
				if (AffectInteractiveComponent.IsValid())
				{
					const FTransform& Transform = AffectInteractiveComponent->GetComponentTransform();
					FVector Direction = ComponentTransform.GetLocation() - Transform.GetLocation();
					Direction.Normalize();
					AffectInteractiveComponent->SetPhysicsLinearVelocity(Direction * SuckingSpeedPerSecond);

					//const FTransform& Transform = AffectInteractiveComponent->GetComponentTransform();
					//
					//FVector Direction = ComponentTransform.GetLocation() - Transform.GetLocation();
					//Direction.Normalize();					
					//
					//FVector NextLocation = Transform.GetLocation() + Direction * SuckingSpeedPerSecond * DeltaTime;
					//
					//AffectInteractiveComponent->SetWorldLocation(NextLocation);

					//UE_LOG(LogTemp, Display, TEXT("NextLocation : <%.2f, %.2f, %.2f>"), NextLocation.X, NextLocation.Y, NextLocation.Z);
				}
			}

		}
		//else if (EInteractiveAction::Holding == InteractiveAction)
		//{
		//	for (TSoftObjectPtr<UPrimitiveComponent> AffectInteractiveComponent : AffectInteractiveComponents)
		//	{
		//		FTransform HoldingTransform = ComponentTransform;
		//
		//		if (AffectInteractiveComponent->IsA(UStaticMeshComponent::StaticClass()))
		//		{
		//			UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(AffectInteractiveComponent.Get());
		//
		//			if (IsValid(StaticMeshComponent))
		//			{
		//				UStaticMesh* StaticMesh = StaticMeshComponent->GetStaticMesh();
		//
		//				if (IsValid(StaticMesh))
		//				{
		//					FBoxSphereBounds StaticMeshBounds = StaticMesh->GetBounds();
		//
		//					HoldingTransform.SetLocation(HoldingTransform.GetLocation() + InteractiveComponent->GetForwardVector() * StaticMeshBounds.GetBox().GetExtent().Size() / 2.f);
		//				}
		//			}
		//		}
		//		else if (AffectInteractiveComponent->IsA(UDestructibleComponent::StaticClass()))
		//		{
		//			UDestructibleComponent* DestructibleMeshComponent = Cast<UDestructibleComponent>(AffectInteractiveComponent.Get());
		//
		//			if (IsValid(DestructibleMeshComponent))
		//			{
		//				UDestructibleMesh* DestructibleMesh = DestructibleMeshComponent->GetDestructibleMesh();
		//
		//				if (IsValid(DestructibleMesh))
		//				{
		//					FBoxSphereBounds StaticMeshBounds = DestructibleMesh->GetBounds();
		//
		//					HoldingTransform.SetLocation(HoldingTransform.GetLocation() + InteractiveComponent->GetForwardVector() * StaticMeshBounds.GetBox().GetExtent().Size() / 2.f);
		//				}
		//			}
		//		}
		//
		//		if (AffectInteractiveComponent.IsValid())
		//		{
		//			const FTransform& Transform = AffectInteractiveComponent->GetComponentTransform();
		//			AffectInteractiveComponent->SetWorldLocation(HoldingTransform.GetLocation());
		//			AffectInteractiveComponent->SetWorldRotation(HoldingTransform.GetRotation());
		//		}
		//	}
		//}
	}


	if (EInteractiveAction::ArcShooting == InteractiveAction
		|| EInteractiveAction::HoldShooting == InteractiveAction)
	{
		for (TSoftObjectPtr<UPrimitiveComponent> AffectInteractiveComponent : AffectInteractiveComponents)
		{
			if (AffectInteractiveComponent.IsValid())
			{
				FVector LinearVelocity = AffectInteractiveComponent->GetPhysicsLinearVelocity();

				if (LinearVelocity.Size() <= 10.f)
				{
					EInteractiveAction NextInteractiveAction = EInteractiveAction::None;

					if (InteractiveComponent.IsValid())
					{
						ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(InteractiveComponent->GetOwner());

						if (IsValid(BaseCharacter))
						{
							EAnimationType AnimationType = BaseCharacter->GetAnimationType();

							if (EAnimationType::Vacuum == AnimationType)
							{
								NextInteractiveAction = EInteractiveAction::Sucking;
							}							
						}	
					}
					
					SetupInteractiveAction(NextInteractiveAction);					
				}
			}
		}
	}
}

void UInteractiveObjectComponent::__OnComponentFracture(const FVector& HitPoint, const FVector& HitDirection)
{
	SetInteractiveType(EInteractiveType::Fracture);
	SetupInteractiveAction(EInteractiveAction::None);
	SetComponentTickEnabled(false);
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
	else if (EInteractiveAction::HoldShooting == NextInteractiveAction)
	{
		if (InteractiveComponent.IsValid())
		{
			for (TSoftObjectPtr<UPrimitiveComponent> AffectInteractiveComponent : AffectInteractiveComponents)
			{
				if (InteractiveComponent.IsValid())
				{
					FTransform Transform = InteractiveComponent->GetComponentToWorld();

					FVector startLoc = Transform.GetLocation();
					FVector targetLoc = Transform.GetLocation() + InteractiveComponent->GetOwner()->GetActorForwardVector() * HoldShootingPower;
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
	else if (EInteractiveAction::ArcShooting == NextInteractiveAction)
	{
		for (TSoftObjectPtr<UPrimitiveComponent> AffectInteractiveComponent : AffectInteractiveComponents)
		{
			if (AffectInteractiveComponent.IsValid())
			{
				AffectInteractiveComponent->SetSimulatePhysics(true);
			}
		}
	}
	else if (EInteractiveAction::Holding == NextInteractiveAction)
	{
		//if (EInteractiveType::Junk == InteractiveType)
		//{
		//	GetOwner()->Destroy();
		//}
	}
	else
	{
		//for (TSoftObjectPtr<UPrimitiveComponent> AffectInteractiveComponent : AffectInteractiveComponents)
		//{
		//	if (AffectInteractiveComponent.IsValid())
		//	{
		//		AffectInteractiveComponent->SetSimulatePhysics(false);
		//	}
		//}
	}
}

bool UInteractiveObjectComponent::CanUpdateInteractive(EInteractiveAction NextInteractiveAction, EInteractiveAction CurrentInteractiveAction)
{
	UE_LOG(LogTemp, Display, TEXT("Kormaga CanUpdateInteractive : <%s> <%s>"), *GetEnumerationToString(NextInteractiveAction), *GetEnumerationToString(CurrentInteractiveAction));

	if (EInteractiveType::None == InteractiveType
		|| EInteractiveType::Fracture == InteractiveType)
	{
		return false;
	}

	if (EInteractiveAction::ArcShooting == CurrentInteractiveAction
		|| EInteractiveAction::HoldShooting == CurrentInteractiveAction)
	{
		return false;
	}

	return Super::CanUpdateInteractive(NextInteractiveAction, CurrentInteractiveAction);
}