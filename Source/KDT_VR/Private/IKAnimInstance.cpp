// Fill out your copyright notice in the Description page of Project Settings.


#include "IKAnimInstance.h"
#include "VRPlayer.h"
#include "MotionControllerComponent.h"
#include "Camera/CameraComponent.h"


void UIKAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	player = Cast<AVRPlayer>(GetOwningActor());

	if (player != nullptr)
	{
		leftHand = player->leftMotion;
		rightHand = player->rightMotion;
	}
}

void UIKAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (leftHand != nullptr && rightHand != nullptr)
	{
		headLocation = player->cameraComp->GetComponentLocation();
		headRotation = player->cameraComp->GetComponentRotation();

		leftHandLocation = leftHand->GetComponentLocation();
		leftHandRotation = leftHand->GetComponentRotation();

		rightHandLocation = rightHand->GetComponentLocation();
		rightHandRotation = rightHand->GetComponentRotation();
		rightHandRotation = FRotator(rightHandRotation.Pitch * -1, rightHandRotation.Yaw, rightHandRotation.Roll);
	}
}
