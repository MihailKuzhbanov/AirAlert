#include "AirAlertGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/PlayerPawn.h"

AAirAlertGameModeBase::AAirAlertGameModeBase()
	:
	PlayerRecoverTime(3)
{
	EnemySpawnController = CreateDefaultSubobject<UEnemySpawnController>(TEXT("EnemySpawnController"));
	HealthsComponent = CreateDefaultSubobject<UGameHealthComponent>(TEXT("HealthsComponent"));

}

void AAirAlertGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HealthsComponent->HealthsEnded.AddDynamic(this, &AAirAlertGameModeBase::EndGame);

	PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));

	PlayerPawn->PawnDamaged.AddDynamic(this, &AAirAlertGameModeBase::ExplodePawn);
}

void AAirAlertGameModeBase::ExplodePawn_Implementation()
{
	PlayerPawn->ExplodePawn();
	
	HealthsComponent->ChangeHealth(-1);

	GetWorld()->GetTimerManager().SetTimer(RecoverTimer, this, &AAirAlertGameModeBase::RecoverPawn, PlayerRecoverTime, false);
}

void AAirAlertGameModeBase::RecoverPawn_Implementation()
{
	PlayerPawn->RecoverPawn();
}

void AAirAlertGameModeBase::EndGame()
{
	GameOver.Broadcast();

	UE_LOG(LogTemp, Log, TEXT("GAME OVER!!!"))
}