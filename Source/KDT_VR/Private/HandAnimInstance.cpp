// Fill out your copyright notice in the Description page of Project Settings.


#include "HandAnimInstance.h"
#include "VRPlayer.h"


void UHandAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	player = Cast<AVRPlayer>(GetOwningActor());

}

void UHandAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (player != nullptr)
	{
		graspValue = player->rightHandValue;
	}
}
