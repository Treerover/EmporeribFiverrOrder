// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "PacmanPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API APacmanPlayerController : public APlayerController
{
	GENERATED_BODY()

	public:
		APacmanPlayerController();
	
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
			class UInputMappingContext* DefaultMappingContext;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
			class UInputAction* MoveUpAction;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
			class UInputAction* MoveRightAction;



	protected:
		virtual void BeginPlay() override;

		virtual void SetupInputComponent() override;

		//on possess
		virtual void OnPossess(APawn* InPawn) override;

	public:
		virtual void Tick(float DeltaTime) override;

		void MoveUp(const FInputActionValue& Value);

		void MoveRight(const FInputActionValue& Value);
};
