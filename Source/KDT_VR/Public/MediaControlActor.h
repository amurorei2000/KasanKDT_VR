// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MediaControlActor.generated.h"

UCLASS()
class KDT_VR_API AMediaControlActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMediaControlActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="MySettings")
	class UMediaPlayer* myMediaPlayer;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UMediaSource* myVideo;

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class USceneComponent* rootComp;

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class UMediaSoundComponent* soundComp;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	TSubclassOf<class UMovieWidget> movieWidgetClass;
};
