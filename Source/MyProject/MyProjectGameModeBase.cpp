// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyProjectGameModeBase.h"

#include <string>

#include "GameCube.h"
#include "MyHUD.h"


AMyProjectGameModeBase::AMyProjectGameModeBase()
{
	HUDClass = AMyHUD::StaticClass();
}

void AMyProjectGameModeBase::ScoreModify(int value)
{
	if(value > 0)
	{
		if(Score < CubeMAX )
		{
			Score += value;
			if(Score >= CubeMAX){ Game = false;};
			ScoreDelegateEvent.Broadcast(Score);
		}
	}
	else
	{
		if(Score > 0)
		{
			Score += value;
			if(Score >= CubeMAX){ Game = false;};
			ScoreDelegateEvent.Broadcast(Score);
		}
	}
}

bool AMyProjectGameModeBase::GameStatus()
{
	return Game;
}

void AMyProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	int8 CubeCount = FMath::RandRange(CubeMinCount, CubeMaxCount);
	CubeMAX = CubeCount;
	for(int i = 0; i< CubeCount;i++)
	{
		AGameCube* Cube = GetWorld()->SpawnActor<AGameCube>(CubeClass,FVector( 
		FMath::RandRange(XRange[0],XRange[1]),
		FMath::RandRange(YRange[0],YRange[1]),
		FMath::RandRange(ZRange[0],ZRange[1])),FRotator::ZeroRotator);
		Cubes.Add(Cube);
		Cube->HitDelegateEvent.AddUObject(this, &AMyProjectGameModeBase::ScoreModify);
	}
	
	
}


