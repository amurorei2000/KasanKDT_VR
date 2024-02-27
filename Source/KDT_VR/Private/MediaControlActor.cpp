// Fill out your copyright notice in the Description page of Project Settings.


#include "MediaControlActor.h"
#include "MediaPlayer.h"
#include "MediaSource.h"
#include "MediaSoundComponent.h"
#include "Blueprint/UserWidget.h"
#include "MovieWidget.h"


AMediaControlActor::AMediaControlActor()
{
	PrimaryActorTick.bCanEverTick = false;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootComp);

	soundComp = CreateDefaultSubobject<UMediaSoundComponent>(TEXT("Media Sound Component"));
	soundComp->SetupAttachment(RootComponent);

}

void AMediaControlActor::BeginPlay()
{
	Super::BeginPlay();
	
	// 미디어 플레이어에 미디어 소스 파일을 넣는다.
	//myMediaPlayer->OpenSource(myVideo);

	// 미디어 플레이어에 들어있는 소스 파일의 음원을 설정한다.
	//soundComp->SetMediaPlayer(myMediaPlayer);

	// 위젯을 스크린에 출력하기
	UMovieWidget* movieWidgetInst = CreateWidget<UMovieWidget>(GetWorld(), movieWidgetClass);
	if (movieWidgetInst)
	{
		movieWidgetInst->AddToViewport(0);

		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	}
}

void AMediaControlActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

