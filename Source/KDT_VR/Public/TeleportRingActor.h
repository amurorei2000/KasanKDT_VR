// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeleportRingActor.generated.h"

UCLASS()
class KDT_VR_API ATeleportRingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ATeleportRingActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* rootComp;

	UPROPERTY(VisibleAnywhere)
	class UNiagaraComponent* ringFX;
};
