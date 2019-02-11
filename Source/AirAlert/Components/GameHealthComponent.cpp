#include "GameHealthComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"

UGameHealthComponent::UGameHealthComponent()
	:
	Healths(5)
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

int UGameHealthComponent::SetHealth(int Value)
{
	Healths = Value;
	return Healths;
}



