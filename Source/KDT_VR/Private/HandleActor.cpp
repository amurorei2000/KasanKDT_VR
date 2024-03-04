// Fill out your copyright notice in the Description page of Project Settings.


#include "HandleActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


AHandleActor::AHandleActor()
{
	PrimaryActorTick.bCanEverTick = false;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComp);
	boxComp->SetCollisionProfileName(FName("ClimbPreset"));
	boxComp->SetBoxExtent(FVector(8, 10, 5));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	meshComp->SetupAttachment(boxComp);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	meshComp->SetRelativeLocation(FVector(-5.0f, 0, -3.0f));
	meshComp->SetWorldScale3D(FVector(0.2f));

}

void AHandleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHandleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

