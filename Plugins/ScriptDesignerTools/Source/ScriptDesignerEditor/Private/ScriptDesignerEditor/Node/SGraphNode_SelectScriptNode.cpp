// Fill out your copyright notice in the Description page of Project Settings.


#include "ScriptDesignerEditor/Node/SGraphNode_SelectScriptNode.h"
#include "EdGraphNode_SelectScriptNode.h"

void SGraphNode_SelectScriptNode::Construct(const FArguments& InArgs, UEdGraphNode_SelectScriptNode* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
	InNode->SetEdNode(this);	
}
