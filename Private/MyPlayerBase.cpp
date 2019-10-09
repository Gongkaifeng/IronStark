// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerController.h"

AMyPlayerBase::AMyPlayerBase()
{
	// 1,设置任务人物胶囊体大小
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// 2,人物角度不使用
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;

	// 3,设置人物movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// 4,设置弹簧臂
	SpringArmCamera = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmCamera"));
	SpringArmCamera->SetupAttachment(RootComponent);
	SpringArmCamera->TargetArmLength = 350.0f;
	SpringArmCamera->bUsePawnControlRotation = true;

	// 5,设置人物跟随相机
	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(SpringArmCamera,USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// 6,变量初始化
	FireState = EMagicFireState::E_NONE;
	SkillState = ESkillState::E_SkillOne;

	Hp = 100.0f;

}

void AMyPlayerBase::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPlayerBase::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Skill01", IE_Pressed, this, &AMyPlayerBase::SetSkillStateOne);
	PlayerInputComponent->BindAction("Skill02", IE_Pressed, this, &AMyPlayerBase::SetSkillStateTwo);
	PlayerInputComponent->BindAction("Skill03", IE_Pressed, this, &AMyPlayerBase::SetSkillStateThree);
	PlayerInputComponent->BindAction("Skill04", IE_Pressed, this, &AMyPlayerBase::SetSkillStateFour);
	PlayerInputComponent->BindAction("Skill05", IE_Pressed, this, &AMyPlayerBase::SetSkillStateFive);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyPlayerBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyPlayerBase::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	
	
}

void AMyPlayerBase::MoveForward(float KeyWSValue)
{
	if ((Controller != NULL) && (KeyWSValue != 0.0f))
	{
		// 找到前进方向 1,右 2，上 3，前
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		// 获取前进向量
		const FVector Dir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Dir, KeyWSValue);
	}
}

void AMyPlayerBase::MoveRight(float KeyADValue)
{
	if ((Controller != NULL) && (KeyADValue != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
		
		const FVector Dir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Dir, KeyADValue);
	}
}

void AMyPlayerBase::MouseLeftButton()
{
}

void AMyPlayerBase::MouseLeftButtonReleased()
{
}

void AMyPlayerBase::SetSkillStateOne()
{
	SkillState = ESkillState::E_SkillOne;
}

void AMyPlayerBase::SetSkillStateTwo()
{
	SkillState = ESkillState::E_SkillTwo;
}

void AMyPlayerBase::SetSkillStateThree()
{
	SkillState = ESkillState::E_SkillThree;
}

void AMyPlayerBase::SetSkillStateFour()
{
	SkillState = ESkillState::E_SkillFour;
}

void AMyPlayerBase::SetSkillStateFive()
{
	SkillState = ESkillState::E_SkillFive;
}

bool AMyPlayerBase::GetSightRayHitLocation(FVector & OutHitLocation)
{
	int32 ViewportSizeX, ViewportSizeY;
	if (Controller)
	{
		Cast<APlayerController>(Controller)->GetViewportSize(ViewportSizeX, ViewportSizeY);// 获取屏幕长、宽
	}
	FVector2D ScreenLocation = FVector2D(ViewportSizeX* CrosshairXLocation, ViewportSizeY*CrosshairYLocation);

	FVector WorldLocation;			// 屏幕坐标转成世界坐标后的世界坐标
	FVector WorldDirection;			// 
	if (Cast<APlayerController>(Controller)->DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection))
	{
		GetLookVectorHitLocation(WorldDirection, OutHitLocation);
		return true;
	}
	return false;
}

bool AMyPlayerBase::GetLookVectorHitLocation(FVector LookDirection, FVector & OutHitLocation)
{
	FVector StartLocation = Cast<APlayerController>(Controller)->PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + LookDirection * LineTraceRange;

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		OutHitLocation = HitResult.Location;
		return true;
	}

	OutHitLocation = EndLocation;

	return false;
}
