
#pragma once

#include "CoreMinimal.h"
#include "Actors/Interface/IsACollectable.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"

#include "Collectable.generated.h"

class ASJG_Player_Character;

UENUM(BlueprintType)
enum class ECollectableState :uint8
{
	EWS_Pickup		 UMETA(Display_Name = "Pickup"),
	EWS_Equipped	 UMETA(Display_Name = "Equipped"),

	EWS_Max   UMETA(Display_Name = "Deafaultmax")
};

UENUM()
enum class ECollectableType :uint8
{
	ECT_Weapon,
	ECT_Item
};

UENUM()
enum class EWeaponType :uint8
{
	ECT_axe,
	ECT_hatchet
};

UENUM()
enum class EBodyPartType :uint8
{
	ECT_Head,
	ECT_Item
};

UCLASS()
class SPOOKYJAMEGAM2023_API ACollectable : public AActor,public IIsACollectable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectable();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Collect ")
		ECollectableState CollectableState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Collect ")
		ECollectableType CollectableType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Collect ")
		EWeaponType WeaponType;

	FORCEINLINE void SetWeaponState(ECollectableState state) { CollectableState = state; }

	FORCEINLINE  ECollectableState GetCollectableState() { return  CollectableState; }

	FORCEINLINE   ECollectableType GetCollectableType() { return  CollectableType; }



	void EquipRightHand(ASJG_Player_Character*Character);

	void EquipLeftHand(ASJG_Player_Character*Character);

	void UnEquipRightHand(ASJG_Player_Character*Character);

	void UnEquipLeftHand(ASJG_Player_Character*Character);


protected:

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TObjectPtr<UBoxComponent>box;





};
