#pragma once

#include "CoreMinimal.h"
#include "Actors/Bonuses/BonusOne.h"
#include "BonusShootUp.generated.h"

UCLASS()
class AIRALERT_API ABonusShootUp : public ABonusOne
{
	GENERATED_BODY()
	
protected:

	virtual void BonusCollected_Implementation() override;
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonus")
		int LevelsAdded;
};


