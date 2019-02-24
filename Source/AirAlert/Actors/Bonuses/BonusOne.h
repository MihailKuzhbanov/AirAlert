#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BonusOne.generated.h"

UCLASS(Blueprintable)
class AIRALERT_API ABonusOne : public AActor
{
	GENERATED_BODY()
	
public:	

	ABonusOne();

protected:

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION(BlueprintNativeEvent)
		void BonusCollected();
		virtual void BonusCollected_Implementation();
		virtual void Tick(float DeltaTime)override;
public:	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
		class USphereComponent* Collision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
		UParticleSystem* CollectParticle;

	
};
