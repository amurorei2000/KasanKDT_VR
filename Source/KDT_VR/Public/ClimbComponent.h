// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputActionValue.h"
#include "ClimbComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KDT_VR_API UClimbComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UClimbComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetupPlayerInputComponent(class UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*> inputs);
	
private:
	class AVRPlayer* player;

	void HandleGrabLeft(const FInputActionValue& value);
	void HandleGrabRight(const FInputActionValue& value);
};
