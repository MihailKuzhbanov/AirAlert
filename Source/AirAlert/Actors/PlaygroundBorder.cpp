#include "PlaygroundBorder.h"
#include "Components/BoxComponent.h"
#include "Pawns/PlayerPawn.h"

APlaygroundBorder::APlaygroundBorder()
{
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	SetRootComponent(Trigger);

	Trigger->SetCollisionProfileName("OverlapAll");
}

void APlaygroundBorder::NotifyActorEndOverlap(AActor * OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (!OtherActor) return;

	if (Cast<APlayerPawn>(OtherActor)) return;

	UE_LOG(LogTemp, Log, TEXT("OUT OF PLAYGROUND"));

	OtherActor->Destroy();
}
