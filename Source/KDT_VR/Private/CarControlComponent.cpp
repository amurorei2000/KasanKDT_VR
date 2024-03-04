// Fill out your copyright notice in the Description page of Project Settings.


#include "CarControlComponent.h"
#include "VRPlayer.h"
#include "MotionControllerComponent.h"
#include "MyCar.h"
#include "EngineUtils.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"


UCarControlComponent::UCarControlComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCarControlComponent::BeginPlay()
{
	Super::BeginPlay();

	player = GetOwner<AVRPlayer>();

	for (TActorIterator<AMyCar> iter(GetWorld()); iter; ++iter)
	{
		myCar = *iter;
	}

}


void UCarControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 오른손 컨트롤러 위치 - 왼손 컨트롤러 위치 값을 정규화한 벡터를 구한다.
	FVector wheelVector = (player->rightMotion->GetComponentLocation() - player->leftMotion->GetComponentLocation()).GetSafeNormal();

	// 플레이어 액터의 오른쪽 방향을 기준으로 위의 wheelVector와의 각도를 구한다(내적)
	float cosTheta = FVector::DotProduct(player->GetActorRightVector(), wheelVector);
	float degree = FMath::RadiansToDegrees(FMath::Acos(cosTheta));
	
	// 플레이어 액터의 위쪽 방향을 기준으로 wheelVector와의 각도를 구한다.(내적)
	float upTheta = FVector::DotProduct(player->GetActorUpVector(), wheelVector);
	if (upTheta >= 0)
	{
		degree *= -1.0f;
	}
	
	//UE_LOG(LogTemp, Warning, TEXT("degree : %.1f"), degree);
	if (myCar != nullptr)
	{
		myCar->Rotate(degree);
	}
}

void UCarControlComponent::SetupPlayerInputComponent(UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*> inputs)
{
	enhancedInputComponent->BindAction(inputs[5], ETriggerEvent::Triggered, this, &UCarControlComponent::AccelerationCar);
}

void UCarControlComponent::AccelerationCar()
{
	if (myCar != nullptr)
	{
		myCar->Move(myCar->GetActorForwardVector());
	}
}

