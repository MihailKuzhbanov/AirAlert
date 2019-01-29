#include "PawnShield.h"
#include "Pawns/PlayerPawn.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Actors/Bonuses/BonusShield.h"

APawnShield::APawnShield()
	
{
	
}

void APawnShield::ActivateShield(APlayerPawn* PlayerPawn, float ShieldTime)
{
	if (!PlayerPawn)
	{
		Destroy();
		return;
	}

	ShieldForPawn = PlayerPawn;
	PlayerPawn->bCanBeDamaged = false;

	FAttachmentTransformRules AttachRules = FAttachmentTransformRules(
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepWorld,
		false
		);

	AttachToActor(PlayerPawn, AttachRules);

	GetWorld()->GetTimerManager().SetTimer(ShieldTimer, this, &APawnShield::DeactivateShield, ShieldTime, false);

}

void APawnShield::DeactivateShield()
{

	if (!ShieldForPawn) return;

	ShieldForPawn->bCanBeDamaged = true;

	Destroy();

}
