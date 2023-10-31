// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyProjectGameModeBase.generated.h"


/**
 * 
 */
class AMyHUD;
DECLARE_MULTICAST_DELEGATE_OneParam(ScoreDelegate, int32);

class AGameCube;
UCLASS()
class MYPROJECT_API AMyProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AMyProjectGameModeBase();
	ScoreDelegate ScoreDelegateEvent;
	bool GameStatus();

protected:
	virtual void BeginPlay() override;
	void ScoreModify(int);

	UPROPERTY(VisibleAnywhere)
	bool Game = true;
	UPROPERTY(EditDefaultsOnly)
	int8 CubeMaxCount = 70;
	UPROPERTY(EditDefaultsOnly)
	int8 CubeMinCount = 20;
	UPROPERTY(VisibleAnywhere)
	int8 CubeMAX;
	UPROPERTY(VisibleAnywhere)
	int8 Score;
	UPROPERTY(EditDefaultsOnly)
	TArray<int32> XRange = {-4900, 4900};
	UPROPERTY(EditDefaultsOnly)
	TArray<int32> YRange = {-4800, 5000};
	UPROPERTY(EditDefaultsOnly)
	TArray<int32> ZRange = {0, 350};
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGameCube> CubeClass;
	
private:
	UPROPERTY()
	TArray<AGameCube*> Cubes;
	
};
