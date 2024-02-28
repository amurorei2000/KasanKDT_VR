// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPawn.h"
#include "Components/CapsuleComponent.h"
#include "MotionControllerComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/SkeletalMeshComponent.h"


ATestPawn::ATestPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	rootCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root Collider"));
	SetRootComponent(rootCapsule);
	rootCapsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	rootCapsule->SetCollisionObjectType(ECC_Pawn);

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Eye"));
	cameraComp->SetupAttachment(RootComponent);

	rightMotion = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Motion Controller"));
	rightMotion->SetupAttachment(RootComponent);
	rightMotion->SetRelativeLocation(FVector(150, 0, 0));
	rightMotion->MotionSource = FName("Right");

	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand Mesh"));
	rightHand->SetupAttachment(rightMotion);

	widgetPointerRight = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Right Widget Pointer"));
	widgetPointerRight->SetupAttachment(rightMotion);
	widgetPointerRight->bShowDebug = true;
	widgetPointerRight->InteractionDistance = 1000;
}

void ATestPawn::BeginPlay()
{
	Super::BeginPlay();
	
	pc = GetController<APlayerController>();
	if (pc != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());

		if (subsys != nullptr)
		{
			subsys->AddMappingContext(vrMapping, 0);
		}
	}

	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Eye);

}

void ATestPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void ATestPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (enhancedInputComponent != nullptr)
	{
		enhancedInputComponent->BindAction(vrInputs[5], ETriggerEvent::Started, this, &ATestPawn::ClickLeftMouseButtonPress);
		enhancedInputComponent->BindAction(vrInputs[5], ETriggerEvent::Completed, this, &ATestPawn::ClickLeftMouseButtonRelease);
	}
}

void ATestPawn::ClickLeftMouseButtonPress()
{
	// 키보드 버튼을 누른 효과를 줄 때
	//widgetPointerRight->PressKey();

	// 마우스 버튼을 누른 효과를 줄 때
	widgetPointerRight->PressPointerKey(EKeys::LeftMouseButton);
}

void ATestPawn::ClickLeftMouseButtonRelease()
{
	widgetPointerRight->ReleasePointerKey(EKeys::LeftMouseButton);
}

