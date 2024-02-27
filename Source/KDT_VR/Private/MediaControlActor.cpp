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
	
	// �̵�� �÷��̾ �̵�� �ҽ� ������ �ִ´�.
	//myMediaPlayer->OpenSource(myVideo);

	// �̵�� �÷��̾ ����ִ� �ҽ� ������ ������ �����Ѵ�.
	//soundComp->SetMediaPlayer(myMediaPlayer);

	// ������ ��ũ���� ����ϱ�
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

