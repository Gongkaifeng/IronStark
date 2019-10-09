// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "MyPlayerBase.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MyBulletBase.h"
#include "MyBullet_MGFireBall.h"
#include "MyBullet_MGTornado.h"
#include "MyItem_DecalCircle.h"
#include "Components/DecalComponent.h"
#include "MyPlayer_Magic01.generated.h"

UCLASS()
class SMALLWHITEWAR_API AMyPlayer_Magic01 : public AMyPlayerBase
{
	GENERATED_BODY()
public:
	AMyPlayer_Magic01();
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	// 按键绑定
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// 鼠标左键回调
	void MouseLeftButton() override;
	void MouseLeftButtonReleased() override;

	// MagicFireBall技能函数(蓝图处理动画蒙太奇)
	UFUNCTION(BlueprintImplementableEvent, Category = "CallFunc")
		void MagicFireBall(EMagicFireState m_FireBallState);
	UFUNCTION(BlueprintImplementableEvent, Category = "CallFunc")
		void MagicFireBallEnd(EMagicFireState m_FireBallState);


	// C++处理技能逻辑
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void FireBall();

	UFUNCTION(BlueprintCallable, Category = "Setup")	// 1技能火球
		void Skill01_FireBall();
	UFUNCTION(BlueprintCallable, Category = "Setup")	// 2技能龙卷风
		void Skill02_Tornado();
	UFUNCTION(BlueprintCallable, Category = "Setup")	// 3技能加血Buff
		void Skill03_Healing();

public:
	// 左右手粒子、武器
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ParticleEmitter")
		UParticleSystemComponent* MagicRightEffect;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
		UStaticMeshComponent* MagicLeftWeapon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ParticleEmitter")
		UParticleSystemComponent* MagicLeftEffect;

	
	// 2技能龙卷风
	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		AMyBullet_MGTornado* myTornado = nullptr;

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		UDecalComponent* myDecal = nullptr;
};