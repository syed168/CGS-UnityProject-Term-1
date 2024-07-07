// Copyright Epic Games, Inc. All Rights Reserved.


#include "Week_2_DoorGameModeBase.h"
#include "ObjectiveWorldSubsystem.h"

void AWeek_2_DoorGameModeBase::StartPlay() {

	Super::StartPlay();
	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();
	if (ObjectiveWorldSubsystem) {

		ObjectiveWorldSubsystem->CreateObjectiveWidget(ObjectiveWidgetClass);
		ObjectiveWorldSubsystem->DisplayObjectiveWidget();
	}
	
}
