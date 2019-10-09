// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBulletBase.h"

// Sets default values
AMyBulletBase::AMyBulletBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyBulletBase::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void AMyBulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyBulletBase::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
}

void AMyBulletBase::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
}

void AMyBulletBase::OnOverlapEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
}

void AMyBulletBase::LaunchBullet()
{
}

