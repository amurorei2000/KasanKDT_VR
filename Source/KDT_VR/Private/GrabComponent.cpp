// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "VRPlayer.h"
#include "PickUpActor.h"
#include "Components/SkeletalMeshComponent.h"


UGrabComponent::UGrabComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UGrabComponent::BeginPlay()
{
	Super::BeginPlay();

	player = GetOwner<AVRPlayer>();

}


void UGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UGrabComponent::SetupPlayerInputComponent(UEnhancedInputComponent* PlayerInputComponent, TArray<class UInputAction*> inputs)
{
	PlayerInputComponent->BindAction(inputs[1], ETriggerEvent::Started, this, &UGrabComponent::GrabObject);
	PlayerInputComponent->BindAction(inputs[1], ETriggerEvent::Completed, this, &UGrabComponent::ReleaseObject);
}

void UGrabComponent::GrabObject()
{
	// 범위형 충돌 체크(Object Type: PickUp)
#pragma region SweepTrace Type
	// 1. SweepTrace를 이용한 방식
	/*FHitResult hitInfo;
	FVector originLoc = player->rightHand->GetComponentLocation();
	FCollisionObjectQueryParams objectParams;
	objectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel2);

	FCollisionQueryParams params;
	params.AddIgnoredActor(player);

	bool bChecked = GetWorld()->SweepSingleByObjectType(hitInfo, originLoc, originLoc, FQuat::Identity, objectParams, FCollisionShape::MakeSphere(30), params);

	if (bChecked)
	{
		APickUpActor* pickedObject = Cast<APickUpActor>(hitInfo.GetActor());
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *hitInfo.GetActor()->GetActorNameOrLabel());

		if (pickedObject != nullptr)
		{
			pickedObject->OnGrabbed(player->rightHand);
		}
	}*/
#pragma endregion

#pragma region Overlap Type
	// 2. overlap을 이용한 방식
	TArray<FOverlapResult> hitInfos;
	FCollisionObjectQueryParams objectParams;
	objectParams.AddObjectTypesToQuery(ECC_GameTraceChannel2);

	FCollisionQueryParams params;
	params.AddIgnoredActor(player);

	bool bChecked = GetWorld()->OverlapMultiByObjectType(hitInfos, player->rightHand->GetComponentLocation(), FQuat::Identity, objectParams, FCollisionShape::MakeSphere(20), params);
	// 충돌 체크 범위 시각화
	DrawDebugSphere(GetWorld(), player->rightHand->GetComponentLocation(), 20, 30, FColor::Green, false, 2.0f, 0, 1);

	if (bChecked)
	{
		// 범위 내의 감지된 모든 PickUpActor 오브젝트들을 다 잡기
		for (const FOverlapResult& hitInfo : hitInfos)
		{
			APickUpActor* pickedObj = Cast<APickUpActor>(hitInfo.GetActor());

			if (pickedObj != nullptr)
			{
				pickedObj->OnGrabbed(player->rightHand);
			}
		}
	}
#pragma endregion

}

// 물체를 놓는 함수
void UGrabComponent::ReleaseObject()
{
	// 
}

