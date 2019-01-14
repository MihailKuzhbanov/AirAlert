// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthsEndedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthsChangedEvent, int, ChangeValue);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AIRALERT_API UGameHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGameHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Game Health")
	int Healths;
	
	UFUNCTION()
	void OnPlayerDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Insigator, AActor* DamageCause);

public:	
	// Called every frame
	
	UFUNCTION(BlueprintCallable, Category = "Game Health")
		void ChangeHealth(int ByValue);

	UFUNCTION(BlueprintPure, Category = "Game Health")
		int GetHealth();

	UPROPERTY(BlueprintAssignable, Category = "Game Health")
		FHealthsEndedEvent HealthsEnded;

	UPROPERTY(BlueprintAssignable, Category = "Game Health")
		FHealthsChangedEvent HealthsChanged;
};
