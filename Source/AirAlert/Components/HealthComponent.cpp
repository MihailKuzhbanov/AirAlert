#include "HealthComponent.h"
#include "GameFramework/Actor.h"

UHealthComponent::UHealthComponent()
	:
	Health(100)
{

	


}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnOwnerDamaged);


}

void UHealthComponent::OnOwnerDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Insigator, AActor* DamageCause)
{
	ChangeHealth(-Damage);
}

void UHealthComponent::ChangeHealth(float Value)
{
	Health += Value;

	if (Health <= 0.f)
	{
		GetOwner()->OnTakeAnyDamage.RemoveDynamic(this, &UHealthComponent::OnOwnerDamaged);

		OnHealthEnded.Broadcast();
	}
}

float UHealthComponent::GetHealth()
{
	return Health;
}

