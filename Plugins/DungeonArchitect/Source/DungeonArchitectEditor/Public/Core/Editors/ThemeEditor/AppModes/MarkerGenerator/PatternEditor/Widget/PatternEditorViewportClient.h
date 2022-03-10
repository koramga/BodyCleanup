//$ Copyright 2015-21, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#pragma once
#include "CoreMinimal.h"

class FPatternEditorViewportClient : public FEditorViewportClient , public TSharedFromThis<FPatternEditorViewportClient>
{
public:
	FPatternEditorViewportClient(FPreviewScene& InPreviewScene);

	// FEditorViewportClient interface
	virtual void Tick(float DeltaSeconds) override;
	// End of FEditorViewportClient interface
};

