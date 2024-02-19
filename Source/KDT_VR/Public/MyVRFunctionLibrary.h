// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyVRFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class KDT_VR_API UMyVRFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static TArray<FVector> DrawBezierCurve(FVector p0, FVector p1, FVector p2, float term);

};
