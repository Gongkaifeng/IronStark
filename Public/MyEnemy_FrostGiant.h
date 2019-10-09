// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyEnemyBase.h"
#include "MyPlayerBase.h"
#include "MyPlayer_Magic01.h"
#include "MyEnemy_FrostGiant.generated.h"

UENUM(BlueprintType)
enum class EFrostGiantState :uint8
{
	E_NONE,
	E_IDLE,
	E_CHASE,
	E_AtkA,
	E_AtkC,
	E_AtkCombo,
	E_DEAD,
};

UCLASS()
class SMALLWHITEWAR_API AMyEnemy_FrostGiant : public AMyEnemyBase
{
	GENERATED_BODY()
public:
	AMyEnemy_FrostGiant();
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Atk(EFrostGiantState m_FrostGiantState);

	// MagicFireBall技能函数(蓝图处理动画蒙太奇)
	UFUNCTION(BlueprintImplementableEvent, Category = "CallFunc")
		void AtkA(EFrostGiantState m_FrostGiantState);
	UFUNCTION(BlueprintImplementableEvent, Category = "CallFunc")
		void AtkC(EFrostGiantState m_FrostGiantState);
	UFUNCTION(BlueprintImplementableEvent, Category = "CallFunc")
		void AtkCombo(EFrostGiantState m_FrostGiantState);

public:
	UPROPERTY(BlueprintReadWrite, Category = "Setup")
		EFrostGiantState FrostGiantState;
	float m_LastTime;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float m_AttCd=2.0f;

	int RandCount;



};
