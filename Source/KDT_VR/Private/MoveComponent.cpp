// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "VRPlayer.h"
#include "MotionControllerComponent.h"
#include "GameFramework/PlayerController.h"
#include "NiagaraDataInterfaceArrayFunctionLibrary.h"
#include "TeleportRingActor.h"
#include "NiagaraComponent.h"
#include "BallActor.h"
#include "Components/SphereComponent.h"
#include "MyVRFunctionLibrary.h"


UMoveComponent::UMoveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;


}


void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	player = GetOwner<AVRPlayer>();

	// �ڷ���Ʈ Ÿ�� ������ ǥ���� �� ����Ʈ�� ���� �� ��Ȱ��ȭ�Ѵ�.
	//ringInstance = GetWorld()->SpawnActor<ATeleportRingActor>(ringActor, player->GetActorLocation(), player->GetActorRotation());
	//ringInstance->ringFX->SetVisibility(false);

	// ���� �񱳿� �� ���� �����ϱ�
	/*FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ballInstance = GetWorld()->SpawnActor<ABallActor>(ballActor, player->rightMotion->GetComponentLocation(), FRotator::ZeroRotator, params);*/
}


void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsShowLine && player != nullptr)
	{
		UMotionControllerComponent* rightMotionCon = player->rightMotion;
		if (rightMotionCon != nullptr)
		{
			FVector handLocation = rightMotionCon->GetComponentLocation();
			FVector direction = rightMotionCon->GetForwardVector() + rightMotionCon->GetUpVector() * -1;

			// ���� ������ ������� �׸���.
			DrawTrajectory(handLocation, direction.GetSafeNormal(), power, throwTime, throwTerm);

			// ������ � ������� �׸���.
			//DrawBezierLine(rightMotionCon);
		}
	}

	// ���� �߻��ϱ� ���� ���� ���� �Ѿƴٴϵ��� ó���ϱ�
	/*if (!bShootBall)
	{
		ballInstance->SetActorLocation(player->rightMotion->GetComponentLocation());
	}*/
}

void UMoveComponent::SetupPlayerInputComponent(UEnhancedInputComponent* PlayerInputComponent, TArray<UInputAction*> inputs)
{
	//PlayerInputComponent->BindAction(inputs[0], ETriggerEvent::Started, this, &UMoveComponent::ShootBall);
	PlayerInputComponent->BindAction(inputs[0], ETriggerEvent::Triggered, this, &UMoveComponent::ShowTrajectory);
	PlayerInputComponent->BindAction(inputs[0], ETriggerEvent::Completed, this, &UMoveComponent::TeleportToTarget);
}

void UMoveComponent::ShootBall()
{
	if (ballInstance != nullptr)
	{
		UMotionControllerComponent* rightMotionCon = player->rightMotion;
		if (rightMotionCon != nullptr)
		{
			FVector handLocation = rightMotionCon->GetComponentLocation();
			FVector direction = rightMotionCon->GetForwardVector() + rightMotionCon->GetUpVector() * -1;
			ballInstance->sphereComp->SetEnableGravity(true);
			ballInstance->sphereComp->AddImpulse(direction.GetSafeNormal() * power);
			bShootBall = true;
		}
	}
}

void UMoveComponent::ShowTrajectory()
{
	bIsShowLine = true;
}

// �������� �׸��� �Լ�(�ʿ��� ��: �÷��̾��� �� ��ġ, ���� ���� ����, ��, ���� �ð�, ���� Ƚ��)
void UMoveComponent::DrawTrajectory(FVector startLoc, FVector dir, float throwPower, float time, int32 term)
{
	float interval = time / (float)term;
	throwPoints.Empty();
	throwPoints.Add(startLoc);

	for (int32 i = 0; i < term; i++)
	{
		// p = p0 + vt - 0.5 * g * m * m * t * t
		float t = interval * i;
		float mass;

		if (ballInstance != nullptr)
		{
			mass = ballInstance->sphereComp->GetMass();
		}
		else
		{
			mass = 1.0f;
		}

		float gravity = 0.5f * GetWorld()->GetDefaultGravityZ() * mass * mass * t * t;
		FVector curLocation = startLoc + dir * throwPower * t + FVector(0, 0, gravity);

		// �� ���������� �浹 ���θ� üũ
		FHitResult hitInfo;
		FVector startVec = throwPoints[throwPoints.Num() - 1];

		if (GetWorld()->LineTraceSingleByChannel(hitInfo, startVec, curLocation, ECC_Visibility))
		{
			throwPoints.Add(hitInfo.ImpactPoint);
			break;
		}

		throwPoints.Add(curLocation);
	}

	if (throwPoints.Num() > 1)
	{
		for (int32 i = 0; i < throwPoints.Num() - 1; i++)
		{
			// DebugLine�� �̿��ؼ� �׸���
			DrawDebugLine(GetWorld(), throwPoints[i], throwPoints[i + 1], FColor::Red, false, 0, 0, 2);

			// NiagaraSystem�� �̿��ؼ� �׸���
			/*UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayVector(player->lineFX, FName("PointArray"), throwPoints);

			ringInstance->ringFX->SetVisibility(true);
			ringInstance->SetActorLocation(throwPoints[throwPoints.Num() - 1]);*/
		}
	}
}

