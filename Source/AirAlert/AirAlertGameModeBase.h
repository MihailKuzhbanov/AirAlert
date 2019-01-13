// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Components/EnemySpawnController.h"
#include "Components/GameHealthComponent.h"
#include "AirAlertGameModeBase.generated.h"

UCLASS()
class AIRALERT_API AAirAlertGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AAirAlertGameModeBase();
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemies")
		UEnemySpawnController* EnemySpawnController;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Health")
		UGameHealthComponent* HealthsComponent;
	
	
};
