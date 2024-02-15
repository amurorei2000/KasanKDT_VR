// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "VRPlayer.generated.h"

UCLASS()
class KDT_VR_API AVRPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AVRPlayer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class UCameraComponent* cameraComp;

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class UStaticMeshComponent* headMesh;

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class UMotionControllerComponent* leftMotion;

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class USkeletalMeshComponent* leftHand;

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class UTextRenderComponent* leftLog;

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class UMotionControllerComponent* rightMotion;

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class USkeletalMeshComponent* rightHand;

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class UTextRenderComponent* rightLog;

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class UMoveComponent* moveComp;

	UPROPERTY(EditAnywhere, Category = "MySettings|Inputs")
	class UInputMappingContext* vrMapping;

	UPROPERTY(EditAnywhere, Category = "MySettings|Inputs")
	TArray<class UInputAction*> vrInputs;


private:
	void RightTriggerTouch(const FInputActionValue& val);
	void RightTriggerPress(const FInputActionValue& val);
	void RightTriggerValue(const FInputActionValue& val);
	void Move(const FInputActionValue& val);
	void Rotate(const FInputActionValue& val);
};
