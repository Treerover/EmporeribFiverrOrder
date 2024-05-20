// Fill out your copyright notice in the Description page of Project Settings.


#include "Pellet.h"
#include "Components/BoxComponent.h"
#include "PacmanCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "MyProjectGameModeBase.h"


// Sets default values
APellet::APellet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComponent;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(MeshComponent);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);


	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APellet::OnBeginOverlap);
}


// Called when the game starts or when spawned
void APellet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APellet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APellet::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APacmanCharacter::StaticClass()))
	{
		// Get game mode, increases score by 1.
		AMyProjectGameModeBase* GameMode = Cast<AMyProjectGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode != nullptr)
		{
			GameMode->IncreaseScore(1);
		}

		//Play sound effect from player character audio
		APacmanCharacter* PacmanCharacter = Cast<APacmanCharacter>(OtherActor);
		if (PacmanCharacter != nullptr)
		{
			PacmanCharacter->PlayPelletPickupSound();
		}

		//Destroy the pellet
		Destroy();
	}
}

