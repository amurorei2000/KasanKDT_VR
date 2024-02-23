// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PianoActor.generated.h"

UCLASS()
class KDT_VR_API APianoActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APianoActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="MySettings|Sources")
	TArray<class USoundBase*> keySounds;

	UPROPERTY(EditAnywhere, Category = "MySettings|Sources")
	TSubclassOf<class AKeyboardActor> keyboardActor;

	UPROPERTY(EditAnywhere, Category = "MySettings|Sources")
	float keyboardTerm = 5.0f;

	UPROPERTY(EditAnywhere, Category = "MySettings|Components")
	class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = "MySettings|Components")
	TArray<class UChildActorComponent*> childKeys;

};
