// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereChar.h"

#include <string>

#include "Camera/CameraComponent.h"
#include "Camera/CameraModifier.h"
#include "Components/CapsuleComponent.h"
#include "Components/MeshComponent.h"
// Sets default values
ASphereChar::ASphereChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CharMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CharMesh"));
	CharCam = CreateDefaultSubobject<UCameraComponent>(TEXT("Cam"));
	CharSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CharArm"));
	CharMesh->SetupAttachment(GetCapsuleComponent());
	CharSpringArm->SetupAttachment(GetCapsuleComponent());
	CharCam->SetupAttachment(CharSpringArm);
	
	
}

// Called when the game starts or when spawned
void ASphereChar::BeginPlay()
{
	Super::BeginPlay();
	
}
UStaticMeshComponent* ASphereChar::MeshGet() const
{
	return CharMesh;
}

void ASphereChar::ScoreSet(uint32 Score)
{
	if(Score < 0 && MyScore == 0)
	{
		MyScore = 0;	
	}
		
	MyScore = Score;
	GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Red, std::to_string(MyScore).c_str() );
}

void ASphereChar::MoveForward(float Axis)
{

	FVector ForwardVector =  FRotator(0,GetControlRotation().Yaw,0).Vector();

	AddMovementInput(ForwardVector*100.f*Axis);
	
	CharMesh->AddWorldRotation((Speed / CharMesh->GetStaticMesh()->GetBounds().SphereRadius) *
		FRotator(
			ForwardVector.X * Axis  * -90,
			0 ,
			ForwardVector.Y * Axis * 90
			));
		
	//SetActorRotation(GetActorRotation());
	//GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Red, *GetActorForwardVector().ToString() );
	//GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Red, *FString::Printf(TEXT("%f"), Axis) );
}
void ASphereChar::MoveRight(float Axis)
{
	FVector ForwardVector = FRotationMatrix(FRotator(0,GetControlRotation().Yaw,0)).GetScaledAxis(EAxis::Y);
	
	AddMovementInput( ForwardVector *100.f*Axis);
	CharMesh->AddWorldRotation((Speed / CharMesh->GetStaticMesh()->GetBounds().SphereRadius) *
FRotator(
	ForwardVector.X * Axis * -90 ,
	0,
	ForwardVector.Y * Axis  * 90
	
	));
}

void ASphereChar::MouseUp(float Axis)
{
	CharSpringArm->AddRelativeRotation(FRotator(Axis, 0, 0));
};

// Called to bind functionality to input
void ASphereChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &ASphereChar::MoveForward );
	PlayerInputComponent->BindAxis("MoveRight", this, &ASphereChar::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed ,this, &ACharacter::Jump);
	PlayerInputComponent->BindAxis("MouseUp", this,&ACharacter::AddControllerPitchInput);//&ASphereChar::MouseUp
	PlayerInputComponent->BindAxis("MouseRight", this,&ACharacter::AddControllerYawInput);

}

