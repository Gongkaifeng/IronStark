// Fill out your copyright notice in the Description page of Project Settings.
#include "MyPlayer_Magic01.h"
#include "Components/InputComponent.h"
#include "EngineMinimal.h"

AMyPlayer_Magic01::AMyPlayer_Magic01()
{
	// 1,右手挂粒子 P_FireHand
	MagicRightEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MagicRightEffect"));
	MagicRightEffect->AttachToComponent(
		Cast<USceneComponent>(FindComponentByClass<USkeletalMeshComponent>()), 
		FAttachmentTransformRules(EAttachmentRule::KeepRelative,true),
		"magic_right_hand");								// 绑定到静态模型
	MagicRightEffect->bAutoActivate = true;					// 默认是播放粒子动画
	
	// 2,左手武器 SM_MagicWand
	MagicLeftWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MagicLeftWeapon"));
	MagicLeftWeapon->AttachToComponent(
		Cast<USceneComponent>(FindComponentByClass<USkeletalMeshComponent>()),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		"wand_use");										// 绑定到静态模型

	// 3，左手武器粒子 P_ArcaneHand  wand_use
	MagicLeftEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MagicLeftEffect"));
	MagicLeftEffect->AttachToComponent(
		Cast<USceneComponent>(FindComponentByClass<USkeletalMeshComponent>()),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		"wand_use");										// 绑定到静态模型
	MagicLeftEffect->bAutoActivate = true;					// 默认是播放粒子动画

	// 5,初始化龙卷风技能的技能显示位置圈
	myDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("myDecal"));
	myDecal->AttachToComponent(
		Cast<USceneComponent>(FindComponentByClass<USkeletalMeshComponent>()),
		FAttachmentTransformRules::KeepRelativeTransform);

	Hp = 100.0f;
}

void AMyPlayer_Magic01::BeginPlay()
{
	Super::BeginPlay();

	// 初始化龙卷风（注意：初始化之前BulletType_Fire=BP_AMyBullet_Tornado）
	myTornado = GetWorld()->SpawnActor<AMyBullet_MGTornado>(
		BulletType_Fire,
		GetActorLocation()+FVector(200.0f,0.f,0.f),
		FRotator(0.0f));

	myDecal->SetVisibility(false);
}

void AMyPlayer_Magic01::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FireState == EMagicFireState::E_FireTonadoLoop)
	{
		// 1,玩家Yaw值跟着相机Yaw值
		FRotator CameraRotation = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation();
		SetActorRotation(FRotator(GetActorRotation().Roll, CameraRotation.Yaw, GetActorRotation().Pitch));
		// 2,龙卷风位置跟着碰撞点
		GetSightRayHitLocation(HitLocation);
		myTornado->Move(HitLocation);
		// 3,Decal跟着十字叉走
		myDecal->SetVisibility(true);
		myDecal->SetWorldLocation(HitLocation);
	}
	if (FireState == EMagicFireState::E_FireTonadoEnd)
	{
		myDecal->SetVisibility(false);
	}
}

void AMyPlayer_Magic01::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Magic技能按键回调（给Magic复写）
	PlayerInputComponent->BindAction("FireBall", IE_Pressed, this, &AMyPlayer_Magic01::MouseLeftButton);
	PlayerInputComponent->BindAction("FireBall", IE_Released, this, &AMyPlayer_Magic01::MouseLeftButtonReleased);

}

void AMyPlayer_Magic01::MouseLeftButton()
{
	FRotator CameraRotation = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation();
	SetActorRotation(FRotator(GetActorRotation().Roll, CameraRotation.Yaw, GetActorRotation().Pitch));
	MagicFireBall(FireState);
}

void AMyPlayer_Magic01::MouseLeftButtonReleased()
{
	if (SkillState == ESkillState::E_SkillTwo)
	{
		if (FireState == EMagicFireState::E_FireTonadoStart || FireState == EMagicFireState::E_FireTonadoLoop)
		{
			FireState = EMagicFireState::E_FireTonadoEnd;
			myTornado->EndBullet();
			MagicFireBallEnd(FireState);
		}
	}
}

void AMyPlayer_Magic01::FireBall()
{
	switch (SkillState)
	{
	case ESkillState::E_SkillOne:
	{
		Skill01_FireBall();
	}
		break;
	case ESkillState::E_SkillTwo:
	{
		Skill02_Tornado();
	}
		break;
	case ESkillState::E_SkillThree:
	{
		Skill03_Healing();
	}
		break;
	case ESkillState::E_SkillFour:
		break;
	case ESkillState::E_SkillFive:
		break;
	default:
		break;
	}
}

void AMyPlayer_Magic01::Skill01_FireBall()
{
	if (!GetWorld())
		return;
	// APlayerCameraManager* CurrentCamera = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FRotator CameraRotation = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation();
	SetActorRotation(FRotator(GetActorRotation().Roll, CameraRotation.Yaw, GetActorRotation().Pitch));
	AMyBullet_MGFireBall* pBulletFireBall = nullptr;
	// UE_LOG(LogTemp, Display, TEXT("EMagicFireState::E_FireBallOne "));


	if (FireState == EMagicFireState::E_FireBallOne || FireState == EMagicFireState::E_FireBallThree)
	{
		// 计算子弹路径方向
		GetSightRayHitLocation(HitLocation);
		FVector PosStart = Cast<USceneComponent>(this->FindComponentByClass<USkeletalMeshComponent>())->GetSocketLocation(FName("magic_right_hand")) + GetActorForwardVector() * 50;
		FVector RightDir = HitLocation - PosStart;
		RightDir.Normalize();
		FRotator RightRotator = RightDir.Rotation();

		pBulletFireBall = GetWorld()->SpawnActor<AMyBullet_MGFireBall>(
			BulletType_Fire,
			Cast<USceneComponent>(this->FindComponentByClass<USkeletalMeshComponent>())->GetSocketLocation(FName("magic_right_hand")) + GetActorForwardVector() * 50,
			//FRotator(GetActorRotation().Pitch, CameraRotation.Yaw, GetActorRotation().Roll));
			RightRotator);
	}
	else if (FireState == EMagicFireState::E_FireBallTwo)
	{
		// 计算子弹路径方向
		GetSightRayHitLocation(HitLocation);
		FVector PosStart = Cast<USceneComponent>(this->FindComponentByClass<USkeletalMeshComponent>())->GetSocketLocation(FName("magic_left_hand")) + GetActorForwardVector() * 50;
		FVector LeftDir = HitLocation - PosStart;
		LeftDir.Normalize();
		FRotator LeftRotator = LeftDir.Rotation();

		pBulletFireBall = GetWorld()->SpawnActor<AMyBullet_MGFireBall>(
			BulletType_Fire,
			Cast<USceneComponent>(this->FindComponentByClass<USkeletalMeshComponent>())->GetSocketLocation(FName("magic_left_hand")) + GetActorForwardVector() * 50,
			// FRotator(GetActorRotation().Pitch, CameraRotation.Yaw, GetActorRotation().Roll));
			LeftRotator);
	}

	if (pBulletFireBall)
		pBulletFireBall->LaunchBullet();
}

void AMyPlayer_Magic01::Skill02_Tornado()
{
	if (myTornado)
	{
		GetSightRayHitLocation(HitLocation);
		myTornado->SetActorLocation(HitLocation);
		myTornado->LaunchBullet();
	}
}

void AMyPlayer_Magic01::Skill03_Healing()
{
}
