// Fill out your copyright notice in the Description page of Project Settings.


#include "SphericalMovieActor.h"
#include "Components/StaticMeshComponent.h"
#include "MediaPlayer.h"
#include "MediaSource.h"


ASphericalMovieActor::ASphericalMovieActor()
{
	PrimaryActorTick.bCanEverTick = false;

	movieMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Movie Mesh"));
	SetRootComponent(movieMesh);
	movieMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void ASphericalMovieActor::BeginPlay()
{
	Super::BeginPlay();

	if (vrMediaPlayer != nullptr)
	{
		vrMediaPlayer->PlayOnOpen = true;
		vrMediaPlayer->OpenSource(vrMediaSource);
	}
}

void ASphericalMovieActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

