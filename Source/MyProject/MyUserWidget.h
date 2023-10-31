// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */

class UBackgroundBlur;
class UTextBlock;

UCLASS()
class MYPROJECT_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* Score;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UBackgroundBlur* Blure;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* WinMessenge;
	
	void ScoreChanger(int32);
	void GameOver();
};
