// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TestPawn.generated.h"

UCLASS()
class KDT_VR_API ATestPawn : public APawn
{
	GENERATED_BODY()

public:
	ATestPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category="MySettings|Components")
	class UCapsuleComponent* rootCapsule;

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class UCameraComponent* cameraComp;

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class UMotionControllerComponent* rightMotion;

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class USkeletalMeshComponent* rightHand;

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class UWidgetInteractionComponent* widgetPointerRight;

	UPROPERTY(EditAnywhere, Category = "MySettings|Inputs")
	class UInputMappingContext* vrMapping;

	UPROPERTY(EditAnywhere, Category = "MySettings|Inputs")
	TArray<class UInputAction*> vrInputs;

	class APlayerController* pc;

private:
	void ClickLeftMouseButtonPress();
	void ClickLeftMouseButtonRelease();

};
