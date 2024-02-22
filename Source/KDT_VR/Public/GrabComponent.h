// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GrabComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KDT_VR_API UGrabComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGrabComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent, TArray<class UInputAction*> inputs);

	UPROPERTY(EditAnywhere, Category = "MySettings")
	float throwPower = 500;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	float throwThreshold = 0.3f;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UHapticFeedbackEffect_Base* grabHaptic;

private:
	class AVRPlayer* player;
	class APickUpActor* currentObject;
	FVector currentLocation_rightCon;
	FVector previousLocation_rightCon;

	void GrabObject();
	void ReleaseObject();
};
