// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GazeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KDT_VR_API UGazeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGazeComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 물체를 바라보고 있을 때 게이즈 메시가 점차 확대된다.
	// 물체를 바라보고 있지 않을 때 게이즈 메시가 점차 축소된다.
	// 최대 시야 거리, 최대 최소 크기, 응시할 수 있는 오브젝트 타입

	UPROPERTY(EditAnywhere, Category="MySettings")
	float maxSight = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	float minSize = 0.01f;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	float maxSize = 0.3f;

private:
	class AVRPlayer* player;
	class UStaticMeshComponent* gazeMesh;
	float rate = 1.0f;

	bool CheckShowObjects();
};
