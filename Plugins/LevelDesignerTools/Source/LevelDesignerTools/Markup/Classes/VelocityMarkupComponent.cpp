// Fill out your copyright notice in the Description page of Project Settings.


#include "VelocityMarkupComponent.h"
//#include "../../Utilities/LevelSupportFunctionLibrary.h"
#include "../../Utility/LevelSupportFunctionLibrary.h"

FVector UVelocityMarkupComponent::GetLinearVelocity() const
{
	return LinearVelocity;
}

FVector UVelocityMarkupComponent::GetAngularVelocity() const
{
	return AngularVelocity;
}

ELevelMarkupType UVelocityMarkupComponent::GetLevelMarkupType() const
{
	return ELevelMarkupType::Velocity;
}

void UVelocityMarkupComponent::UpdateFromMarkup(UObject* Object) const
{
	TArray<TSoftObjectPtr<UPrimitiveComponent>> PrimitiveComponents;

	if (Object->IsA(AActor::StaticClass()))
	{
		ULevelSupportFunctionLibrary::FindPrimitiveComponets(PrimitiveComponents, Cast<AActor>(Object));
	} 
	else if (Object->IsA(USceneComponent::StaticClass()))
	{
		ULevelSupportFunctionLibrary::FindPrimitiveComponets(PrimitiveComponents, Cast<USceneComponent>(Object)->GetOwner());
	}

	for (TSoftObjectPtr<UPrimitiveComponent> PrimitiveComponent : PrimitiveComponents)
	{
		PrimitiveComponent->SetSimulatePhysics(true);
		PrimitiveComponent->SetPhysicsLinearVelocity(LinearVelocity);
		PrimitiveComponent->SetPhysicsAngularVelocity(AngularVelocity);
	}
}
