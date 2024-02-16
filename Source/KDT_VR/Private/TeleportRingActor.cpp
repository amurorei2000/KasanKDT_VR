// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportRingActor.h"
#include "NiagaraComponent.h"


ATeleportRingActor::ATeleportRingActor()
{
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(rootComp);

	ringFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Teleport Ring Effect"));
	ringFX->SetupAttachment(RootComponent);

}

void ATeleportRingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATeleportRingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

