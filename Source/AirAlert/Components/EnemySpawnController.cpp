// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySpawnController.h"
#include "Engine/World.h"
#include "TimerManager.h"


// Sets default values for this component's properties
//UEnemySpawnController::UEnemySpawnController()
//{
//	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
//	// off to improve performance if you don't need them.
//	//PrimaryComponentTick.bCanEverTick = true;
//}


// Called when the game starts
void UEnemySpawnController::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	SpawnStage = FEnemySpawnInfo();
	SpawnStage.NumOfEnemies = 10;
	SpawnStage.SpawnDelay = 1.f;
	
	StartSpawnStage();
}

void UEnemySpawnController::StartSpawnStage()
{
	GetWorld()->GetTimerManager().SetTimer(EnemySpawnTimer, this, &UEnemySpawnController::SpawnEnemy, SpawnStage.SpawnDelay, true, SpawnStage.SpawnDelay);
	
}

void UEnemySpawnController::SpawnEnemy()
{
	//UE_LOG(LogTemp, Log, TEXT("Spawned enemy"));

	FActorSpawnParameters SpawnParameters;
	GetWorld()->SpawnActor<APawn>(SpawnStage.EnemyClass, SpawnStage.SpawnTranform, SpawnParameters);
	
	EnemiesSpawned++;
	if (EnemiesSpawned >= SpawnStage.NumOfEnemies)
	{
		GetWorld()->GetTimerManager().ClearTimer(EnemySpawnTimer);
	}
}


// Called every frame
//void UEnemySpawnController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

