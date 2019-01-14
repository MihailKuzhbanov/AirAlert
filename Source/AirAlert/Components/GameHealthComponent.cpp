

#include "GameHealthComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"

UGameHealthComponent::UGameHealthComponent()
	:
	Healths(3)
{

	PrimaryComponentTick.bCanEverTick = true;

	
}

void UGameHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("No playerPawn!!"));
		return;
	}
	
	PlayerPawn->OnTakeAnyDamage.AddDynamic(this, &UGameHealthComponent::OnPlayerDamaged);
}

void UGameHealthComponent::OnPlayerDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Insigator, AActor* DamageCause)
{
	ChangeHealth(-1);
}

void UGameHealthComponent::ChangeHealth(int ByValue)
{
	Healths += ByValue;

	HealthsChanged.Broadcast(ByValue);
	if (Healths <= 0)
	{
		HealthsEnded.Broadcast();
	}
	UE_LOG(LogTemp, Log, TEXT("Health changed: %i"), Healths);
}

int UGameHealthComponent::GetHealth()
{
	return Healths;
}



