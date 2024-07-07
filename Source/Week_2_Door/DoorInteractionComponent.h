// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Curves/CurveFloat.h"
#include "DoorInteractionComponent.generated.h"

class ATriggerBox;
class IConsoleVariable;

UENUM() 
enum class EDoorState
{
	DS_Closed = 0   UMETA(DisplayName = "Closed"),
	DS_Opening = 1   UMETA(DisplayName = "Opening"),
	DS_Open = 2   UMETA(DisplayName = "Open"),
	DS_Locked = 3   UMETA(DisplayName = "Locked"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WEEK_2_DOOR_API UDoorInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorInteractionComponent();

	UFUNCTION(BlueprintCallable)
	void Open(float DeltaTime);
	UFUNCTION(BlueprintCallable)
	void Close();

	UPROPERTY(EditAnywhere)
	FRotator DesiredRotation = FRotator::ZeroRotator;
	FRotator StartRotation = FRotator::ZeroRotator;
	FRotator FinalRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere)
	ATriggerBox* TriggerBox;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	bool IsValid();

	UPROPERTY(EditAnywhere)
	float Speed;

	UPROPERTY(EditAnywhere)
	FRuntimeFloatCurve Curve;

	float Alpha;
	
	UPROPERTY(BlueprintReadOnly)
	EDoorState DoorState;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	DECLARE_EVENT(UDoorInteractionComponent, FOpened)
	FOpened& OnOpened() { return OpenedEvent; }

	FOpened OpenedEvent;

	void OnDoorOpen();

	static void OnDebugToggled(IConsoleVariable* var);
	void DebugDraw();
		
};
