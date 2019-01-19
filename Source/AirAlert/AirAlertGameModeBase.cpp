#include "AirAlertGameModeBase.h"

AAirAlertGameModeBase::AAirAlertGameModeBase()
{
	EnemySpawnController = CreateDefaultSubobject<UEnemySpawnController>(TEXT("EnemySpawnController"));
	HealthsComponent = CreateDefaultSubobject<UGameHealthComponent>(TEXT("HealthsComponent"));

}

void AAirAlertGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HealthsComponent->HealthsEnded.AddDynamic(this, &AAirAlertGameModeBase::EndGame);

}

void AAirAlertGameModeBase::EndGame()
{
	GameOver.Broadcast();

	UE_LOG(LogTemp, Log, TEXT("GAME OVER!!!"))
}
