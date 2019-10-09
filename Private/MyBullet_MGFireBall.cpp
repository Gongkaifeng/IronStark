// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBullet_MGFireBall.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayerBase.h"
AMyBullet_MGFireBall::AMyBullet_MGFireBall()
{
	PrimaryActorTick.bCanEverTick = true;
	// 1,��ʼ��ProjectileMovement���
	BulletMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Bullet"));
	BulletMovementComponent->bAutoActivate = true;

	// 2,��ʼ����ײ��
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>("CollisionMesh");
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);			// ���ø�����ײΪtrue
	//CollisionMesh->SetVisibility(true);						// ����Ϊ�ɼ�

	// 3,��ʼ��������Ч
	BulletFireBallEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BulletFireBallEffect"));
	BulletFireBallEffect->AttachTo(RootComponent);
	BulletFireBallEffect->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f));
	BulletFireBallEffect->SetAutoActivate(false);
	
	// 4,�ӵ���ײ������Ч
	BulletCollisionEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BulletCollisionEffect"));
	BulletCollisionEffect->AttachTo(RootComponent);
	BulletCollisionEffect->SetActive(false);

}

void AMyBullet_MGFireBall::BeginPlay()
{
	Super::BeginPlay();

	CollisionMesh->OnComponentHit.AddUniqueDynamic(this, &AMyBullet_MGFireBall::OnHit);
}

void AMyBullet_MGFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyBullet_MGFireBall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("AMyBullet_MGFireBall::OnHit!!!!!!!!!!"));
	AMyPlayerBase* Owner =Cast<AMyPlayerBase>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (Owner)
	{
		AMyPlayerBase* OtherOwner = Cast<AMyPlayerBase>(OtherActor);
		if (OtherOwner && OtherOwner == Owner)
		{
			//CollisionMesh->SetNotifyRigidBodyCollision(false);
			return;
		}
		else
		{
			//SetRootComponent(BulletFireBallEffect);
			BulletFireBallEffect->SetActive(false);
			CollisionMesh->DestroyComponent();			
		}
	}
	BulletCollisionEffect->SetActive(true);

	AMyEnemy_FrostGiant* HitEnemy = Cast<AMyEnemy_FrostGiant>(OtherActor);
	if (HitEnemy)
	{
		HitEnemy->Hp -= 5.0f;
	}
}

void AMyBullet_MGFireBall::LaunchBullet()
{
	if (BulletMovementComponent == nullptr || BulletFireBallEffect == nullptr)
		return;

	BulletMovementComponent->InitialSpeed = 500.0f;
	//BulletMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector*10.0f);
	BulletMovementComponent->Activate();
}
