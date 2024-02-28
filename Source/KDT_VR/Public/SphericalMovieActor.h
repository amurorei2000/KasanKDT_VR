// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SphericalMovieActor.generated.h"

UCLASS()
class KDT_VR_API ASphericalMovieActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASphericalMovieActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category="MySettings")
	class UStaticMeshComponent* movieMesh;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UMediaPlayer* vrMediaPlayer;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UMediaSource* vrMediaSource;

};
