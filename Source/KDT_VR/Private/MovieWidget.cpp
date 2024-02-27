// Fill out your copyright notice in the Description page of Project Settings.


#include "MovieWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "MediaPlayer.h"
#include "MediaSource.h"


void UMovieWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (myMediaPlayer != nullptr && myVideo != nullptr)
	{
		//myMediaPlayer->PlayOnOpen = false;

		myMediaPlayer->OpenSource(myVideo);
	}

	btn_stop->OnClicked.AddDynamic(this, &UMovieWidget::MediaStop);
	btn_play->OnClicked.AddDynamic(this, &UMovieWidget::MediaPlay);
}

void UMovieWidget::MediaStop()
{
	myMediaPlayer->Close();
}

void UMovieWidget::MediaPlay()
{
	myMediaPlayer->OpenSource(myVideo);
	//myMediaPlayer->open
	
	//GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UMovieWidget::MediaStartPlay);
	FTimerHandle mediaPlayHandler;

	GetWorld()->GetTimerManager().SetTimer(mediaPlayHandler, this, &UMovieWidget::MediaStartPlay, 0.1f, false);
}

void UMovieWidget::MediaStartPlay()
{
	myMediaPlayer->Play();
}
