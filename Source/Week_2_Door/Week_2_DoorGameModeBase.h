// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Week_2_DoorGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class WEEK_2_DOOR_API AWeek_2_DoorGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void StartPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> ObjectiveWidgetClass;

	//UUserWidget* ObjectiveWidget = nullptr;
};
