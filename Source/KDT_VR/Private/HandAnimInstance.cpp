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
		graspValue = bMirrored ? player->currentLeftHandTrigger : player->currentRightHandTrigger;

		targetIndexValue = bMirrored ? player->leftIndexTouch : player->rightIndexTouch;
		currentIndexValue = FMath::Lerp(currentIndexValue, targetIndexValue, DeltaSeconds * 13);

		IndexTriggerValue = bMirrored ? player->currentLeftIndexTrigger : player->currentRightIndexTrigger;
		
		targetThumbUpValue = bMirrored ? player->leftThumbUpTouch : player->rightThumbUpTouch;
		currentThumbUpValue = FMath::Lerp(currentThumbUpValue, targetThumbUpValue, DeltaSeconds * 13);
	}
}
