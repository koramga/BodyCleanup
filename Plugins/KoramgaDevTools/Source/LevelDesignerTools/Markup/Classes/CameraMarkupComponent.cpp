// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraMarkupComponent.h"

UCameraMarkupComponent::UCameraMarkupComponent()
{

}

void UCameraMarkupComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UCameraMarkupComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

ELevelMarkupType UCameraMarkupComponent::GetLevelMarkupType() const
{
    return ELevelMarkupType::Camera;
}

FVector UCameraMarkupComponent::GetMarkupLocation() const
{
    return GetComponentToWorld().GetLocation();
}

FTransform UCameraMarkupComponent::GetMarkupTransform() const
{
    return GetComponentToWorld();
}

void UCameraMarkupComponent::UpdateFromMarkup(UObject* Object) const
{
}
