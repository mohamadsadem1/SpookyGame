// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPCS.generated.h"

UENUM(BlueprintType)
enum class EEnimyMovementStatus :uint8
{
	EMS_Idle				    UMETA(DisplayName = "Idle"),
	EMS_MoveToRandomLocation	UMETA(DisplayName = "MoveToRandomLocation"),
	EMS_MoveToSafeLocation		UMETA(DisplayName = "Attackking"),
	EMS_Dead					UMETA(DisplayName = "Dead"),

	EMS_Max						UMETA(DisplayName = "Default")

};

UCLASS()
class SPOOKYJAMEGAM2023_API ANPCS : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPCS();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		EEnimyMovementStatus EnimyMovementStatus;

	FORCEINLINE void SetEnimyMovementStatus(EEnimyMovementStatus  Status) { EnimyMovementStatus = Status; }

	FORCEINLINE EEnimyMovementStatus GetEnimyMovementStatus() { return EnimyMovementStatus; }

};
