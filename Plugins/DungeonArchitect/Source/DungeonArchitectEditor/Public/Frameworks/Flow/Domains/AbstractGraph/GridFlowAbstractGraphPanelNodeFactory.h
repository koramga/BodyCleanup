//$ Copyright 2015-22, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#pragma once
#include "CoreMinimal.h"
#include "EdGraphUtilities.h"

class DUNGEONARCHITECTEDITOR_API FGridFlowAbstractGraphPanelNodeFactory : public FGraphPanelNodeFactory {
public:
    virtual TSharedPtr<class SGraphNode> CreateNode(UEdGraphNode* Node) const override;
};

