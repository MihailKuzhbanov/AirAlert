#include "BonusPoints.h"
#include "Kismet/GameplayStatics.h"
#include "AirAlertGameModeBase.h"

void ABonusPoints::BonusCollected_Implementation()
{

	AAirAlertGameModeBase* Gamemode = Cast<AAirAlertGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (Gamemode) Gamemode->AddPoints(PointsAdded);

	Super::BonusCollected_Implementation();

}


