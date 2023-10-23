// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SafeLocation.generated.h"

UCLASS()
class SPOOKYJAMEGAM2023_API ASafeLocation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASafeLocation();

public:
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		TArray<FVector >Locations;



};
