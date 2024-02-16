// Fill out your copyright notice in the Description page of Project Settings.


#include "BallActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"


ABallActor::ABallActor()
{
	PrimaryActorTick.bCanEverTick = true;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SetRootComponent(sphereComp);
	sphereComp->SetSphereRadius(20.0f);
	sphereComp->SetSimulatePhysics(true);
	sphereComp->SetEnableGravity(false);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	meshComp->SetWorldScale3D(FVector(0.2f));
}

void ABallActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

