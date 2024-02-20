// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "VRPlayer.h"
#include "PickUpActor.h"


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
	// 1. SweepTrace를 이용한 방식

	FHitResult hitInfo;
	FVector originLoc = player->rightHand->GetComponentLocation();
	FCollisionObjectQueryParams objectParams;
	FCollisionQueryParams params;
	
	bool bChecked = GetWorld()->SweepSingleByObjectType(hitInfo, originLoc, originLoc, FQuat::Identity, objectParams, FCollisionShape::MakeSphere(30), params);

	if (bChecked)
	{
		APickUpActor* pickedObject = Cast<APickUpActor>(hitInfo.GetActor());

		if (pickedObject != nullptr)
		{
			
		}
	}

	// 2. overlap을 이용한 방식


	// 잡으려는 물체의 Physics 설정을 false로 변경한다.

	// 물체를 손에 부착한다.(keep/snap)


}

void UGrabComponent::ReleaseObject()
{

}

