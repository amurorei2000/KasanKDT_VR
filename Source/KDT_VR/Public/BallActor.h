// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallActor.generated.h"

UCLASS()
class KDT_VR_API ABallActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABallActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* sphereComp;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* meshComp;

};
