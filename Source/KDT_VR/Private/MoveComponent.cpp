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

	// 텔레포트 타겟 지점에 표시할 링 이펙트를 생성 후 비활성화한다.
	//ringInstance = GetWorld()->SpawnActor<ATeleportRingActor>(ringActor, player->GetActorLocation(), player->GetActorRotation());
	//ringInstance->ringFX->SetVisibility(false);

	// 물리 비교용 공 액터 생성하기
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

			// 물리 예측선 방식으로 그린다.
			DrawTrajectory(handLocation, direction.GetSafeNormal(), power, throwTime, throwTerm);

			// 베지어 곡선 방식으로 그린다.
			//DrawBezierLine(rightMotionCon);
		}
	}

	// 공을 발사하기 전에 오른 손을 쫓아다니도록 처리하기
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

// 예측선을 그리는 함수(필요한 것: 플레이어의 손 위치, 던질 방향 벡터, 힘, 예측 시간, 예측 횟수)
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

		// 각 구간마다의 충돌 여부를 체크
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
			// DebugLine을 이용해서 그리기
			DrawDebugLine(GetWorld(), throwPoints[i], throwPoints[i + 1], FColor::Red, false, 0, 0, 2);

			// NiagaraSystem을 이용해서 그리기
			/*UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayVector(player->lineFX, FName("PointArray"), throwPoints);

			ringInstance->ringFX->SetVisibility(true);
			ringInstance->SetActorLocation(throwPoints[throwPoints.Num() - 1]);*/
		}
	}
}

void UMoveComponent::DrawBezierLine(UMotionControllerComponent* rightMotionComp)
{
	// 1. 아래 방향으로 45도 각도로 방향 벡터(searchDirection)를 만든다.
	FVector searchDirection = (rightMotionComp->GetForwardVector() + rightMotionComp->GetUpVector() * 3) * -1;
	FVector handLocation = rightMotionComp->GetComponentLocation();

	// 2. searchDirection 벡터의 방향으로 라인 트레이스를 발사한다.
	FHitResult hitInfo;
	FCollisionQueryParams param;
	param.AddIgnoredActor(player);

	bool bIsSearched = GetWorld()->LineTraceSingleByChannel(hitInfo, handLocation, handLocation + searchDirection * 2000.0f, ECC_Visibility, param);

	if (!bIsSearched)
	{
		return;
	}

	// 3. 부딪힌 지점의 벡터를 저장(DestinationVec)한다.
	FVector destinationVec = hitInfo.ImpactPoint;

	// 4. DestinationVec.Z 과 오른손 콘트롤러의 Z 값의 거리의 2배만큼 높인 벡터를 저장(MiddleVec)한다.
	float distance = FMath::Abs(handLocation.Z - destinationVec.Z);
	FVector middleVec = destinationVec + FVector(0, 0, distance * 2);

	// 5. UBlueprintFunctionLibrary로 만든 DrawBezierCurve() 함수를 사용하여 곡선의 각 구간 위치 값을 배열로 받는다.
	TArray<FVector> points = UMyVRFunctionLibrary::DrawBezierCurve(handLocation, middleVec, destinationVec, 50);

	// 6. 곡선의 각 구간별 충돌 처리 검사를 한다.
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

	// 7. calcPoints 배열의 각 구간을 선으로 잇는다.
	if (throwPoints.Num() > 1)
	{
		for (int32 i = 0; i < throwPoints.Num() - 1; i++)
		{
			//DrawDebugLine(GetWorld(), throwPoints[i], throwPoints[i + 1], FColor::Black, false, 0, 0, 1);

			// NiagaraSystem을 이용해서 그리기
			/*UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayVector(player->lineFX, FName("PointArray"), throwPoints);

			ringInstance->ringFX->SetVisibility(true);
			ringInstance->SetActorLocation(throwPoints[throwPoints.Num() - 1]);*/
		}
	}
	//UE_LOG(LogTemp, Warning, TEXT("Points Array whole count: %d"), points.Num() - 1);
}

// 지정된 곳으로 텔레포트하는 함수
void UMoveComponent::TeleportToTarget()
{
	bIsShowLine = false;
	bezierTimeValue = 0;

	// 라인 이펙트의 구간 벡터 값을 0으로 초기화한다.
	TArray<FVector> initVector;
	initVector.SetNum(2);

	UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayVector(player->lineFX, FName("PointArray"), initVector);


	float fadeTime = 1.0f;

	if (player != nullptr && throwPoints.Num() > 0)
	{
		// 0.5초동안 페이드 인 효과를 주고 이동한다.
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



