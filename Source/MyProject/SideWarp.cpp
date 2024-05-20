// Fill out your copyright notice in the Description page of Project Settings.


#include "SideWarp.h"
#include "Components/BoxComponent.h"

// Sets default values
ASideWarp::ASideWarp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ASideWarp::OnBeginOverlap);

}

// Called when the game starts or when spawned
void ASideWarp::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASideWarp::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (WarpTarget != nullptr)
	{
		OtherActor->SetActorLocation(WarpTarget->GetActorLocation());
	}
}


// Called every frame
void ASideWarp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

