#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Components/EnemySpawnController.h"
#include "Components/GameHealthComponent.h"
#include "AirAlertGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverEvent);

UCLASS()
class AIRALERT_API AAirAlertGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AAirAlertGameModeBase();

	virtual void BeginPlay() override;
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemies")
		UEnemySpawnController* EnemySpawnController;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Health")
		UGameHealthComponent* HealthsComponent;
	
	UPROPERTY(BlueprintAssignable, Category = "Game")
		FGameOverEvent GameOver;

	UFUNCTION(BlueprintCallable, Category = "Game")
		void EndGame();

};
