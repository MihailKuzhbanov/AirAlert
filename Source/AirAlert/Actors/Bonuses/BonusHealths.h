#pragma once

#include "CoreMinimal.h"
#include "Actors/Bonuses/BonusOne.h"
#include "BonusHealths.generated.h"

UCLASS()
class AIRALERT_API ABonusHealths : public ABonusOne
{
	GENERATED_BODY()
	
protected:

	virtual void BonusCollected_Implementation() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonus")
		int HealthsAdded;
	
	
};