void UMoveComponent::DrawBezierLine(UMotionControllerComponent* rightMotionComp)
{
	// 1. �Ʒ� �������� 45�� ������ ���� ����(searchDirection)�� �����.
	FVector searchDirection = (rightMotionComp->GetForwardVector() + rightMotionComp->GetUpVector() * 3) * -1;
	FVector handLocation = rightMotionComp->GetComponentLocation();

	// 2. searchDirection ������ �������� ���� Ʈ���̽��� �߻��Ѵ�.
	FHitResult hitInfo;
	FCollisionQueryParams param;
	param.AddIgnoredActor(player);

	bool bIsSearched = GetWorld()->LineTraceSingleByChannel(hitInfo, handLocation, handLocation + searchDirection * 2000.0f, ECC_Visibility, param);

	if (!bIsSearched)
	{
		return;
	}

	// 3. �ε��� ������ ���͸� ����(DestinationVec)�Ѵ�.
	FVector destinationVec = hitInfo.ImpactPoint;

	// 4. DestinationVec.Z �� ������ ��Ʈ�ѷ��� Z ���� �Ÿ��� 2�踸ŭ ���� ���͸� ����(MiddleVec)�Ѵ�.
	float distance = FMath::Abs(handLocation.Z - destinationVec.Z);
	FVector middleVec = destinationVec + FVector(0, 0, distance * 2);

	// 5. UBlueprintFunctionLibrary�� ���� DrawBezierCurve() �Լ��� ����Ͽ� ��� �� ���� ��ġ ���� �迭�� �޴´�.
	TArray<FVector> points = UMyVRFunctionLibrary::DrawBezierCurve(handLocation, middleVec, destinationVec, 50);

	// 6. ��� �� ������ �浹 ó�� �˻縦 �Ѵ�.
	throwPoints.Empty();
	throwPoints.Add(points[0]);

	for (int32 i = 0; i < points.Num() - 1; i++)
	{
		FHitResult lineCollide;
		if (GetWorld()->LineTraceSingleByChannel(lineCollide, points[i], points[i + 1], ECC_Visibility, param))
		{
			throwPoints.Add(lineCollide.ImpactPoint);
			break;
		}

		throwPoints.Add(points[i + 1]);
	}

	// 7. calcPoints �迭�� �� ������ ������ �մ´�.
	if (throwPoints.Num() > 1)
	{
		for (int32 i = 0; i < throwPoints.Num() - 1; i++)
		{
			//DrawDebugLine(GetWorld(), throwPoints[i], throwPoints[i + 1], FColor::Black, false, 0, 0, 1);

			// NiagaraSystem�� �̿��ؼ� �׸���
			/*UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayVector(player->lineFX, FName("PointArray"), throwPoints);

			ringInstance->ringFX->SetVisibility(true);
			ringInstance->SetActorLocation(throwPoints[throwPoints.Num() - 1]);*/
		}
	}
	//UE_LOG(LogTemp, Warning, TEXT("Points Array whole count: %d"), points.Num() - 1);
}

// ������ ������ �ڷ���Ʈ�ϴ� �Լ�
void UMoveComponent::TeleportToTarget()
{
	bIsShowLine = false;
	bezierTimeValue = 0;

	// ���� ����Ʈ�� ���� ���� ���� 0���� �ʱ�ȭ�Ѵ�.
	TArray<FVector> initVector;
	initVector.SetNum(2);

	UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayVector(player->lineFX, FName("PointArray"), initVector);


	float fadeTime = 1.0f;

	if (player != nullptr && throwPoints.Num() > 0)
	{
		// 0.5�ʵ��� ���̵� �� ȿ���� �ְ� �̵��Ѵ�.
		//player->GetController<APlayerController>()->ClientSetCameraFade(true, FColor::White, FVector2D(0, 1.0f), fadeTime);
		player->GetController<APlayerController>()->PlayerCameraManager->StartCameraFade(0, 1, fadeTime, FLinearColor::White);

		//FColor myColor1 = FColor(255, 255, 255, 255);
		//FLinearColor myColor2 = FColor(1, 1, 1, 1);

		FTimerHandle teleportTimer;
		GetWorld()->GetTimerManager().SetTimer(teleportTimer, FTimerDelegate::CreateLambda([&]() {
			player->SetActorLocation(throwPoints[throwPoints.Num() - 1]);
			//ringInstance->ringFX->SetVisibility(false);
			}), fadeTime, false);

	}
}



