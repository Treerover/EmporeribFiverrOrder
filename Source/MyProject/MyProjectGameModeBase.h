// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	//Constructor
	AMyProjectGameModeBase();

	//begin play
	virtual void BeginPlay() override;

	protected:
	virtual void Tick(float DeltaTime) override;

	public:
	void IncreaseScore(int Value);


	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score", meta = (AllowPrivate))
	int Score = 0;
	
};
