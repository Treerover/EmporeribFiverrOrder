// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostActor.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "PacmanCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGhostActor::AGhostActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Sprite component
	SpriteComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("SpriteComponent"));
	SpriteComponent->SetupAttachment(RootComponent);

	//Box component
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGhostActor::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AGhostActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    Move();

    // Constant raytrace in front of Ghosts to check if they are near a wall
    FHitResult Hit;
    FVector Start = GetActorLocation();
    FVector ForwardVector = GetActorForwardVector();
    FVector End = ((ForwardVector * 55.0f) + Start);
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);
    GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_WorldStatic, CollisionParams);
    if (Hit.bBlockingHit)
    {
        isNearWall = true;
    }
    else
    {
        isNearWall = false;
    }

    //If the ghost hits the player, the player dies
    if (Hit.GetActor() != nullptr && Hit.GetActor()->IsA(APacmanCharacter::StaticClass()))
    {
		APacmanCharacter* Pacman = Cast<APacmanCharacter>(Hit.GetActor());
        if (Pacman != nullptr)
        {
			Pacman->Destroy();
            UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), false);
		}
	}

    // Debug ray
    DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 0.1f, 0, 1.0f);

    // If Ghost is near a wall, turn 90* to find a new direction. Random left or right
    if (isNearWall)
    {
         
         // 50% chance to turn left or right
         int Random = FMath::RandRange(0, 1);
         FRotator NewRotation = (Random == 0) ? FRotator(-90.0f, 0.0f, 0.0f) : FRotator(90.0f, 0.0f, 0.0f);
         AddActorLocalRotation(NewRotation);
    }


}

void AGhostActor::Move()
{
    FVector NewLocation = GetActorLocation();
    NewLocation += GetActorForwardVector() * Speed * GetWorld()->DeltaTimeSeconds;
    SetActorLocation(NewLocation);
}
