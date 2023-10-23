// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IsACollectable.generated.h"

UENUM()
enum class EInteractableType : uint8
{
	PickUp				 UMETA(DisplayName = "PickUp"),
	NonPlayerCharacter	 UMETA(DisplayName = "NonPlayerCharacter"),
	Device				 UMETA(DisplayName = "Device"),
	Toggle				 UMETA(DisplayName = "Toggle"),
	Container			 UMETA(DisplayName = "Container"),


};

USTRUCT()
struct FInteractableData
{
	GENERATED_BODY()

		FInteractableData() :
		InteractableType(EInteractableType::PickUp),
		Name(FText::GetEmpty()),
		Action(FText::GetEmpty()),
		Quantity(0),
		InteractionDuration(0.f)
	{

	};

	UPROPERTY(EditInstanceOnly)
		EInteractableType InteractableType;

	UPROPERTY(EditInstanceOnly)
		FText Name;

	UPROPERTY(EditInstanceOnly)
		FText Action;

	UPROPERTY(EditInstanceOnly)
		int8 Quantity;

	UPROPERTY(EditInstanceOnly)
		float InteractionDuration;

};
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIsACollectable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SPOOKYJAMEGAM2023_API IIsACollectable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GamePlayInterface")
		void Interact(APawn* InstigatorPawn);

	virtual void BeginFocus();
	virtual void EndFocus();
	virtual void BeginInteract();
	virtual void EndInteract();
	virtual void Interact();

	FInteractableData InteractableData;
};
