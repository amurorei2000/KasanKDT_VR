// Fill out your copyright notice in the Description page of Project Settings.


#include "MyVRFunctionLibrary.h"


// 곡선을 그리고 싶다.
// 공식이 필요하다. -> 베지어 곡선 공식
// p0 -> p1 까지 선을 그린다.
// p1 -> p2까지 선을 그린다.
// p0 ~ p1까지의 비율에 따른 점의 위치(m1)를 구한다. -> Lerp()
// p1 ~ p2까지의 비율에 따른 점의 위치(m2)를 구한다. -> Lerp()
// m1 ~ m2까지 선을 그린다.
// m1 ~ m2까지의 비율에 따른 점의 위치(b0)를 구한다.
// b0의 위치 값들을 배열에 저장한다.

TArray<FVector> UMyVRFunctionLibrary::DrawBezierCurve(FVector p0, FVector p1, FVector p2, float term)
{
	// 계산 값을 담을 배열 변수를 선언한다.
	TArray<FVector> Points;

	for (int32 i = 0; i < term; i++)
	{
		float interval = (float)i / term;
		FVector m0 = FMath::Lerp(p0, p1, interval);
		//DrawDebugLine(GetWorld(), p0, m0, FColor::Red, false, 0, 0, 1);

		FVector m1 = FMath::Lerp(p1, p2, interval);
		//DrawDebugLine(GetWorld(), p1, m1, FColor::Red, false, 0, 0, 1);

		//DrawDebugLine(GetWorld(), m0, m1, FColor::Green, false, 0, 0, 1);
		FVector b0 = FMath::Lerp(m0, m1, interval);
		Points.Add(b0);
	}

	// 계산된 곡선의 각 구간의 위치 값을 모아놓은 배열 Points 변수를 반환한다.
	return Points;
}
