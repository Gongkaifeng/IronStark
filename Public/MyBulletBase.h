// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBulletBase.generated.h"

UCLASS()
class SMALLWHITEWAR_API AMyBulletBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyBulletBase();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;	

	UFUNCTION()						// ���������ײֻ����һ��
	virtual void OnHit(
			UPrimitiveComponent* HitComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComponent,
			FVector NormalImpulse,
			const FHitResult& Hit);

	UFUNCTION()						// ��������������ʱ����
	virtual	void OnOverlapBegin(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep, 
			const FHitResult &SweepResult);

	UFUNCTION()						// �����뿪�������ʱ����
	virtual	void OnOverlapEnd(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	UFUNCTION()
	virtual void LaunchBullet();

};
