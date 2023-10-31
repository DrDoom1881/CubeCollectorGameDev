// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "SphereChar.generated.h"

class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;
UCLASS()
class MYPROJECT_API ASphereChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASphereChar();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	const uint32& ScoreGet() const {return MyScore;};
	void ScoreSet(uint32);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	uint32 MyScore = 0;
	
	UPROPERTY(EditDefaultsOnly)
	float Speed  = 4;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* CharMesh;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CharCam;
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CharSpringArm;

private:
	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void MouseUp(float Axis);
	UStaticMeshComponent* MeshGet() const;


	// Called to bind functionality to input
	

};
