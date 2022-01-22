// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TriggerSceneComponent.h"
#include "WarpComponent.generated.h"


UENUM(BlueprintType)
enum class EWarpType : uint8
{
	//Warp를 이용하여 Level을 이동합니다.
	Level,
	//Warp를 이용하여 위치를 이동합니다.
	Location,
};

UCLASS( ClassGroup=(Actions), meta=(BlueprintSpawnableComponent) )
class LEVELDESIGNERTOOLS_API UWarpComponent : public UTriggerSceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWarpComponent();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|WarpComponent")
	EWarpType	WarpType = EWarpType::Location;

	//Warp에 이동할 Actor입니다. Actor가 지정되지 않았다면 Self로 이동하게 됩니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|WarpComponent", meta = (EditCondition = "WarpType == EWarpType::Location", EditConditionHides, ToolTip = ""))
	TSoftObjectPtr<AActor>				WarpActor;

	//Warp가 이동할 Actor 내의 Markup입니다. Markup이 없다면 Actor를 기준으로 이동하게 됩니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|WarpComponent", meta = (EditCondition = "WarpType == EWarpType::Location", EditConditionHides, ToolTip = ""))
	FName								MarkupName;

	//Level의 이름을 지정합니다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup|WarpComponent", meta = (EditCondition = "WarpType == EWarpType::Level", EditConditionHides, ToolTip = ""))
	FName								LevelName;

	UPROPERTY(VisibleAnywhere)
	TSoftObjectPtr<UObject>	MarkupComponent;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void SetupTrigger() override;
	virtual void UpdateTrigger(bool bInputIsOnTrigger) override;

public :
	EWarpType GetWarpType() const;		
	TSoftObjectPtr<AActor> GetWarpActor() const;
	class ILevelMarkupInterface* FindMarkupComponent() const; 
	FVector GetWarpLocation() const;
};
