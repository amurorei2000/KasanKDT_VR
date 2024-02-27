// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MovieWidget.generated.h"

/**
 * 
 */
UCLASS()
class KDT_VR_API UMovieWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UMediaPlayer* myMediaPlayer;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UMediaSource* myVideo;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category = "MySettings")
	class UImage* img_Screen;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "MySettings")
	class UButton* btn_stop;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "MySettings")
	class UButton* btn_play;
	
protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void MediaStop();

	UFUNCTION()
	void MediaPlay();

	UFUNCTION()
	void MediaStartPlay();
};
