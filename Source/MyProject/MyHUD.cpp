// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"

#include "Blueprint/UserWidget.h"

AMyHUD::AMyHUD(): MainWidget(nullptr)
{
	//MainWidget = CreateDefaultSubobject<UUserWidget>(TEXT("widget"));
}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();
	MainWidget = CreateWidget(GetWorld(), MainWidgetClass);
	MainWidget->AddToViewport();
	
}
