// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerController.h"

AMyPlayerBase::AMyPlayerBase()
{
	// 1,�����������ｺ�����С
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// 2,����ǶȲ�ʹ��
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;

	// 3,��������movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// 4,���õ��ɱ�
	SpringArmCamera = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmCamera"));
	SpringArmCamera->SetupAttachment(RootComponent);
	SpringArmCamera->TargetArmLength = 350.0f;
	SpringArmCamera->bUsePawnControlRotation = true;

	// 5,��������������
	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(SpringArmCamera,USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// 6,������ʼ��
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
		// �ҵ�ǰ������ 1,�� 2���� 3��ǰ
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		// ��ȡǰ������
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
		Cast<APlayerController>(Controller)->GetViewportSize(ViewportSizeX, ViewportSizeY);// ��ȡ��Ļ������
	}
	FVector2D ScreenLocation = FVector2D(ViewportSizeX* CrosshairXLocation, ViewportSizeY*CrosshairYLocation);

	FVector WorldLocation;			// ��Ļ����ת��������������������
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
