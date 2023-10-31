// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCube.h"

#include "MyProjectGameModeBase.h"
#include "SphereChar.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGameCube::AGameCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CubeRoot"));
	CubeMesh->SetupAttachment(RootComponent);
}

void AGameCube::onHit(UPrimitiveComponent* HitComponent,AActor* OtherActor,
	UPrimitiveComponent* OtherComp,FVector NormalImpulse,const FHitResult& Hit)
{
	AGameCube* otherCube = Cast<AGameCube>(OtherActor);
	ASphereChar* otherChar = Cast<ASphereChar>(OtherActor);
	if(otherCube)
	{
		if(otherCube->Status == ECubeStatus::CS_Cleaner && Status == ECubeStatus::CS_Ready)
		{
			SetStatus(ECubeStatus::CS_Clear);
			HitDelegateEvent.Broadcast(-1);
			SoundHitPlay(CleaningAudio);
			
		}
		if(otherCube->Status == ECubeStatus::CS_Ready && Status == ECubeStatus::CS_Clear)
		{
			SetStatus(ECubeStatus::CS_Ready);
			HitDelegateEvent.Broadcast(1);
			SoundHitPlay(FirstHitAudio);
		}
		if(otherCube->Status==ECubeStatus::CS_Ready)
		{
			SoundHitPlay(HitAudio);
		}
	}
	if(otherChar)
	{
		if(Status == ECubeStatus::CS_Clear || Status == ECubeStatus::CS_Cleaner)
		{
			SetStatus(ECubeStatus::CS_Ready);
			HitDelegateEvent.Broadcast(1);
			SoundHitPlay(FirstHitAudio);
		}
		if(Status == ECubeStatus::CS_Ready)
		{
			SoundHitPlay(HitAudio);
		}
		
	}
	
}

void AGameCube::Impulse()
{
	CubeMesh->AddImpulse(FVector(FMath::RandRange(
		-ImpulseX,ImpulseX),
		FMath::RandRange(
			-ImpulseY,ImpulseY),
			ImpulseZ),NAME_None, true);
}

void AGameCube::SetStatus(ECubeStatus status)
{
	Status = status;
	switch (Status)
	{
	case ECubeStatus::CS_Cleaner:
		CubeMesh->SetMaterial(0,CleanerMat);
		break;
	case ECubeStatus::CS_Clear:
		CubeMesh->SetMaterial(0,ClearMat);
		break;
	case ECubeStatus::CS_Ready:
		CubeMesh->SetMaterial(0,ReadyMat);
		break;
		
	}
}

void AGameCube::SoundHitPlay(USoundBase* Sound)
{
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(),Sound,GetActorLocation());
}

// Called when the game starts or when spawned
void AGameCube::BeginPlay()
{
	//
	CubeMesh->OnComponentHit.AddDynamic(this, &AGameCube::onHit);
	Super::BeginPlay();
	uint8 Type = FMath::RandRange(0,1);
	if(Type)
		{SetStatus(ECubeStatus::CS_Clear);}
	else
		{SetStatus(ECubeStatus::CS_Cleaner); }
	
	GetWorldTimerManager().SetTimer(Timer, this ,&AGameCube::Impulse,FMath::FRandRange(1.f,5.f), true, -1);
	
}




