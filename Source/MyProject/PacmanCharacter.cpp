// Fill out your copyright notice in the Description page of Project Settings.


#include "PacmanCharacter.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "PacmanPlayerController.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/AudioComponent.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APacmanCharacter::APacmanCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Sprite component
	SpriteComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("SpriteComponent"));
	SpriteComponent->SetupAttachment(RootComponent);

	//Audio component
	PelletPickupAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PelletPickupAudioComponent"));
	PelletPickupAudioComponent->SetupAttachment(RootComponent);


	// Disable gravity
	GetCharacterMovement()->GravityScale = 0.0f;

	// Enable flying movement mode
	GetCharacterMovement()->SetMovementMode(MOVE_Flying);

	// Configure character movement
	GetCharacterMovement()->MaxFlySpeed = Speed;
}


// Called when the game starts or when spawned
void APacmanCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Set initial direction
	Direction = EPacmanDirection::Right;
	//Plays flipbook animation depending on direction
	PlayFlipbook(Direction);
}

// Called every frame
void APacmanCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If character is not moving, set direction to none
	if (GetCharacterMovement()->Velocity.Z == 0.0f && GetCharacterMovement()->Velocity.Y == 0.0f && Direction != EPacmanDirection::None)
	{
		Direction = EPacmanDirection::None;
		//Plays flipbook animation depending on direction
		PlayFlipbook(Direction);
	}

}

// Called to bind functionality to input
void APacmanCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveUp", this, &APacmanCharacter::MoveUp);
	PlayerInputComponent->BindAxis("MoveRight", this, &APacmanCharacter::MoveRight);
	PlayerInputComponent->BindAction("Escape", IE_Pressed, this, &APacmanCharacter::BackToMenu);
}

void APacmanCharacter::PlayFlipbook(EPacmanDirection NewDirection)
{
	// Set flipbook depending on direction
	switch (NewDirection)
	{
		case EPacmanDirection::Up:
			SpriteComponent->SetFlipbook(UpFlipbook);
			break;
		case EPacmanDirection::Down:
			SpriteComponent->SetFlipbook(DownFlipbook);
			break;
		case EPacmanDirection::Left:
			SpriteComponent->SetFlipbook(LeftFlipbook);
			break;
		case EPacmanDirection::Right:
			SpriteComponent->SetFlipbook(RightFlipbook);
			break;
	}
}

void APacmanCharacter::MoveUp(float Value)
{
	if (Value != 0.0f)
	{
		// Add movement in the Up/Down direction (Z axis)
		FVector VDirection = FVector(0.0f, 0.0f, Value > 0.0f ? 1.0f : -1.0f);
		AddMovementInput(VDirection, Speed * GetWorld()->DeltaTimeSeconds);
		// Set direction
		Direction = Value > 0.0f ? EPacmanDirection::Up : EPacmanDirection::Down;
		//Plays flipbook animation depending on direction
		PlayFlipbook(Direction);
	}
	else
	{
		GetCharacterMovement()->Velocity.Z = 0.0f;
	}
}

void APacmanCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// Add movement in the Right/Left direction (Y axis)
		FVector VDirection = FVector(0.0f, Value > 0.0f ? 1.0f : -1.0f, 0.0f);
		AddMovementInput(VDirection, Speed * GetWorld()->DeltaTimeSeconds);
		// Set direction
		Direction = Value > 0.0f ? EPacmanDirection::Right : EPacmanDirection::Left;
		//Plays flipbook animation depending on direction
		PlayFlipbook(Direction);
	}
	else
	{
		GetCharacterMovement()->Velocity.Y = 0.0f;
	}
}

void APacmanCharacter::PlayPelletPickupSound()
{
	if (PelletPickupAudioComponent->Sound)
	{
		PelletPickupAudioComponent->Play();
	}
}

void APacmanCharacter::BackToMenu()
{
	//Loads the main menu level
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}