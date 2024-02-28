// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetMovieActor.h"
#include "Components/WidgetComponent.h"


AWidgetMovieActor::AWidgetMovieActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(rootComp);

	movieWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Movie Widget Component"));
	movieWidgetComp->SetupAttachment(RootComponent);

}

void AWidgetMovieActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWidgetMovieActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

