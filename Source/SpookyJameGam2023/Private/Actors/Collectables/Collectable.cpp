// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Collectables/Collectable.h"
#include "Character/SJG_Player_Character.h"
#include "Engine/SkeletalMeshSocket.h"


// Sets default values
ACollectable::ACollectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	RootComponent=Mesh;

	

	box = CreateDefaultSubobject<UBoxComponent>("box");
	box->SetupAttachment(GetRootComponent());

	box->SetCollisionObjectType(ECC_WorldDynamic);


}

// Called when the game starts or when spawned
void ACollectable::BeginPlay()
{
	Super::BeginPlay();



}

void ACollectable::EquipRightHand(ASJG_Player_Character* Character)
{
	if(Character)
	{
		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);//make the camera of character not affected by the sword movement
		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);//
	

		const USkeletalMeshSocket* RighHandSocket = Character->GetMesh()->GetSocketByName("RightHandSocket");//call the socket created in the class and attach it to the socket in the skeleton

		if (RighHandSocket)//attach the weapon to the right hand socket
		{
			RighHandSocket->AttachActor(this, Character->GetMesh());
			box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			box->SetCollisionObjectType(ECC_WorldStatic);
			Character->bIsHoldingRightWeapon = true;
			Character->SetRightEquippedCollectable(this);


		}

	}
}

void ACollectable::EquipLeftHand(ASJG_Player_Character* Character)
{
	if (Character )
	{

		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);//make the camera of character not affected by the sword movement
		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);//


		const USkeletalMeshSocket* LeftHandSocket = Character->GetMesh()->GetSocketByName("LeftHandSocket");//call the socket created in the class and attach it to the socket in the skeleton

		if (LeftHandSocket)//attach the weapon to the right hand socket
		{
			LeftHandSocket->AttachActor(this, Character->GetMesh());

			box->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			Character->bIsHoldingLeftWeapon = true;
		}
	}
}
//=======================================
//UNEQUIP FUNCTIONS
void ACollectable::UnEquipRightHand(ASJG_Player_Character* Character)
{
	if(Character)
	{
		if(Character->bIsHoldingRightWeapon==true)
		{
			ACollectable* Collectable= Character->GetrightCollectableHolded();

			Collectable->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

			Collectable->SetWeaponState(ECollectableState::EWS_Pickup);
			Character->bIsHoldingRightWeapon = false;

		}
	}
}

void ACollectable::UnEquipLeftHand(ASJG_Player_Character* Character)
{
	if (Character)
	{
		if (Character->bIsHoldingLeftWeapon == true)
		{
			ACollectable* Collectable = Character->GetLeftCollectableHolded();
			Collectable->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);


			Collectable->SetWeaponState(ECollectableState::EWS_Pickup);


		}
	}
}








