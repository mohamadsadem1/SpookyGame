// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPCS.generated.h"

UENUM(BlueprintType)
enum class ENPCMovementState :uint8
{
	EMS_Idle				    UMETA(DisplayName = "Idle"),
	EMS_MoveToRandomLocation	UMETA(DisplayName = "MoveToRandomLocation"),
	EMS_MoveToSafeLocation		UMETA(DisplayName = "Attackking"),
	EMS_Dead					UMETA(DisplayName = "Dead"),

	EMS_Max						UMETA(DisplayName = "Default")

};

UENUM(BlueprintType)
enum class ENPCState :uint8
{
	EMS_Normal				    UMETA(DisplayName = "Normal"),
	EMS_Scary					UMETA(DisplayName = "Scary"),


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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		ENPCMovementState NPCMovementState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		ENPCState NPCState;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	UFUNCTION(BlueprintCallable, Category = "NPC|Movement")
	void SetNPCMovementState(ENPCMovementState  State) { NPCMovementState = State; }

	UFUNCTION(BlueprintCallable, Category = "NPC|Movement")
	ENPCMovementState GetNPCMovementState() { return NPCMovementState; }

	UFUNCTION(BlueprintCallable, Category = "NPC|State")
	void SetEnimyStatus(ENPCState  Status) { NPCState = Status; }

	UFUNCTION(BlueprintCallable, Category = "NPC|State")
	ENPCState GetNPCState() { return NPCState; }

};
