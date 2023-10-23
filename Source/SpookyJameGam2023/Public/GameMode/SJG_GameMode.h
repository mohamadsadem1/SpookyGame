// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SJG_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYJAMEGAM2023_API ASJG_GameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	ASJG_GameMode();


	virtual void BeginPlay() override;



};
