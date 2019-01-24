#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlaygroundBorder.generated.h"

UCLASS()
class AIRALERT_API APlaygroundBorder : public AActor
{
	GENERATED_BODY()
	
public:	

	APlaygroundBorder();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* Trigger;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
};
