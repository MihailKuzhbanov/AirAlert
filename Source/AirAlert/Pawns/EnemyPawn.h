// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Components/ShootComponent.h"
#include "Components/HealthComponent.h"
#include "EnemyPawn.generated.h"

UCLASS()
class AIRALERT_API AEnemyPawn : public APawn
{
	GENERATED_BODY()

public:
	
	AEnemyPawn();

protected:
	
	virtual void BeginPlay() override;
	UFUNCTION()
		void DestroyPawn();

	UFUNCTION()
	void OnEnemyOverlap(AActor* OverlappedActor, AActor* OtherActor);


public:	
	
	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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
};
