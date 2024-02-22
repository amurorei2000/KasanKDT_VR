// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KeyboardActor.generated.h"

UCLASS()
class KDT_VR_API AKeyboardActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AKeyboardActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category="MySettings")
	class UBoxComponent* boxComp;

	UPROPERTY(VisibleAnywhere, Category = "MySettings")
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class USoundBase* keySound;

private:
	class UMaterialInstanceDynamic* keyMat;

	UFUNCTION()
	void OnHitKey(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetOriginalColor();

};
