#include "EnemyPawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework//DamageType.h"
#include "Components/StaticMeshComponent.h"
#include "AirAlertGameModeBase.h"
#include "Engine/World.h"


AEnemyPawn::AEnemyPawn()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));
	RootComponent = PawnCollision;
	PawnCollision->SetCollisionProfileName("Pawn");

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
	PawnMesh->SetupAttachment(PawnCollision, NAME_None);
	PawnMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

}

void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnHealthEnded.AddDynamic(this, &AEnemyPawn::KillPawn);
	OnActorBeginOverlap.AddDynamic(this, &AEnemyPawn::OnEnemyOverlap);
}

void AEnemyPawn::KillPawn()
{
	AAirAlertGameModeBase* Gamemode = Cast<AAirAlertGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (Gamemode) Gamemode->AddPoints(DestroyPoints);
	SpawnBonuses();
	DestroyPawn();

}

void AEnemyPawn::DestroyPawn()
{
	//AAirAlertGameModeBase* Gamemode = Cast<AAirAlertGameModeBase>(UGameplayStatics::GetGameMode(this));
	//if (Gamemode) Gamemode->AddPoints(DestroyPoints);

	Destroy();

}

void AEnemyPawn::OnEnemyOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor != UGameplayStatics::GetPlayerPawn(this, 0)) return;

	float AppliedDamage = UGameplayStatics::ApplyDamage(OtherActor, 100.f, GetController(), this, UDamageType::StaticClass());

	if (AppliedDamage > 0) DestroyPawn();
}

void AEnemyPawn::SpawnBonuses()
{
	FRandomStream Random;
	Random.GenerateNewSeed();
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (FBonusChance Bonus : PossibleBonuses)
	{
		if (Random.RandRange(0, 100.f) < Bonus.Chance)
		{
			GetWorld()->SpawnActor<ABonusOne>(Bonus.BonusClass, GetActorLocation(), FRotator(0.f), SpawnParameters);
		}
	}
}

void AEnemyPawn::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	float WorldMoveOffset = -100.f * DeltaTime;

	AddActorWorldOffset(FVector(WorldMoveOffset, 0.f, 0.f));

}