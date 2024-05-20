// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GhostActor.generated.h"

UCLASS()
class MYPROJECT_API AGhostActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGhostActor();

	//Sprite component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UPaperFlipbookComponent* SpriteComponent;

	//Box component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UBoxComponent* BoxComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Move();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ghost")
		float Speed = 300.0f;

	bool isNearWall = false;
};
