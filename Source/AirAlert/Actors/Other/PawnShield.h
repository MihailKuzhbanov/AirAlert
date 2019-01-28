#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PawnShield.generated.h"

class APlayerPawn;

UCLASS()
class AIRALERT_API APawnShield : public AActor
{
	GENERATED_BODY()
	
public:	

	APawnShield();



public:	

	UFUNCTION(BlueprintCallable, Category = "Shield")
		void ActivateShield(APlayerPawn* PlayerPawn);

	UFUNCTION(BlueprintCallable, Category = "Shield")
		void DeactivateShield();
	
};