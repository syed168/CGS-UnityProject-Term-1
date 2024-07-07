// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteractionComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TriggerBox.h"
#include "Engine/World.h"
#include "ObjectiveWorldSubsystem.h"
#include "ObjectiveComponent.h"
#include "DrawDebugHelpers.h"

constexpr float FLT_METERS(float meters) { return meters * 100.0f; }

static TAutoConsoleVariable<bool> CVToggleDebugDoor(
	TEXT("Abstaction.DoorInteractionComponent.Debug"),
	false,
	TEXT("Toggle DoorInteractionComponent debug display."),
	ECVF_Default);

// Sets default values for this component's properties
UDoorInteractionComponent::UDoorInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	DoorState = EDoorState::DS_Closed;

	CVToggleDebugDoor.AsVariable()->SetOnChangedCallback(FConsoleVariableDelegate::CreateStatic(&UDoorInteractionComponent::OnDebugToggled));
	// ...
}


// Called when the game starts
void UDoorInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	StartRotation = GetOwner()->GetActorRotation();
	FinalRotation = DesiredRotation + StartRotation;
	//UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();
	//if (ObjectiveWorldSubsystem) {
	//	OpenedEvent.AddUObject(ObjectiveWorldSubsystem, &UObjectiveWorldSubsystem::OnObjectiveCompleted);
	//}

}
void UDoorInteractionComponent::Open(float DeltaTime) {

	FRotator CurrentRotation = GetOwner()->GetActorRotation();

	//if (!CurrentRotation.Equals(FinalRotation, 5.0f)) {
	
	//	CurrentRotation.Yaw += Speed * DeltaTime;
		//GetOwner()->SetActorRotation(CurrentRotation);
	//}
	if (Alpha < 1) {
		Alpha += Speed * DeltaTime;
		float CurvedAlpha = Curve.GetRichCurveConst()->Eval(Alpha);

		GetOwner()->SetActorRotation(FMath::Lerp(StartRotation, FinalRotation, CurvedAlpha));
	}
	// GetOwner()->SetActorRotation(FinalRotation);
}

void UDoorInteractionComponent::Close() {
	Alpha = 0;
	GetOwner()->SetActorRotation(StartRotation);
}
// Called every frame
void UDoorInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	
	if (IsValid()) {

		
		APawn* Player = GetWorld()->GetFirstPlayerController()->GetPawn();
		bool OverLapping = Player && TriggerBox->IsOverlappingActor(Player);
		if (OverLapping == true) {
			Open(DeltaTime);
			OnDoorOpen();
			//OpenedEvent.Broadcast();
		}
		else
			Close();
	}
	DebugDraw();
}
bool UDoorInteractionComponent::IsValid() {

	return TriggerBox && GetWorld() && GetWorld()->GetFirstLocalPlayerFromController();
}

void UDoorInteractionComponent::OnDoorOpen() {

	DoorState = EDoorState::DS_Open;

	UObjectiveComponent* ObjectiveComponent = GetOwner()->FindComponentByClass<UObjectiveComponent>();
	if (ObjectiveComponent) {

		ObjectiveComponent->SetState(EObjectiveState::OS_Completed);
	}
	GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Yellow, TEXT("Door Opened"));
}

void UDoorInteractionComponent::OnDebugToggled(IConsoleVariable* var) {

	UE_LOG(LogTemp, Warning, TEXT("OnDebugToggled"));
}

void UDoorInteractionComponent::DebugDraw() {

	if (CVToggleDebugDoor->GetBool()) {

		FVector Offset(FLT_METERS(-0.75f), 0.0f, FLT_METERS(2.5F));
		FVector StartLocation = GetOwner()->GetActorLocation() + Offset;
		FString EnumASString = TEXT("Door State: ") + UEnum::GetDisplayValueAsText(DoorState).ToString();
		DrawDebugString(GetWorld(), Offset, EnumASString, GetOwner(), FColor::Blue, 0.0f);
	}
}
