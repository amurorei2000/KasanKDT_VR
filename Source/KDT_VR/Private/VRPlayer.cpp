// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "Components/TextRenderComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MoveComponent.h"
#include "NiagaraComponent.h"
#include "GrabComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"


AVRPlayer::AVRPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	cameraComp->SetupAttachment(RootComponent);

	headMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeadMesh"));
	headMesh->SetupAttachment(cameraComp);

	leftMotion = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Left Motion Controller"));
	leftMotion->SetupAttachment(RootComponent);
	leftMotion->MotionSource = FName("Left");

	leftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand Mesh"));
	leftHand->SetupAttachment(leftMotion);
	leftHand->SetRelativeRotation(FRotator(0, 180, -270));

	leftLog = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Left Log"));
	leftLog->SetupAttachment(leftMotion);
	leftLog->SetRelativeLocation(FVector(20, 0, 0));
	leftLog->SetRelativeRotation(FRotator(90, 180, 0));
	leftLog->SetHorizontalAlignment(EHTA_Center);
	leftLog->SetVerticalAlignment(EVRTA_TextCenter);
	leftLog->SetWorldSize(20);
	leftLog->SetTextRenderColor(FColor::Yellow);

	rightMotion = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Motion Controller"));
	rightMotion->SetupAttachment(RootComponent);
	rightMotion->MotionSource = FName("Right");

	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand Mesh"));
	rightHand->SetupAttachment(rightMotion);
	rightHand->SetRelativeRotation(FRotator(0, 0, 90));

	rightLog = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Right Log"));
	rightLog->SetupAttachment(rightMotion);
	rightLog->SetRelativeLocation(FVector(20, 0, 0));
	rightLog->SetRelativeRotation(FRotator(90, 180, 0));
	rightLog->SetHorizontalAlignment(EHTA_Center);
	rightLog->SetVerticalAlignment(EVRTA_TextCenter);
	rightLog->SetWorldSize(20);
	rightLog->SetTextRenderColor(FColor::Yellow);

	lineFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Line Effect"));
	lineFX->SetupAttachment(rightMotion);

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// 커스텀 액터 컴포넌트
	moveComp = CreateDefaultSubobject<UMoveComponent>(TEXT("MoveComponent"));
	grabComp = CreateDefaultSubobject<UGrabComponent>(TEXT("GrabComponent"));

}

void AVRPlayer::BeginPlay()
{
	Super::BeginPlay();

	// Input Mapping Context 파일을 입력 서브 시스템에 등록하는 절차를 실행한다.
	pc = GetController<APlayerController>();
	if (pc != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());

		if (subsys != nullptr)
		{
			subsys->AddMappingContext(vrMapping, 0);
		}
	}

	// HMD 장비의 기준점 설정
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Type::Eye);

}

void AVRPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVRPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (enhancedInputComponent != nullptr)
	{
#pragma region Input Test
		// 입력 컴포넌트에 RightTriggerTouch() 함수를 연결한다.(닿았을 때, 뗏을 때)
		//enhancedInputComponent->BindAction(vrInputs[0], ETriggerEvent::Started, this, &AVRPlayer::RightTriggerTouch);
		//enhancedInputComponent->BindAction(vrInputs[0], ETriggerEvent::Completed, this, &AVRPlayer::RightTriggerTouch);
		//enhancedInputComponent->BindAction(vrInputs[1], ETriggerEvent::Started, this, &AVRPlayer::RightTriggerPress);
		//enhancedInputComponent->BindAction(vrInputs[1], ETriggerEvent::Completed, this, &AVRPlayer::RightTriggerPress);
		//enhancedInputComponent->BindAction(vrInputs[2], ETriggerEvent::Triggered, this, &AVRPlayer::RightTriggerValue);
		//enhancedInputComponent->BindAction(vrInputs[2], ETriggerEvent::Completed, this, &AVRPlayer::RightTriggerValue);
		//enhancedInputComponent->BindAction(leftThumbstickAxis, ETriggerEvent::Triggered, this, &AVRPlayer::Move);
		//enhancedInputComponent->BindAction(leftThumbstickAxis, ETriggerEvent::Completed, this, &AVRPlayer::Move);
		//enhancedInputComponent->BindAction(vrInputs[3], ETriggerEvent::Triggered, this, &AVRPlayer::Rotate);
		//enhancedInputComponent->BindAction(vrInputs[3], ETriggerEvent::Completed, this, &AVRPlayer::Rotate);
		
		enhancedInputComponent->BindAction(animInputs[0], ETriggerEvent::Triggered, this, &AVRPlayer::RightHandTriggerValue);
		enhancedInputComponent->BindAction(animInputs[0], ETriggerEvent::Completed, this, &AVRPlayer::RightHandTriggerValue);

#pragma endregion

		if (moveComp != nullptr)
		{
			moveComp->SetupPlayerInputComponent(enhancedInputComponent, vrInputs);
		}

		grabComp->SetupPlayerInputComponent(enhancedInputComponent, vrInputs);

	}
}

void AVRPlayer::RightTriggerTouch(const FInputActionValue& val)
{
	// 입력받은 값을 오른손 로그에 출력한다.
	FString result = val.Get<bool>() == true ? FString("True") : FString("False");
	//rightLog->SetText(FText::FromString(FString::Printf(TEXT("Right Index touch: %s"), *result)));
}

void AVRPlayer::RightTriggerPress(const FInputActionValue& val)
{
	FString result = val.Get<bool>() == true ? FString("True") : FString("False");
	//rightLog->SetText(FText::FromString(FString::Printf(TEXT("Right Index Pressed: %s"), *result)));
	
}

void AVRPlayer::RightTriggerValue(const FInputActionValue& val)
{
	float pressed = val.Get<float>();
	rightLog->SetText(FText::FromString(FString::Printf(TEXT("Right Index Pressed: %.3f"), pressed)));
}

void AVRPlayer::Move(const FInputActionValue& val)
{
	FVector2D dir = val.Get<FVector2D>();
	// 입력 값 확인용 출력 로그
	leftLog->SetText(FText::FromString(FString::Printf(TEXT("X: %.2f\nY: %.2f"), dir.X, dir.Y)));

	// 현재 바라보고 있는 방향으로 이동한다.
	FVector originVec = FVector(dir.Y, dir.X, 0);
	FVector newVec = GetTransform().TransformVector(originVec);

	AddMovementInput(newVec);
}

void AVRPlayer::Rotate(const FInputActionValue& val)
{
	FVector2D dir = val.Get<FVector2D>();
	rightLog->SetText(FText::FromString(FString::Printf(TEXT("X: %.2f\nY: %.2f"), dir.X, dir.Y)));

	// 입력받은 방향으로 회전한다.
	AddControllerYawInput(dir.X);
}

void AVRPlayer::RightHandTriggerValue(const FInputActionValue& val)
{
	rightHandValue = val.Get<float>();
}

