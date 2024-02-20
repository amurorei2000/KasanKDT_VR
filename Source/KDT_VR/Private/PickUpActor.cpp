// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"


APickUpActor::APickUpActor()
{
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComp);
	//boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	boxComp->SetCollisionProfileName(FName("PickUpActor"));
	boxComp->SetBoxExtent(FVector(50));
	boxComp->SetWorldScale3D(FVector(0.1f, 0.1f, 0.4f));
	boxComp->SetSimulatePhysics(true);
	boxComp->SetEnableGravity(true);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	meshComp->SetRelativeLocation(FVector(0, 0, -50));

}

void APickUpActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickUpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 자기 자신을 handMeshComp에 부착시키는 함수
void APickUpActor::OnGrabbed(USkeletalMeshComponent* handMeshComp)
{
	boxComp->SetSimulatePhysics(false);
	
	// 1. 잡을 당시의 간격 위치 값(월드 좌표 기준)을 그대로 유지하면서 붙이도록 설정한다.
	FAttachmentTransformRules attachRules = FAttachmentTransformRules::KeepWorldTransform;
	AttachToComponent(handMeshComp, attachRules);

	// 2. 손 메시의 소켓 위치에 맞춰서 자신을 부착한다.
	/*FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

	AttachToComponent(handMeshComp, attachRules, FName("GrabPoint"));
	SetActorRelativeLocation(offsetLocation);
	SetActorRelativeRotation(offsetRotation);*/
}

