// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"

#include "MyProjectGameModeBase.h"
#include "Components/BackgroundBlur.h"
#include "Components/TextBlock.h"

void UMyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(AMyProjectGameModeBase* GM = Cast<AMyProjectGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		GM->ScoreDelegateEvent.AddUObject(this, &UMyUserWidget::ScoreChanger);

	}
}

//
void UMyUserWidget::ScoreChanger(int32 Value)
{
	Score->SetText(FText::FromString(FString::FromInt(Value)));
	AMyProjectGameModeBase* GM = Cast<AMyProjectGameModeBase>(GetWorld()->GetAuthGameMode());
	if(!GM->GameStatus())
	{
		GameOver();
	}
}

void UMyUserWidget::GameOver()
{
	Blure->SetBlurStrength(100);
	WinMessenge->SetText(FText::FromString(FString("You Win"))); 
}
