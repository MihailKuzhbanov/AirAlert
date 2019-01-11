// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Pawns/EnemyPawn.h"
#include "EnemySpawnController.generated.h"

USTRUCT(BlueprintType)
struct FEnemySpawnInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
	TSubclassOf<AEnemyPawn> EnemyClass = AEnemyPawn::StaticClass();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	FTransform SpawnTranform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	int NumOfEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	float SpawnDelay;
	
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AIRALERT_API UEnemySpawnController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	//UEnemySpawnController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void Deactivate() override;
	void StartSpawnStage();
	
	void SpawnEnemy();

	FEnemySpawnInfo SpawnStage;

	int EnemiesSpawned;

	FTimerHandle ChangeStageTimer;
	FTimerHandle EnemySpawnTimer;

	FRandomStream Random;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
	TArray<FEnemySpawnInfo> SpawnStages;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
	float StageMinDelay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
	float StageMaxDelay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
		float ChangeStageTimeMultiplier;

};
