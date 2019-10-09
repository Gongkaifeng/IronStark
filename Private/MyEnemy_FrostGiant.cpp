// Fill out your copyright notice in the Description page of Project Settings.

#include "MyEnemy_FrostGiant.h"

AMyEnemy_FrostGiant::AMyEnemy_FrostGiant()
{

}

void AMyEnemy_FrostGiant::BeginPlay()
{
	Super::BeginPlay();

	Hp = 100.0f;
	FrostGiantState = EFrostGiantState::E_IDLE;
}

void AMyEnemy_FrostGiant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RandCount = FMath::RandHelper(3);
}

void AMyEnemy_FrostGiant::Atk(EFrostGiantState m_FrostGiantState)
{
	//AtkCombo(m_FrostGiantState);
	if (FPlatformTime::Seconds() - m_LastTime < m_AttCd) { return; }

	switch (RandCount)
	{
	case 0:
		AtkA(m_FrostGiantState);
		break;
	case 1:
		AtkC(m_FrostGiantState);
		break;
	case 2:
		AtkCombo(m_FrostGiantState);
		break;
	default:
		break;
	}

	/*switch (m_FrostGiantState)
	{
	case EFrostGiantState::E_NONE:
		break;
	case EFrostGiantState::E_IDLE:
		break;
	case EFrostGiantState::E_CHASE:
		break;
	case EFrostGiantState::E_AtkA:
	{
		AtkA(m_FrostGiantState);
	}
		break;
	case EFrostGiantState::E_AtkC:
	{
		AtkC(m_FrostGiantState);
	}
		break;
	case EFrostGiantState::E_AtkCombo:
	{
		AtkCombo(m_FrostGiantState);
	}
		break;
	default:
		break;
	}*/

	m_LastTime = FPlatformTime::Seconds();
}
