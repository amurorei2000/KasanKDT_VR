// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HandAnimInstance.generated.h"


UCLASS()
class KDT_VR_API UHandAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="MySettings")
	float graspValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings")
	float currentIndexValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings")
	float targetIndexValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings")
	float IndexTriggerValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings")
	float currentThumbUpValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings")
	float targetThumbUpValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings")
	bool bMirrored = false;

private:
	class AVRPlayer* player;

};
