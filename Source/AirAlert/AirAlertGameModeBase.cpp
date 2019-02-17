#include "AirAlertGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/PlayerPawn.h"

AAirAlertGameModeBase::AAirAlertGameModeBase()
	:
	PlayerRecoverTime(3),
	CurrentShootLevel(-1),
	IncreaseDifficultyPriod(1.f)
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

	ChangeShootLevel(true, 1);

	MaxHealths = HealthsComponent->GetHealth();

	UE_LOG(LogTemp, Log, TEXT("Max Health: %d"), MaxHealths);

	PlayerPawn->PawnDamaged.AddDynamic(this, &AAirAlertGameModeBase::ExplodePawn);

	GetWorld()->GetTimerManager().SetTimer(IncreaseTimer, this, &AAirAlertGameModeBase::IncreaseDifficulty, IncreaseDifficultyPriod, true);
}

void AAirAlertGameModeBase::ExplodePawn_Implementation()
{
	PlayerPawn->ExplodePawn();
	
	HealthsComponent->ChangeHealth(-1);

	ChangeShootLevel(false, -1);

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

void AAirAlertGameModeBase::IncreaseDifficulty()
{

	EnemySpawnController->ChangeStageTimeMultiplier = FMath::Max(EnemySpawnController->ChangeStageTimeMultiplier*0.95, 0.4);

}

void AAirAlertGameModeBase::AddPoints(int Points)
{
	GamePoints += Points;
}

bool AAirAlertGameModeBase::ChangeShootLevel(bool Up, int Levels)
{
	PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!PlayerPawn) return false;

	
	int NewLevel = FMath::Clamp(CurrentShootLevel + (Up ? Levels + 0 : -1), 0, ShootInfoLevels.Num()-1);

	if (NewLevel == CurrentShootLevel) return false;

	CurrentShootLevel = NewLevel;

	PlayerPawn->ShootComponent->ShootInfos = ShootInfoLevels[CurrentShootLevel].ShootInfos;
	PlayerPawn->ShootComponent->ShootPeriod = ShootInfoLevels[CurrentShootLevel].ShootPeriod;
	
	return true;
}


