#include "AirAlertGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/PlayerPawn.h"

AAirAlertGameModeBase::AAirAlertGameModeBase()
	:
	PlayerRecoverTime(3),
	CurrentShootLevel(-1)
{
	EnemySpawnController = CreateDefaultSubobject<UEnemySpawnController>(TEXT("EnemySpawnController"));
	HealthsComponent = CreateDefaultSubobject<UGameHealthComponent>(TEXT("HealthsComponent"));

}

void AAirAlertGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HealthsComponent->HealthsEnded.AddDynamic(this, &AAirAlertGameModeBase::EndGame);

	PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!PlayerPawn) return;

	ChangeShootLevel(true);

	PlayerPawn->PawnDamaged.AddDynamic(this, &AAirAlertGameModeBase::ExplodePawn);
}

void AAirAlertGameModeBase::ExplodePawn_Implementation()
{
	PlayerPawn->ExplodePawn();
	
	HealthsComponent->ChangeHealth(-1);

	if (!IsGameOver)
		GetWorld()->GetTimerManager().SetTimer(RecoverTimer, this, &AAirAlertGameModeBase::RecoverPawn, PlayerRecoverTime, false);
}

void AAirAlertGameModeBase::RecoverPawn_Implementation()
{
	PlayerPawn->RecoverPawn();
}

void AAirAlertGameModeBase::EndGame()
{
	IsGameOver = true;
	
	EnemySpawnController->SetActive(false);
		
	GameOver.Broadcast();

	UGameplayStatics::GetPlayerPawn(this, 0)->Destroy();
		
}

void AAirAlertGameModeBase::AddPoints(int Points)
{
	GamePoints += Points;
}

bool AAirAlertGameModeBase::ChangeShootLevel(bool Up)
{
	PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!PlayerPawn) return false;

	int NewLevel = FMath::Clamp(CurrentShootLevel + (Up ? 1 : -1), 0, ShootInfoLevels.Num()-1);

	if (NewLevel == CurrentShootLevel) return false;

	CurrentShootLevel = NewLevel;

	PlayerPawn->ShootComponent->ShootInfos = ShootInfoLevels[CurrentShootLevel].ShootInfos;
	PlayerPawn->ShootComponent->ShootPeriod = ShootInfoLevels[CurrentShootLevel].ShootPeriod;
	
	return true;
}
