// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "IKAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class KDT_VR_API UIKAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	class AVRPlayer* player;
	class UMotionControllerComponent* leftHand;
	class UMotionControllerComponent* rightHand;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings")
	FVector headLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="MySettings")
	FVector leftHandLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings")
	FVector rightHandLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings")
	FRotator headRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings")
	FRotator leftHandRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings")
	FRotator rightHandRotation;

};
