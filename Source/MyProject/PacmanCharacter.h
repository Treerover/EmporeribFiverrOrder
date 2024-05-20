// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PacmanCharacter.generated.h"

//Enum for direction
UENUM(BlueprintType)
enum class EPacmanDirection : uint8
{
	Up,
	Down,
	Left,
	Right,
	None
};

UCLASS()
class MYPROJECT_API APacmanCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APacmanCharacter();

	//Sprite component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UPaperFlipbookComponent* SpriteComponent;

	//Audio component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UAudioComponent* PelletPickupAudioComponent;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Setup player input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void PlayFlipbook(EPacmanDirection NewDirection);

	//Move up
	void MoveUp(float Value);

	//Move right
	void MoveRight(float Value);

	//Play pellet pickup sound
	void PlayPelletPickupSound();

	void BackToMenu();


	UPROPERTY(EditAnywhere, Category = "Movement")
		class UPaperFlipbook* UpFlipbook;

	UPROPERTY(EditAnywhere, Category = "Movement")
		class UPaperFlipbook* DownFlipbook;

	UPROPERTY(EditAnywhere, Category = "Movement")
		class UPaperFlipbook* RightFlipbook;

	UPROPERTY(EditAnywhere, Category = "Movement")
		class UPaperFlipbook* LeftFlipbook;

	UPROPERTY(EditAnywhere, Category = "Movement")
		class UPaperFlipbook* NotMovingFlipbook;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float Speed = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
		EPacmanDirection Direction = EPacmanDirection::Right;

};
