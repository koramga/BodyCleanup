//$ Copyright 2015-21, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//

#pragma once
#include "CoreMinimal.h"
#include "MarkerGenLayer.generated.h"

class UMarkerGenPattern;

UCLASS()
class DUNGEONARCHITECTRUNTIME_API UMarkerGenLayer : public UObject {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category="Marker Generator")
	FText LayerName;

	UPROPERTY()
	UMarkerGenPattern* Pattern;

public:
	void Compile();
};

