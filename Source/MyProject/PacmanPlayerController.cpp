// Fill out your copyright notice in the Description page of Project Settings.


#include "PacmanPlayerController.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"

APacmanPlayerController::APacmanPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}


void APacmanPlayerController::BeginPlay()
{
	Super::BeginPlay();

}

void APacmanPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	//{
	//	EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &APacmanPlayerController::MoveRight);// 1
	//	EnhancedInputComponent->BindAction(MoveUpAction, ETriggerEvent::Triggered, this, &APacmanPlayerController::MoveUp);// 2
	//}

	//Binds functions to Axis mapping


}

void APacmanPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);


}

void APacmanPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APacmanPlayerController::MoveUp(const FInputActionValue& Value)
{
	if (Value.GetMagnitude() > 0.0f)
	{
		FVector Direction = FVector(0.0f, 0.0f, 1.0f);
		GetPawn()->AddMovementInput(Direction, Value.GetMagnitude());
	}
	else
	{
		FVector Direction = FVector(0.0f, 0.0f, -1.0f);
		GetPawn()->AddMovementInput(Direction, -Value.GetMagnitude());
	}

}

void APacmanPlayerController::MoveRight(const FInputActionValue& Value)
{
	if (Value.GetMagnitude() > 0.0f)
	{
		FVector Direction = FVector(0.0f, 1.0f, 0.0f);
		GetPawn()->AddMovementInput(Direction, Value.GetMagnitude());
	}
	else
	{
		FVector Direction = FVector(0.0f, -1.0f, 0.0f);
		GetPawn()->AddMovementInput(Direction, -Value.GetMagnitude());
	}
}
