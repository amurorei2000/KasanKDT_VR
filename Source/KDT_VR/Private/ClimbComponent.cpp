// Fill out your copyright notice in the Description page of Project Settings.


#include "ClimbComponent.h"
#include "VRPlayer.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"


UClimbComponent::UClimbComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UClimbComponent::BeginPlay()
{
	Super::BeginPlay();

	player = GetOwner<AVRPlayer>();

}


void UClimbComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UClimbComponent::SetupPlayerInputComponent(UEnhancedInputComponent* enhancedInputComponent, TArray<class UInputAction*> inputs)
{
	enhancedInputComponent->BindAction(inputs[3], ETriggerEvent::Started, this, &UClimbComponent::HandleGrabLeft);
	enhancedInputComponent->BindAction(inputs[3], ETriggerEvent::Completed, this, &UClimbComponent::HandleGrabLeft);
	enhancedInputComponent->BindAction(inputs[1], ETriggerEvent::Started, this, &UClimbComponent::HandleGrabRight);
	enhancedInputComponent->BindAction(inputs[1], ETriggerEvent::Completed, this, &UClimbComponent::HandleGrabRight);
}

void UClimbComponent::HandleGrabLeft(const FInputActionValue& value)
{

}

void UClimbComponent::HandleGrabRight(const FInputActionValue& value)
{

}

