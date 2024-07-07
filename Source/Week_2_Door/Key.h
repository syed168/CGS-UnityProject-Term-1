
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Key.generated.h"

class UKeyComponent;
/**
 *
 */
UCLASS()
class WEEK_2_DOOR_API A_Key : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	A_Key();
protected:
	UPROPERTY(EditAnywhere, NoClear)
	UKeyComponent* KeyComponent;

};