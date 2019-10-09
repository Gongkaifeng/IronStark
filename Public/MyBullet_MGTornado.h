// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBulletBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "MyEnemyBase.h"
#include "MyBullet_MGTornado.generated.h"

/**
 * 
 */
UCLASS()
class SMALLWHITEWAR_API AMyBullet_MGTornado : public AMyBulletBase
{
	GENERATED_BODY()
public:
	AMyBullet_MGTornado();
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	void OnHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		FVector NormalImpulse,
		const FHitResult& Hit) override;
	// 进入重叠
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult &SweepResult) override;
	// 离开重叠
	void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex) override;

	void LaunchBullet() override;
	void EndBullet();
	void Move(FVector);

public:
	UPROPERTY(VisibleAnywhere, Category = "Setup")
		UProjectileMovementComponent* BulletMovementComponent = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* CollisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent* BulletTornadoEffect = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
		TMap<FString, AMyEnemyBase*> EnemyMap;

	int32 TimeCount = 25;
};
