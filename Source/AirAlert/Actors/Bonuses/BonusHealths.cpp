#include "BonusHealths.h"
#include "Kismet/GameplayStatics.h"
#include "AirAlertGameModeBase.h"

void ABonusHealths::BonusCollected_Implementation()
{

	AAirAlertGameModeBase* Gamemode = Cast<AAirAlertGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (Gamemode->HealthsComponent->GetHealth() + HealthsAdded > Gamemode->MaxHealths)
		Gamemode->HealthsComponent->SetHealth(Gamemode->MaxHealths);
		else Gamemode->HealthsComponent->ChangeHealth(HealthsAdded);


	Super::BonusCollected_Implementation();

}

