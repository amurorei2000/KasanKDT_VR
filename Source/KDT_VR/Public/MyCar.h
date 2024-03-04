// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyCar.generated.h"

UCLASS()
class KDT_VR_API AMyCar : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyCar();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "MySettings")
	class UBoxComponent* boxComp;

	UPROPERTY(VisibleAnywhere, Category = "MySettings")
	class UStaticMeshComponent* meshComp;

	void Move(FVector moveDirection);
	void Rotate(float degree);
};
