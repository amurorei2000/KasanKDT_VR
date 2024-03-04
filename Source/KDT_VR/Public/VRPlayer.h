// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
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
	class UStaticMeshComponent* gazePointer;

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
	class UNiagaraComponent* lineFX;

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class UWidgetInteractionComponent* widgetPointerRight;

	// 액터 컴포넌트들
	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class UMoveComponent* moveComp;

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class UGrabComponent* grabComp;
	
	UPROPERTY(EditAnywhere, Category = "MySettings|Components")
	class UGazeComponent* gazeComp;

	UPROPERTY(EditAnywhere, Category = "MySettings|Components")
	class UClimbComponent* climbComp;

	// 사용자 인풋
	UPROPERTY(EditAnywhere, Category = "MySettings|Inputs")
	class UInputMappingContext* vrMapping;

	UPROPERTY(EditAnywhere, Category = "MySettings|Inputs")
	TArray<class UInputAction*> vrInputs;

	UPROPERTY(EditAnywhere, Category = "MySettings|Inputs")
	TArray<class UInputAction*> animInputs;

	class APlayerController* pc;

	// 오른손
	float currentRightHandTrigger = 0;
	float rightIndexTouch = 0;
	float currentRightIndexTrigger = 0;
	float rightThumbUpTouch = 0;

	// 왼손
	float currentLeftHandTrigger = 0;
	float leftIndexTouch = 0;
	float currentLeftIndexTrigger = 0;
	float leftThumbUpTouch = 0;

	FORCEINLINE void SetCharGravityScale(float scaleValue) { GetCharacterMovement()->GravityScale = scaleValue; };


private:
	void RightTriggerTouch(const FInputActionValue& val);
	void RightTriggerPress(const FInputActionValue& val);
	void RightTriggerValue(const FInputActionValue& val);
	void Move(const FInputActionValue& val);
	void Rotate(const FInputActionValue& val);
	void RightHandTriggerValue(const FInputActionValue& val);
	void RightIndexTouchValue(const FInputActionValue& val);
	void RightIndexTriggerValue(const FInputActionValue& val);
	void RightThumbUpTouchValue(const FInputActionValue& val);
	void LeftHandTriggerValue(const FInputActionValue& val);
	void LeftIndexTouchValue(const FInputActionValue& val);
	void LeftIndexTriggerValue(const FInputActionValue& val);
	void LeftThumbUpTouchValue(const FInputActionValue& val);
	void LeftYPress(const FInputActionValue& val);

	void ClickLeftMouseButtonPress();
	void ClickLeftMouseButtonRelease();


};
