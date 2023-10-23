// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SJG_Player_Character.h"

#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"



ASJG_Player_Character::ASJG_Player_Character()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Arm Comp");
	SpringArmComponent->SetupAttachment(RootComponent);  
	SpringArmComponent->bUsePawnControlRotation = true;  


	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);



	InteractionComp = CreateDefaultSubobject<USInteractComponent>(TEXT("InteractionComp"));


	InteractionCheckDistance = 500.f;
	InteractionCheckFrequency = 0.8f;
	bIsHoldingLeftWeapon = false;
	bIsHoldingRightWeapon = false;
	RagePercent = 90;
	RagePercentMax = 100;

	bAbleToEnterRageMode = false;
	RageModeState = ERageModeState::ERMS_NormalMode;
	bAbleToRecover = true;

}

void ASJG_Player_Character::BeginPlay()
{
	Super::BeginPlay();


		GetWorldTimerManager().SetTimer(IncreasingTimerHandle, this, &ASJG_Player_Character::IncreasingTheRagePercent, 1.f,bAbleToRecover==true);
	

}


void ASJG_Player_Character::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetWorld()->TimeSince(InteractionData.LastInteractionCheckTime) > InteractionCheckFrequency)
	{
		
			PrimaryInteract();

		// Update the last interaction check time
		InteractionData.LastInteractionCheckTime = GetWorld()->GetTimeSeconds();
	}

	
	CharacterSpeed = GetVelocity().Size();

}


void ASJG_Player_Character::PrimaryInteract()
{

	FCollisionObjectQueryParams ObjectQuerryParams;
	ObjectQuerryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();
	FVector Start;
	FVector EyeLocation;
	FRotator EyeRotation;

	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * 700);

	TArray<FHitResult>Hits;
	float Radius = 30.f;

	FCollisionShape Shape;
	Shape.SetSphere(Radius);

	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQuerryParams, Shape);
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : Hits)
	{
		if (AActor* HitActor = Hit.GetActor())
		{
			UE_LOG(LogTemp, Warning, TEXT("PerformInteractionCheck: Hit actor %s"), *HitActor->GetName());
			if (HitActor->GetClass()->ImplementsInterface(UIsACollectable::StaticClass()))
			{
				TObjectPtr<ACollectable> Collectable = Cast<ACollectable>(HitActor);

				SetCurrentInteractableCollectable(Collectable);
				
			
			}
			else
			{
				SetCurrentInteractableCollectable(nullptr);
			}
		}
	}

	DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.f, 0, 2.f);
}



void ASJG_Player_Character::Pickup(ASJG_Player_Character* PlayerCharacter)
{
	if (IsValid(GetCurrentInteractableCollectable()))
	{
		TObjectPtr<ACollectable> Collectable = CurrentInteractablecollectable;

		if (Collectable->GetCollectableState() == EWS_Pickup)
		{
			if (Collectable->CollectableType == ECollectableType::ECT_Weapon)
			{
				if (bIsHoldingRightWeapon == false)
				{
					Collectable->EquipRightHand(PlayerCharacter);
					UE_LOG(LogTemp, Warning, TEXT("Righthand"));

					SetRightEquippedCollectable(Collectable);
				}
				if (bIsHoldingRightWeapon == true)
				{

					GetrightCollectableHolded()->UnEquipRightHand(PlayerCharacter);
					if (bIsHoldingRightWeapon == false)
					{
						UE_LOG(LogTemp, Warning, TEXT("unequ"))

						Collectable->EquipRightHand(PlayerCharacter);
					}
				}
			}
			else if (Collectable->CollectableType == ECollectableType::ECT_Item)
			{
				if (bIsHoldingLeftWeapon == false)
				{
					Collectable->EquipLeftHand(PlayerCharacter);
					UE_LOG(LogTemp, Warning, TEXT("LeftHand"));

					SetLeftEquippedCollectable(Collectable);
				}

				Collectable->SetWeaponState(EWS_Equipped);
			}
		}
	}
}

