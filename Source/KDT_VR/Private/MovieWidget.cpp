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
	// ����, �̵�� �ҽ��� ���� �����...
	if (myMediaPlayer->IsClosed())
	{
		// �ҽ��� �ִ´�.
		myMediaPlayer->OpenSource(myVideo);
	}
	// �׷��� �ʰ� ����, �̵�� �ҽ��� ������ �÷��� ���� �ƴҶ�...
	else if (!myMediaPlayer->IsPlaying() || myMediaPlayer->IsPaused())
	{
		// �÷��̸� ���ش�.
		myMediaPlayer->Play();
	}
	// �׷����ʰ� ����, �÷��� ���� ���¶��...
	else if (myMediaPlayer->IsPlaying())
	{
		// �Ͻ������� ���ش�.
		myMediaPlayer->Pause();
	}
	
	// ���1. �̵�� �ҽ� ���� �� 0.1�� �ڿ� �÷��� ����
	//GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UMovieWidget::MediaStartPlay);
	//FTimerHandle mediaPlayHandler;
	//GetWorld()->GetTimerManager().SetTimer(mediaPlayHandler, this, &UMovieWidget::MediaStartPlay, 0.1f, false);

	// ��� 2. OpenSource �� �� �Ŀ� �Ϸ� �̺�Ʈ�� �޾Ƽ� �÷��� ����(��������Ʈ)

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
