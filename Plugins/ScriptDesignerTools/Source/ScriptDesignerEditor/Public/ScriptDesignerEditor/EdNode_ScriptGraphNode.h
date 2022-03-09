// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScriptGraphNode.h"
#include "EdGraph/EdGraphNode.h"
#include "EdNode_ScriptGraphNode.generated.h"

/**
 * 
 */
UCLASS()
class SCRIPTDESIGNEREDITOR_API UEdNode_ScriptGraphNode : public UEdGraphNode
{
	GENERATED_BODY()

public :
	UEdNode_ScriptGraphNode();
	virtual ~UEdNode_ScriptGraphNode();

	UPROPERTY(VisibleAnywhere, Instanced, Category="ScriptGraph")
	UScriptGraphNode* ScriptGraphNode;

	//void SetScriptGraphNode(UScriptGraphNode* InNode);
	
	
};
