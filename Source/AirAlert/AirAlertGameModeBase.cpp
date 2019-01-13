#include "AirAlertGameModeBase.h"

AAirAlertGameModeBase::AAirAlertGameModeBase()
{
	EnemySpawnController = CreateDefaultSubobject<UEnemySpawnController>(TEXT("EnemySpawnController"));
	HealthsComponent = CreateDefaultSubobject<UGameHealthComponent>(TEXT("HealthsComponent"));

}
