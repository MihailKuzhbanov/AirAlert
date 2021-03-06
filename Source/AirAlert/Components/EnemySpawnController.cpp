#include "EnemySpawnController.h"
#include "AirAlertGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"


void UEnemySpawnController::BeginPlay()

{

	Super::BeginPlay();

	Random.GenerateNewSeed();
	
	StartSpawnStage();

}

void UEnemySpawnController::Deactivate()
{
	Super::Deactivate();

	GetWorld()->GetTimerManager().ClearTimer(ChangeStageTimer);
	GetWorld()->GetTimerManager().ClearTimer(EnemySpawnTimer);
}


void UEnemySpawnController::StartSpawnStage()
{
	AAirAlertGameModeBase * Gamemode = Cast<AAirAlertGameModeBase>(UGameplayStatics::GetGameMode(this));
	SpawnStage = SpawnStages[Random.RandRange(0, SpawnStages.Num() - 1)];
	while (Gamemode->CurrentShootLevel < SpawnStage.StartLevel)	SpawnStage = SpawnStages[Random.RandRange(0, SpawnStages.Num() - 1)];

		EnemiesSpawned = 0;
		SpawnEnemy();

		float ChangeStageTime = Random.RandRange(StageMinDelay, StageMaxDelay) * ChangeStageTimeMultiplier;
		GetWorld()->GetTimerManager().SetTimer(ChangeStageTimer, this, &UEnemySpawnController::StartSpawnStage, ChangeStageTime, false);
}

void UEnemySpawnController::SpawnEnemy()
{
	
	FActorSpawnParameters SpawnParameters;
	GetWorld()->SpawnActor<AEnemyPawn>(SpawnStage.EnemyClass, SpawnStage.SpawnTranform, SpawnParameters);
	
	EnemiesSpawned++;
	if (EnemiesSpawned < SpawnStage.NumOfEnemies)
	{
		GetWorld()->GetTimerManager().SetTimer(EnemySpawnTimer, this, &UEnemySpawnController::SpawnEnemy, SpawnStage.SpawnDelay, false);
	}
}