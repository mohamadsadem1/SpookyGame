// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/Player/SJG_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Character/SJG_Player_Character.h"

class ASJG_Player_Character;

ASJG_PlayerController::ASJG_PlayerController()
{
}

void ASJG_PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void ASJG_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(SJGContext);
	APawn* PlayerPawn = GetPawn();

	if (PlayerPawn)
	{
		// Your existing code

		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(SJGContext, 0);
		}
	}
}

void ASJG_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASJG_PlayerController::Move);

	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASJG_PlayerController::Look);

	EnhancedInputComponent->BindAction(PickUp, ETriggerEvent::Triggered, this, &ASJG_PlayerController::CallPickUp);

	EnhancedInputComponent->BindAction(UnequipRightHand, ETriggerEvent::Triggered, this, &ASJG_PlayerController::CallUnequipRightHand);
	EnhancedInputComponent->BindAction(UnequipLeftHand, ETriggerEvent::Triggered, this, &ASJG_PlayerController::CallUnequipLeftHand);

	EnhancedInputComponent->BindAction(EnterRageMode, ETriggerEvent::Triggered, this, &ASJG_PlayerController::CallEnteringTheRageMode);
	EnhancedInputComponent->BindAction(PrimaryAttack, ETriggerEvent::Triggered, this, &ASJG_PlayerController::CallPrimaryAttack);

}


void ASJG_PlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);

	}
}

void ASJG_PlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		// add yaw and pitch input to controller
		ControlledPawn->AddControllerYawInput(LookAxisVector.X);
		ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);


	}

}

void ASJG_PlayerController::CallPickUp(const FInputActionValue& Value)
{
	ASJG_Player_Character* PlayerCharacter = Cast<ASJG_Player_Character>(GetPawn());
	PlayerCharacter->Pickup(PlayerCharacter);

}

void ASJG_PlayerController::CallUnequipRightHand(const FInputActionValue& Value)
{
	ASJG_Player_Character* PlayerCharacter = Cast<ASJG_Player_Character>(GetPawn());
	PlayerCharacter->UnequipRightHand();
}

void ASJG_PlayerController::CallUnequipLeftHand(const FInputActionValue& Value)
{
	ASJG_Player_Character* PlayerCharacter = Cast<ASJG_Player_Character>(GetPawn());
	PlayerCharacter->UnequipLeftHand();
}

void ASJG_PlayerController::CallEnteringTheRageMode(const FInputActionValue& Value)
{
	ASJG_Player_Character* PlayerCharacter = Cast<ASJG_Player_Character>(GetPawn());
	PlayerCharacter->EnteringRageMode();
}

void ASJG_PlayerController::CallPrimaryAttack(const FInputActionValue& Value)
{
	ASJG_Player_Character* PlayerCharacter = Cast<ASJG_Player_Character>(GetPawn());
	PlayerCharacter->PrimaryAttack();
}
