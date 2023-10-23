// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Collectables/Collectable.h"
#include "Actors/Intraction/SInteractComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/SJGCharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "SJG_Player_Character.generated.h"


USTRUCT()
struct FInteractionData
{
	GENERATED_BODY()

		FInteractionData() : CurrentInteractable(nullptr), LastInteractionCheckTime(0.f)
	{

	};

	UPROPERTY()
		AActor* CurrentInteractable;

	UPROPERTY()
		float LastInteractionCheckTime;


};

UENUM(BlueprintType)
enum class  ERageModeState:uint8
{
	ERMS_InRageMode		    UMETA(Display_Name = "InRageMode"),
	ERMS_RecoverMode	    UMETA(Display_Name = "RecoverMode"),
	ERMS_ExhaustedMode	    UMETA(Display_Name = "ExhaustedMode"),
	ERMS_NormalMode			UMETA(Display_Name = "NormalMode"),

	ERMS_Max				UMETA(Display_Name = "Max")
};

UENUM(BlueprintType)
enum class  EIsHoldingcollectable:uint8
{
	EMS_Holding UMETA(Display_Name = "Holding"),
	EMS_NoCollectable UMETA(Display_Name = "NoCollectable")
};




UCLASS()
class SPOOKYJAMEGAM2023_API ASJG_Player_Character : public ASJGCharacterBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	ASJG_Player_Character();

public:

	virtual void Tick(float DeltaSeconds) override;


	void PrimaryInteract();





protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USInteractComponent* InteractionComp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<USpringArmComponent> SpringArmComponent;

	FInteractionData InteractionData;

	TObjectPtr<ACollectable> RightCollectableHolded;

	TObjectPtr<ACollectable> LeftCollectableHolded;
	
	TObjectPtr<ACollectable> CurrentInteractablecollectable;

	TObjectPtr<ACollectable> InUseCollectable;



	
public:

	//===========================================================
	//INTERACTION SYSTEM RELATED
	//===========================================================
	float InteractionCheckFrequency;

	float InteractionCheckDistance;

	FTimerHandle TimerHandle_Interaction;

	FORCEINLINE bool IsInteracting() const { return GetWorldTimerManager().IsTimerActive(TimerHandle_Interaction); };


	//===========================================================
	//ANIMATIONS RELATED
	//===========================================================
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Animation")
	class UAnimMontage* PrimaryAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Animation")
	class UAnimMontage* DroppingBodyPartMon;



	//===========================================================
	//COLLECTABLES RELATED
	//===========================================================

	FORCEINLINE ACollectable* GetCurrentInteractableCollectable() { return CurrentInteractablecollectable; }
	FORCEINLINE void  SetCurrentInteractableCollectable(ACollectable* Collectable) { CurrentInteractablecollectable = Collectable; }

	void SetRightEquippedCollectable(ACollectable* Collectable) { RightCollectableHolded = Collectable; };

	
	FORCEINLINE ACollectable* GetrightCollectableHolded() { return RightCollectableHolded; }

	void SetLeftEquippedCollectable(ACollectable* Collectable) { LeftCollectableHolded = Collectable; }

	
	FORCEINLINE ACollectable* GetLeftCollectableHolded() { return LeftCollectableHolded; }




	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RageMode")
	bool bIsHoldingRightWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RageMode")
	bool bIsHoldingLeftWeapon;

	void Pickup(ASJG_Player_Character*PlayerCharacter);
	void UnequipRightHand(ASJG_Player_Character*PlayerCharacter);
	void UnequipLeftHand(ASJG_Player_Character*PlayerCharacter);




	//===========================================================
	//RAGE MODE RELATED
	//===========================================================
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RageMode")
		TEnumAsByte<ERageModeState> RageModeState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RageMode")
	float RagePercent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RageMode")
	float RagePercentMax;

	void IncreasingTheRagePercent();
	void DecreasingTheRagePercent();

	FTimerHandle DecreasingTimerHandle;
	FTimerHandle IncreasingTimerHandle;
	FTimerHandle RecoverTimerHandle;

	void EnteringRageMode(ASJG_Player_Character* PlayerCharacter);
	void ExitRageMode();
	void ExhaustedMode();
	void RecoverMode();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RageMode")
 	bool bAbleToEnterRageMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="RageMode")
	bool bAbleToRecover;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RageMode")
	float CharacterSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RageMode")
	float MaxCharacterSpeed;



	UFUNCTION()
		void SetRageModeState(ERageModeState RMS) { RageModeState = RMS; }


	

};
