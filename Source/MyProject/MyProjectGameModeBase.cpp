// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyProjectGameModeBase.h"
#include "Kismet/GameplayStatics.h"

//Constructor
AMyProjectGameModeBase::AMyProjectGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

//Called when the game starts or when spawned
void AMyProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

//Called every frame

void AMyProjectGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//If the players score is greater than 244, win the game. Open level called "MainMenu"
	if (Score == 244)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
	}
}

void AMyProjectGameModeBase::IncreaseScore(int Value)
{
	Score += Value;
}
