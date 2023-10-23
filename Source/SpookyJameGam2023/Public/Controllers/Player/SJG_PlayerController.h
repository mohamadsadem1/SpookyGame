// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/PlayerController.h"
#include "SJG_PlayerController.generated.h"


class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class SPOOKYJAMEGAM2023_API ASJG_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ASJG_PlayerController();
	virtual void PlayerTick(float DeltaTime) override;


protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;



private:

	UPROPERTY(EditAnywhere, Category = "Input")
		TObjectPtr<UInputMappingContext> SJGContext;

	UPROPERTY(EditAnywhere, Category = "Input")
		TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
		TObjectPtr<UInputAction> PickUp;

	UPROPERTY(EditAnywhere, Category = "Input")
		TObjectPtr<UInputAction> UnequipRightHand;

	UPROPERTY(EditAnywhere, Category = "Input")
		TObjectPtr<UInputAction> UnequipLeftHand;

	UPROPERTY(EditAnywhere, Category = "Input")
		TObjectPtr<UInputAction> EnterRageMode;

	void Move(const struct  FInputActionValue& InputActionValue);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UInputAction> LookAction;

	void Look(const FInputActionValue& Value);

	void CallPickUp(const FInputActionValue& Value);
	void CallUnequipRightHand(const FInputActionValue& Value);
	void CallUnequipLeftHand(const FInputActionValue& Value);

	void CallEnteringTheRageMode(const FInputActionValue& Value);


};
