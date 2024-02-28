// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WidgetMovieActor.generated.h"

UCLASS()
class KDT_VR_API AWidgetMovieActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AWidgetMovieActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "MySettings|Components")
	class USceneComponent* rootComp;

	UPROPERTY(VisibleAnywhere, Category="MySettings|Components")
	class UWidgetComponent* movieWidgetComp;
};
