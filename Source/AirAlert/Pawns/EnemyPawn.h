#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Components/ShootComponent.h"
#include "Components/HealthComponent.h"
#include "Actors/Bonuses/BonusOne.h"
#include "EnemyPawn.generated.h"

USTRUCT(BlueprintType)
struct FBonusChance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bonus")
		TSubclassOf<ABonusOne> BonusClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bonus")
		float Chance;

};

UCLASS()
class AIRALERT_API AEnemyPawn : public APawn
{
	GENERATED_BODY()

public:
	
	AEnemyPawn();

protected:
	
	virtual void BeginPlay() override;

	void SpawnBonuses();

	UFUNCTION()
		void KillPawn();

	UFUNCTION()
	void OnEnemyOverlap(AActor* OverlappedActor, AActor* OtherActor);


public:	
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Pawn")
		void DestroyPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		UBoxComponent* PawnCollision;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
		UStaticMeshComponent* PawnMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
		UShootComponent* ShootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
		UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
		int DestroyPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bonus")
		TArray<FBonusChance> PossibleBonuses;
};
