// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoveComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class KDT_VR_API UMoveComponent : public UActorComponent
{
	GENERATED_BODY()



public:
	UMoveComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupPlayerInputComponent(class UEnhancedInputComponent* PlayerInputComponent, TArray<class UInputAction*> inputs);

	UPROPERTY(EditAnywhere, Category="MySettings")
	float power = 300.0f;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	float throwTime = 5.0f;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	int32 throwTerm = 50;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	TSubclassOf<class ATeleportRingActor> ringActor;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	TSubclassOf<class ABallActor> ballActor;
	
private:
	bool bIsShowLine = false;
	class AVRPlayer* player;
	TArray<FVector> throwPoints;
	class ATeleportRingActor* ringInstance;
	class ABallActor* ballInstance;
	bool bShootBall = false;
	float bezierTimeValue = 0;
	TArray<FVector> bPoints;
	bool bElapsedTime = true;

	void ShootBall();
	void ShowTrajectory();
	void DrawTrajectory(FVector startLoc, FVector dir, float throwPower, float time, int32 term);
	void DrawBezierCurve(FVector p0, FVector p1, FVector p2, float term);
	void TeleportToTarget();
};
