// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBulletBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "MyEnemy_FrostGiant.h"
#include "MyBullet_MGFireBall.generated.h"

UCLASS()
class SMALLWHITEWAR_API AMyBullet_MGFireBall : public AMyBulletBase
{
	GENERATED_BODY()

public:
	AMyBullet_MGFireBall();
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	void OnHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		FVector NormalImpulse,
		const FHitResult& Hit) override;
	
	void LaunchBullet() override;

public:
	UPROPERTY(VisibleAnywhere, Category = "Setup")
		UProjectileMovementComponent* BulletMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* CollisionMesh = nullptr;					// 碰撞体

	UPROPERTY(VisibleAnywhere, Category = "ParticleEmitter")
		UParticleSystemComponent* BulletFireBallEffect = nullptr;		// 子弹粒子特效

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ParticleEmitter")
		UParticleSystemComponent* BulletCollisionEffect;
};
