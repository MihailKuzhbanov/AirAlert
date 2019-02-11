#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthEndedEvent);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AIRALERT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UHealthComponent();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Health")
		float Health;

	UFUNCTION()
		void OnOwnerDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Insigator, AActor* DamageCause);
	
public:	

	
	UFUNCTION(BlueprintCallable, Category = "Health")
		void ChangeHealth(float Value);
	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetHealth();
	UPROPERTY(BlueprintAssignable, Category = "Health")
		FHealthEndedEvent OnHealthEnded;

};
