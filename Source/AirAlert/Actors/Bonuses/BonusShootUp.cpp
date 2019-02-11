#include "BonusShootUp.h"
#include "Kismet/GameplayStatics.h"
#include "AirAlertGameModeBase.h"

void ABonusShootUp::BonusCollected_Implementation()
{

	AAirAlertGameModeBase* Gamemode = Cast<AAirAlertGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (!Gamemode) return;

	

	Gamemode->ChangeShootLevel(true,LevelsAdded);

	Super::BonusCollected_Implementation();

}


