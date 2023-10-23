

#include "Attribute/AttributeComponent.h"


UAttributeComponent::UAttributeComponent()
	: Health(50.0f),
	MaxHealth(100.0f),
	Mana(50.0f),
	MaxMana(100.0f)

{
	// Ensure PrimaryComponentTick is properly initialized if you still need ticking
	PrimaryComponentTick.bCanEverTick = true;

	OnDeath.AddDynamic(this, &UAttributeComponent::Die);
}


void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UAttributeComponent::TakeDamage(float Damage)
{
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);

	if (Health <= 0.0f)
	{
		Die();
	}
}

void UAttributeComponent::ConsumeMana(float ManaValue)
{
	Mana = FMath::Clamp(Mana - ManaValue, 0.0f, MaxMana);

}

void UAttributeComponent::TakeHeal(float HealValue)
{
	Health = FMath::Clamp(Health + HealValue, 0, MaxHealth);
}

void UAttributeComponent::TakeMana(float ManaValue)
{
	Mana = FMath::Clamp(Mana + ManaValue, 0.0f, MaxMana);
}

void UAttributeComponent::Die()
{
	OnDeath.Broadcast();
}



