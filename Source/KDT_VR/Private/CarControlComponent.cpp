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

	// ������ ��Ʈ�ѷ� ��ġ - �޼� ��Ʈ�ѷ� ��ġ ���� ����ȭ�� ���͸� ���Ѵ�.
	FVector wheelVector = (player->rightMotion->GetComponentLocation() - player->leftMotion->GetComponentLocation()).GetSafeNormal();

	// �÷��̾� ������ ������ ������ �������� ���� wheelVector���� ������ ���Ѵ�(����)
	float cosTheta = FVector::DotProduct(player->GetActorRightVector(), wheelVector);
	float degree = FMath::RadiansToDegrees(FMath::Acos(cosTheta));
	
	// �÷��̾� ������ ���� ������ �������� wheelVector���� ������ ���Ѵ�.(����)
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

