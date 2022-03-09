// Fill out your copyright notice in the Description page of Project Settings.


#include "ScriptDesignerEditor/SEdNode_ScriptGraphNode.h"
#include "SGraphPin.h"
#include "ScriptDesignerEditor/Colors_ScriptGraph.h"
#include "ScriptDesignerEditor/ScriptGraphDragConnection.h"
#include "ScriptDesignerEditor/EdNode_ScriptGraphNode.h"
#include "ScriptDesignerEditor/Colors_ScriptGraph.h"

#define LOCTEXT_NAMESPACE "EdNode_ScriptGraph"

class SScriptGraphPin : public SGraphPin
{
public :
	SLATE_BEGIN_ARGS(SScriptGraphPin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InPin)
	{
		this->SetCursor(EMouseCursor::Default);

		bShowLabel = true;

		GraphPinObj = InPin;
		check(GraphPinObj != nullptr)

		const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
		check(Schema);

		SBorder::Construct(SBorder::FArguments()
			.BorderImage(this, &SScriptGraphPin::GetPinBorder)
			.BorderBackgroundColor(this, &SScriptGraphPin::GetPinColor)
			.OnMouseButtonDown(this, &SScriptGraphPin::OnPinMouseDown)
			.Cursor(this, &SScriptGraphPin::GetPinCursor)
			.Padding(FMargin(5.f))
		);
	}

protected:
	virtual FSlateColor GetPinColor() const override
	{
		return ScriptGraphColor::Pin::Default;
	}

	virtual TSharedRef<SWidget> GetDefaultValueWidget() override
	{
		return SNew(STextBlock);
	}

	const FSlateBrush* GetPinBorder() const
	{
		return FEditorStyle::GetBrush(TEXT("Graph.StateNode.Body"));
	}

	virtual TSharedRef<FDragDropOperation> SpawnPinDragEvent(const TSharedRef<SGraphPanel>& InGraphPanel, const TArray<TSharedRef<SGraphPin>>& InStartingPins) override
	{
		FScriptGraphDragConnection::FDraggedPinTable PinHandles;
		PinHandles.Reserve(InStartingPins.Num());

		//since the graph can be refreshed and pins can be reconstructed/replaced
		//behind the scenes, the DragDropOperation holds onto FGraphPinHandles
		//instead of direct widgets/graph-pins.
		for(const TSharedRef<SGraphPin>& PinWidget : InStartingPins)
		{
			PinHandles.Add(PinWidget->GetPinObj());
		}

		return FScriptGraphDragConnection::New(InGraphPanel, PinHandles);
	}
};

void SEdNode_ScriptGraphNode::Construct(const FArguments& InArgs, UEdNode_ScriptGraphNode* InNode)
{
	//작업 필요
	GraphNode = InNode;
	UpdateGraphNode();
	InNode->SetEdNode(this);
}

void SEdNode_ScriptGraphNode::UpdateGraphNode()
{
	SGraphNode::UpdateGraphNode();
}

void SEdNode_ScriptGraphNode::CreatePinWidgets()
{
	SGraphNode::CreatePinWidgets();
}

void SEdNode_ScriptGraphNode::AddPin(const TSharedRef<SGraphPin>& PinToAdd)
{
	SGraphNode::AddPin(PinToAdd);
}

bool SEdNode_ScriptGraphNode::IsNameReadOnly() const
{
	return SGraphNode::IsNameReadOnly();
}

void SEdNode_ScriptGraphNode::OnNameTextCommited(const FText& InText, ETextCommit::Type CommitInfo)
{
}

FSlateColor SEdNode_ScriptGraphNode::GetBorderBackgroundColor() const
{
	//작업 필요
	return ScriptGraphColor::NodeBorder::HighlightAbortRange0;
}

FSlateColor SEdNode_ScriptGraphNode::GetBackgroundColor() const
{
	//작업 필요
	return ScriptGraphColor::NodeBody::Default;
}

EVisibility SEdNode_ScriptGraphNode::GetDragOverMarkerVisibility() const
{
	return EVisibility::Visible;
}

const FSlateBrush* SEdNode_ScriptGraphNode::GetNameIcon() const
{
	return FEditorStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Icon"));
}
