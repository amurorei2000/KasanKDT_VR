// Fill out your copyright notice in the Description page of Project Settings.


#include "GazeComponent.h"
#include "VRPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"


UGazeComponent::UGazeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	player = GetOwner<AVRPlayer>();
	if (player != nullptr)
	{
		gazeMesh = player->gazePointer;
	}
}


void UGazeComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UGazeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CheckShowObjects())
	{
		rate += DeltaTime;
	}
	else
	{
		rate -= DeltaTime;
	}
	rate = FMath::Clamp(rate, 0.0f, 1.0f);

	FVector calcSize = FMath::Lerp(FVector(minSize), FVector(maxSize), rate);
	gazeMesh->SetWorldScale3D(calcSize);
}

bool UGazeComponent::CheckShowObjects()
{
	FHitResult hitInfo;
	FCollisionQueryParams params;
	params.AddIgnoredActor(player);
	FVector startVec = player->cameraComp->GetComponentLocation();
	FVector camForward = FRotationMatrix(player->cameraComp->GetComponentRotation()).GetUnitAxis(EAxis::X);
	FVector endVec = startVec + camForward * maxSight;

	return GetWorld()->LineTraceSingleByChannel(hitInfo, startVec, endVec, ECC_Visibility, params);
}

