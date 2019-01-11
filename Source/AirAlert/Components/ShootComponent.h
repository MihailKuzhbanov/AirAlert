// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Actors/Projectiles/ShootProjectile.h"
#include "ShootComponent.generated.h"

USTRUCT(BlueprintType)
struct FShootInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
		TSubclassOf<AShootProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
		float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		FVector Offset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		float Angle;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AIRALERT_API UShootComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UShootComponent();

protected:
	
	virtual void BeginPlay() override;

	void Shoot();

	FTimerHandle ShootingTimer;

public:	
	
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void StartShooting();

	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void StopShooting();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
	float ShootPeriod;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
	TArray<FShootInfo> ShootInfos;
	
};
