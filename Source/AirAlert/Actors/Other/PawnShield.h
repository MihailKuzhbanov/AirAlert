#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PawnShield.generated.h"

class APlayerPawn;

UCLASS()
class AIRALERT_API APawnShield : public AActor
{
	GENERATED_BODY()
	

protected:

	FTimerHandle ShieldTimer;

	class APlayerPawn* ShieldForPawn;

public:	

	APawnShield();

	UFUNCTION(BlueprintCallable, Category = "Shield")
		void ActivateShield(APlayerPawn* PlayerPawn, float TimeShield);

	UFUNCTION(BlueprintCallable, Category = "Shield")
		void DeactivateShield();
	
};