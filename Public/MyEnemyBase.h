// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacterBase.h"
#include "MyEnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class SMALLWHITEWAR_API AMyEnemyBase : public AMyCharacterBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "Setup")
	float Hp = 100.0f;
};
