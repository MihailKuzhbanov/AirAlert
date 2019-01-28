#pragma once

#include "CoreMinimal.h"
#include "Actors/Bonuses/BonusOne.h"
#include "BonusShield.generated.h"

class APawnShield;

UCLASS()
class AIRALERT_API ABonusShield : public ABonusOne
{
	GENERATED_BODY()
	
protected:

	virtual void BonusCollected_Implementation() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield")
		int TimeShield;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield")
		TSubclassOf<APawnShield> ShieldClass;
};
