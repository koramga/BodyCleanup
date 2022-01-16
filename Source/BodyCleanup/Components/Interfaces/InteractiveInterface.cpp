// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveInterface.h"

// Add default functionality here for any IInteractiveInterface functions that are not pure virtual.

EInteractiveAction IInteractiveInterface::GetInteractiveAction() const
{
	return EInteractiveAction::None;
}

void IInteractiveInterface::SetInteractiveAction(EInteractiveAction InputInteractiveAction)
{
}

void IInteractiveInterface::SetInteractiveComponent(TSoftObjectPtr<USceneComponent> InputInteractiveComponent)
{

}

EInteractiveType IInteractiveInterface::GetInteractiveType() const
{
	return EInteractiveType::None;
}

void IInteractiveInterface::SetInteractiveType(EInteractiveType InputInteractiveType)
{
}
