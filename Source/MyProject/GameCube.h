// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameCube.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(HitDelegate, int32);
UENUM(BlueprintType)
enum class ECubeStatus:uint8
{ CS_Clear, CS_Cleaner, CS_Ready };

UCLASS()
class MYPROJECT_API AGameCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameCube();
	HitDelegate HitDelegateEvent;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

	
	UPROPERTY(BlueprintReadOnly)
	ECubeStatus Status;
	
	UFUNCTION()
	void onHit(UPrimitiveComponent* HitComponent,AActor* OtherActor,
	UPrimitiveComponent* OtherComp,FVector NormalImpulse,const FHitResult& Hit);
	
	void Impulse();
	void SetStatus(ECubeStatus status);
	void SoundHitPlay(USoundBase*);
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* CubeMesh;
	
	UPROPERTY(EditDefaultsOnly)
	int32 ImpulseX = 150;
	UPROPERTY(EditDefaultsOnly)
	int32 ImpulseY = 150;
	UPROPERTY(EditDefaultsOnly)
	int32 ImpulseZ = 600;
	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* ClearMat;
	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* CleanerMat;
	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* ReadyMat;
	UPROPERTY(EditDefaultsOnly)
	USoundBase* FirstHitAudio;
	UPROPERTY(EditDefaultsOnly)
	USoundBase* HitAudio;
	UPROPERTY(EditDefaultsOnly)
	USoundBase* CleaningAudio;
	

	
	FTimerHandle Timer;
	

	
	
	

};
