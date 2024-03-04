// Fill out your copyright notice in the Description page of Project Settings.


#include "ClimbComponent.h"
#include "VRPlayer.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "MotionControllerComponent.h"



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

	if (bGrabbed_left || bGrabbed_right)
	{
		// ���� ���� = ���� �������� ���� ��ġ - ���� �������� ���� ��ġ
		FVector prevHandLoc = lastHand == player->leftMotion ? prevHandLoc_left : prevHandLoc_right;
		FVector handMovingDir = lastHand->GetComponentLocation() - prevHandLoc;
		
		if (lastHand == player->leftMotion)
		{
			prevHandLoc_left = lastHand->GetComponentLocation();
		}
		else
		{
			prevHandLoc_right = lastHand->GetComponentLocation();
		}
		//FVector handMovingDir = FVector::DownVector;

		// ���� ���� = ���� ���� * -1 (�ݴ� ����)
		//player->SetActorLocation(player->GetActorLocation() + handMovingDir * -1);
		player->AddActorWorldOffset(handMovingDir * -1);
	}

	// �ڵ� ��ư�� �� �� ���Ҵٸ�...
	if(!bGrabbed_left && !bGrabbed_right) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Grabbed both!!"));

		// �÷��̾��� movementMode�� ���� ���·� ��ȯ�ϰ�, �߷� ������ 1�� �����Ѵ�.
		player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		player->SetCharGravityScale(1);
	}

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
	// ���/���� ���·� ��ȯ�Ѵ�.
	bool inputGrab = value.Get<bool>();

	// �ڵ� ��ư�� �����ٸ�...
	if (inputGrab)
	{
		// ����, ���� ��� ������ �ڵ��� �־��ٸ�...
		if (CheckGrab(player->leftMotion))
		{
			prevHandLoc_left = player->leftMotion->GetComponentLocation();
			bGrabbed_left = true;
			lastHand = player->leftMotion;
			player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Custom);
			player->SetCharGravityScale(0);
		}
	}
	else
	{
		bGrabbed_left = false;
	}
	
}

void UClimbComponent::HandleGrabRight(const FInputActionValue& value)
{
	// ���/���� ���·� ��ȯ�Ѵ�.
	bool inputGrab = value.Get<bool>();

	// �ڵ� ��ư�� �����ٸ�...
	if (inputGrab)
	{
		// ����, ���� ��� ������ �ڵ��� �־��ٸ�...
		if (CheckGrab(player->rightMotion))
		{
			prevHandLoc_right = player->rightMotion->GetComponentLocation();
			bGrabbed_right = true;
			lastHand = player->rightMotion;
			player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Custom);
			player->SetCharGravityScale(0);
		}
	}
	else
	{
		bGrabbed_right = false;
	}

}

// ���� ��ġ�� �ڵ��� �ִ��� ���θ� üũ�ϴ� �Լ�
bool UClimbComponent::CheckGrab(UMotionControllerComponent* motionController)
{
	FHitResult hitInfo;
	FVector startLoc = motionController->GetComponentLocation();
	FCollisionQueryParams params;
	params.AddIgnoredActor(player);

	return GetWorld()->SweepSingleByChannel(hitInfo, startLoc, startLoc, FQuat::Identity, ECC_GameTraceChannel3, FCollisionShape::MakeSphere(10), params);
}

