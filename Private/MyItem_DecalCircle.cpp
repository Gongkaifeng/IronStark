// Fill out your copyright notice in the Description page of Project Settings.

#include "MyItem_DecalCircle.h"

// Sets default values
AMyItem_DecalCircle::AMyItem_DecalCircle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 初始化龙卷风印花
	myDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("myDecal"));
	SetRootComponent(myDecal);
	// myDecal->bVisible = false;
	myDecal->SetRelativeScale3D(FVector(0.5f));
}

// Called when the game starts or when spawned
void AMyItem_DecalCircle::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void AMyItem_DecalCircle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

