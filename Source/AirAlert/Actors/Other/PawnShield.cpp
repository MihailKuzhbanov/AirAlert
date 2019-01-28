#include "PawnShield.h"
#include "Pawns/PlayerPawn.h"

APawnShield::APawnShield()
{
 	
	PrimaryActorTick.bCanEverTick = true;

}

void APawnShield::ActivateShield(APlayerPawn* PlayerPawn)
{

	PlayerPawn->bCanBeDamaged = false;

	FAttachmentTransformRules AttachRules = FAttachmentTransformRules(
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepWorld,
		false
		);

	AttachToActor(PlayerPawn, AttachRules);

}

void APawnShield::DeactivateShield()
{

	//PlayerPawn->bCanBeDamaged = true;

}
