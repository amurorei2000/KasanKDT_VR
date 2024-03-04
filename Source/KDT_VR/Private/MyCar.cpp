// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCar.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


AMyCar::AMyCar()
{
	PrimaryActorTick.bCanEverTick = false;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	meshComp->SetupAttachment(boxComp);
}

void AMyCar::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyCar::Move(FVector moveDirection)
{
	SetActorLocation(GetActorLocation() + moveDirection);
}

void AMyCar::Rotate(float degree)
{
	SetActorRotation(FRotator(0, degree, 0));
}

