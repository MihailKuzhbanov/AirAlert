// Fill out your copyright notice in the Description page of Project Settings.

#include "AirAlertGameModeBase.h"

AAirAlertGameModeBase::AAirAlertGameModeBase()
{
	EnemySpawnController = CreateDefaultSubobject<UEnemySpawnController>(TEXT("EnemySpawnController"));
}