void ASJG_Player_Character::UnequipRightHand(ASJG_Player_Character* PlayerCharacter)
{
	if(bIsHoldingRightWeapon)
	{
		GetrightCollectableHolded()->UnEquipRightHand(this);
	}
}
void ASJG_Player_Character::UnequipLeftHand(ASJG_Player_Character* PlayerCharacter)
{
	if(bIsHoldingLeftWeapon)
	{
		GetrightCollectableHolded()->UnEquipLeftHand(this);
	}
}



//===========================================================
//RAGE MODE RELATED
//===========================================================
void ASJG_Player_Character::EnteringRageMode(ASJG_Player_Character* PlayerCharacter)
{
	if (bAbleToEnterRageMode == true && RageModeState==ERageModeState::ERMS_NormalMode)
	{
		GetWorldTimerManager().ClearTimer(IncreasingTimerHandle);
		

		bAbleToEnterRageMode = false;
		
		RageModeState = ERageModeState::ERMS_InRageMode;

		UE_LOG(LogTemp, Warning, TEXT("EnteringRageMode function called"));

		TObjectPtr<UCharacterMovementComponent> CharacterMovementComponent = GetCharacterMovement();

		if (CharacterMovementComponent)
		{

			MaxCharacterSpeed= CharacterMovementComponent->MaxWalkSpeed *= 2.f;
		}
			GetWorldTimerManager().SetTimer(DecreasingTimerHandle, this, &ASJG_Player_Character::DecreasingTheRagePercent, 0.2f, true);
		
		
	}

	
}


void ASJG_Player_Character::ExitRageMode()
{
	GetWorldTimerManager().SetTimer(RecoverTimerHandle, this, &ASJG_Player_Character::RecoverMode, 10.f, false);
}




void ASJG_Player_Character::IncreasingTheRagePercent()
{
	if (bAbleToEnterRageMode == false)
	{
		if (RagePercent + 10 > RagePercentMax)
		{
			RagePercent = 100;

			bAbleToEnterRageMode = true;

			bAbleToRecover = false;

			RageModeState= ERageModeState::ERMS_NormalMode;

		}
		else
		{
			RagePercent += 10;
		}
	}
}

void ASJG_Player_Character::DecreasingTheRagePercent()
{
	if (RageModeState == ERageModeState::ERMS_InRageMode)
	{
		if (RagePercent - 10 < 0)
		{
			RagePercent = 0;

			

			ExhaustedMode();

		}
		else
		{
			RagePercent -= 10;
		}
	}

}


void ASJG_Player_Character::ExhaustedMode()
{
	SetRageModeState(ERageModeState::ERMS_ExhaustedMode);
	bAbleToRecover = false;

	TObjectPtr<UCharacterMovementComponent> CharacterMovementComponent = GetCharacterMovement();

	if (CharacterMovementComponent)
	{
		MaxCharacterSpeed=CharacterMovementComponent->MaxWalkSpeed /= 4.f;
	}
	GetWorldTimerManager().SetTimer(RecoverTimerHandle, this, &ASJG_Player_Character::RecoverMode, 10.f, false);
}

void ASJG_Player_Character::RecoverMode()
{
	bAbleToRecover = true;
	bAbleToEnterRageMode = false;
	RageModeState = ERageModeState::ERMS_RecoverMode;
	//IncreasingTheRagePercent();



	GetWorldTimerManager().SetTimer(IncreasingTimerHandle, this, &ASJG_Player_Character::IncreasingTheRagePercent, 1.f, true);
	TObjectPtr<UCharacterMovementComponent> CharacterMovementComponent = GetCharacterMovement();

	if (CharacterMovementComponent)
	{
		MaxCharacterSpeed=CharacterMovementComponent->MaxWalkSpeed *= 2.f;
	}

}

