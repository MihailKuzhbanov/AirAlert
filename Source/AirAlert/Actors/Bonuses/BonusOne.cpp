#include "BonusOne.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Pawns/PlayerPawn.h"

ABonusOne::ABonusOne()
{

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("BonusCollision"));
	RootComponent = Collision;

	Collision->SetCollisionObjectType(ECC_WorldDynamic);
	//Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	//Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	Collision->SetSphereRadius(50);

}

void ABonusOne::NotifyActorBeginOverlap(AActor * OtherActor)
{
	
	Super::NotifyActorEndOverlap(OtherActor);

	if (!OtherActor) return;
	if (!Cast<APlayerPawn>(OtherActor)) return;

	BonusCollected();

}

void ABonusOne::BonusCollected_Implementation()
{
	Destroy();
}

void ABonusOne::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	float WorldMoveOffset = -100.f * DeltaTime;

	AddActorWorldOffset(FVector(WorldMoveOffset, 0.f, 0.f));

}
