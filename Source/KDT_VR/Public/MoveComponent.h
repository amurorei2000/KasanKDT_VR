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

private:
	bool bIsShowLine = false;


	void ShowTrajectory();
	void DrawTrajectory(FVector startLoc, FVector dir, float throwPower, float time, int32 term);
	void TeleportToTarget();
};
