// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBullet_MGTornado.h"


AMyBullet_MGTornado::AMyBullet_MGTornado()
{
	PrimaryActorTick.bCanEverTick = true;

	// 1,初始化ProjectileMovement组件
	BulletMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Tornado"));
	BulletMovementComponent->bAutoActivate = false;

	// 2,初始化StaticMeshComponent
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>("CollisionMesh");
	SetRootComponent(CollisionMesh);
	// CollisionMesh->bVisible = false;
	// CollisionMesh->SetNotifyRigidBodyCollision(false);

	// CollisionMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// CollisionMesh->SetHiddenInGame(true);

	// 3,初始化粒子特效
	BulletTornadoEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName("TornadoEffect"));
	BulletTornadoEffect->AttachTo(RootComponent);
	// BulletTornadoEffect->SetAutoActivate(false);
	// BulletTornadoEffect->SetHiddenInGame(true);
}

void AMyBullet_MGTornado::BeginPlay()
{
	Super::BeginPlay();

	CollisionMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CollisionMesh->SetHiddenInGame(true);
	BulletTornadoEffect->SetAutoActivate(false);
	BulletTornadoEffect->SetHiddenInGame(true);

	CollisionMesh->OnComponentHit.AddUniqueDynamic(this, &AMyBullet_MGTornado::OnHit);
	CollisionMesh->OnComponentBeginOverlap.AddUniqueDynamic(this, &AMyBullet_MGTornado::OnOverlapBegin);
	CollisionMesh->OnComponentEndOverlap.AddUniqueDynamic(this, &AMyBullet_MGTornado::OnOverlapEnd);
}

void AMyBullet_MGTornado::Tick(float DeltaTime)
{
	if (TimeCount < 25)	
		TimeCount++;
	
	if (EnemyMap.GetAllocatedSize() != 0 && TimeCount == 25)
	{
		for (auto& elemt : EnemyMap)
		{
			elemt.Value->Hp -= 5.0f;
			UE_LOG(LogTemp, Warning, TEXT("AMyBullet_MGTornado::Tick-Hp!!!!!!!!!!"));
		}
		TimeCount = 0;
	}
}

void AMyBullet_MGTornado::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	// UE_LOG(LogTemp, Warning, TEXT("AMyBullet_MGTornado::OnHit!!!!!!!!!!"));
}

void AMyBullet_MGTornado::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent,AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("AMyBullet_MGTornado::OnOverlapBegin!!!!!!!!!!"));
	AMyEnemyBase* TempEnemy = Cast<AMyEnemyBase>(OtherActor);
	if (TempEnemy)
	{
		EnemyMap.Emplace((TempEnemy->GetName()), TempEnemy);
		
	}
}

void AMyBullet_MGTornado::OnOverlapEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("AMyBullet_MGTornado::OnOverlapEnd!!!!!!!!!!"));
	AMyEnemyBase* TempEnemy = Cast<AMyEnemyBase>(OtherActor);
	if (TempEnemy)
	{
		EnemyMap.Remove(TempEnemy->GetName());
		
	}
}

void AMyBullet_MGTornado::LaunchBullet()
{
	// CollisionMesh->bVisible = true;
	// CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionMesh->SetHiddenInGame(false);

	BulletTornadoEffect->SetAutoActivate(true);
	BulletTornadoEffect->SetHiddenInGame(false);
}

void AMyBullet_MGTornado::EndBullet()
{
	CollisionMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CollisionMesh->SetHiddenInGame(true);
	BulletTornadoEffect->SetAutoActivate(false);
	BulletTornadoEffect->SetHiddenInGame(true);
}

void AMyBullet_MGTornado::Move(FVector _Vec)
{
	FVector _Temp = (_Vec - GetActorLocation());
	_Temp.Normalize();
	FVector temp2 = FVector(_Temp.X, _Temp.Y, 0.0f);
	SetActorLocation(FVector(GetActorLocation() + temp2 * 3.0f));
}
