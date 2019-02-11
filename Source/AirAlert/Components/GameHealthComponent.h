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

	UGameHealthComponent();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Game Health")
	int Healths;
	

public:	
	
	UFUNCTION(BlueprintCallable, Category = "Game Health")
		void ChangeHealth(int ByValue);

	UFUNCTION(BlueprintPure, Category = "Game Health")
		int GetHealth();

	UFUNCTION(BlueprintPure, Category = "Game Health")
		int SetHealth(int Value);

	UPROPERTY(BlueprintAssignable, Category = "Game Health")
		FHealthsEndedEvent HealthsEnded;

	UPROPERTY(BlueprintAssignable, Category = "Game Health")
		FHealthsChangedEvent HealthsChanged;
};
