#include "BonusShield.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/PlayerPawn.h"
#include "Engine/World.h"
#include "Actors/Other/PawnShield.h"

void ABonusShield::BonusCollected_Implementation()
{
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!Pawn) return;
	APlayerPawn* PlayerPawn = Cast<APlayerPawn>(Pawn);
	if (!PlayerPawn) return;

	APawnShield* Shield = GetWorld()->SpawnActor<APawnShield>(ShieldClass);
	Shield->ActivateShield(PlayerPawn, TimeShield);
	

	Super::BonusCollected_Implementation();

}


