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
	myMediaPlayer->OnMediaOpened.AddDynamic(this, &UMovieWidget::MediaStartPlay);
	btn_forward->OnClicked.AddDynamic(this, &UMovieWidget::MediaForward);
}

void UMovieWidget::MediaStop()
{
	myMediaPlayer->Close();
}

void UMovieWidget::MediaPlay()
{
	// 만일, 미디어 소스가 없는 경우라면...
	if (myMediaPlayer->IsClosed())
	{
		// 소스를 넣는다.
		myMediaPlayer->OpenSource(myVideo);
	}
	// 그렇지 않고 만일, 미디어 소스는 있지만 플레이 중은 아닐때...
	else if (!myMediaPlayer->IsPlaying() || myMediaPlayer->IsPaused())
	{
		// 플레이를 해준다.
		myMediaPlayer->Play();
	}
	// 그렇지않고 만일, 플레이 중인 상태라면...
	else if (myMediaPlayer->IsPlaying())
	{
		// 일시정지를 해준다.
		myMediaPlayer->Pause();
	}
	
	// 방법1. 미디어 소스 읽은 후 0.1초 뒤에 플레이 시작
	//GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UMovieWidget::MediaStartPlay);
	//FTimerHandle mediaPlayHandler;
	//GetWorld()->GetTimerManager().SetTimer(mediaPlayHandler, this, &UMovieWidget::MediaStartPlay, 0.1f, false);

	// 방법 2. OpenSource 를 한 후에 완료 이벤트를 받아서 플레이 시작(델리게이트)

}

void UMovieWidget::MediaStartPlay(FString OpenedUrl)
{
	UE_LOG(LogTemp, Warning, TEXT("Source Open Complete: %s"), *OpenedUrl);
	myMediaPlayer->Play();
}

void UMovieWidget::MediaForward()
{
	MediaForwardToSeconds(10);
}

void UMovieWidget::MediaForwardToSeconds(float seconds)
{
	FTimespan newTime = myMediaPlayer->GetTime() + FTimespan(0, 0, seconds);
	myMediaPlayer->Seek(newTime);
}
