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

	// ��ü�� �ٶ󺸰� ���� �� ������ �޽ð� ���� Ȯ��ȴ�.
	// ��ü�� �ٶ󺸰� ���� ���� �� ������ �޽ð� ���� ��ҵȴ�.
	// �ִ� �þ� �Ÿ�, �ִ� �ּ� ũ��, ������ �� �ִ� ������Ʈ Ÿ��

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
