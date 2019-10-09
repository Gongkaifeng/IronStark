// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MyBulletBase.h"
#include "MyPlayerBase.generated.h"

UENUM(BlueprintType)					// 魔法师技能状态枚举
enum class EMagicFireState :uint8		// 设置uint8类型
{
	E_NONE,
	E_FireBallOne UMETA(DisplayName = "普攻1段"),
	E_FireBallOne_latter UMETA(DisplayName = "普攻1段后"),
	E_FireBallTwo UMETA(DisplayName = "普攻2段"),
	E_FireBallTwo_latter UMETA(DisplayName = "普攻2段后"),
	E_FireBallThree UMETA(DisplayName = "普攻3段"),
	E_FireBallThree_latter UMETA(DisplayName = "普攻3段后"),
	E_FireTonadoStart UMETA(DisplayName = "龙卷风前摇"),
	E_FireTonadoLoop UMETA(DisplayName = "龙卷风重复"),
	E_FireTonadoEnd UMETA(DisplayName = "龙卷风后摇"),
};

UENUM(BlueprintType)
enum class ESkillState :uint8
{
	E_SkillOne,
	E_SkillTwo,
	E_SkillThree,
	E_SkillFour,
	E_SkillFive,
};

UCLASS()
class SMALLWHITEWAR_API AMyPlayerBase : public AMyCharacterBase
{
	GENERATED_BODY()

public:
	// 构造函数
	AMyPlayerBase();
	virtual void BeginPlay() override;
	// 按键绑定
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// 人物前后移动
	void MoveForward(float KeyWSValue);
	// 人物左右移动
	void MoveRight(float KeyADValue);
	// 鼠标左键回调(各自英雄各自复写)
	virtual void MouseLeftButton();
	virtual void MouseLeftButtonReleased();

	UFUNCTION()
		bool GetSightRayHitLocation(FVector &OutHitLocation);
	UFUNCTION()
		bool GetLookVectorHitLocation(FVector LookDirection, FVector &OutHitLocation);

	void SetSkillStateOne();
	void SetSkillStateTwo();
	void SetSkillStateThree();
	void SetSkillStateFour();
	void SetSkillStateFive();

public:
	// 相机弹簧臂和相机
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArmCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FollowCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		EMagicFireState FireState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
		ESkillState SkillState;


	FVector HitLocation;
	float CrosshairXLocation = 0.5f;
	float CrosshairYLocation = 0.4f;
	UPROPERTY(EditAnywhere)
		float LineTraceRange = 10000000.0f;

	// 1技能的状态
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		TSubclassOf<AMyBulletBase> BulletType_Fire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		float Hp;
};