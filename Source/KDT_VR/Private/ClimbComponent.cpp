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
		// 손의 궤적 = 현재 프레임의 손의 위치 - 직전 프레임의 손의 위치
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

		// 몸의 궤적 = 손의 궤적 * -1 (반대 방향)
		//player->SetActorLocation(player->GetActorLocation() + handMovingDir * -1);
		player->AddActorWorldOffset(handMovingDir * -1);
	}

	// 핸드 버튼을 둘 다 놓았다면...
	if(!bGrabbed_left && !bGrabbed_right) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Grabbed both!!"));

		// 플레이어의 movementMode를 낙하 상태로 전환하고, 중력 배율도 1로 변경한다.
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
	// 잡기/놓기 상태로 전환한다.
	bool inputGrab = value.Get<bool>();

	// 핸드 버튼을 눌렀다면...
	if (inputGrab)
	{
		// 만일, 손의 잡기 영역에 핸들이 있었다면...
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
	// 잡기/놓기 상태로 전환한다.
	bool inputGrab = value.Get<bool>();

	// 핸드 버튼을 눌렀다면...
	if (inputGrab)
	{
		// 만일, 손의 잡기 영역에 핸들이 있었다면...
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

// 손의 위치에 핸들이 있는지 여부를 체크하는 함수
bool UClimbComponent::CheckGrab(UMotionControllerComponent* motionController)
{
	FHitResult hitInfo;
	FVector startLoc = motionController->GetComponentLocation();
	FCollisionQueryParams params;
	params.AddIgnoredActor(player);

	return GetWorld()->SweepSingleByChannel(hitInfo, startLoc, startLoc, FQuat::Identity, ECC_GameTraceChannel3, FCollisionShape::MakeSphere(10), params);
}

