#include "PlayerPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "TimerManager.h"
//#include "Materials/MaterialInstanceDynamic.h"



APlayerPawn::APlayerPawn()
	:
	TouchMoveSensetivity(1.f),
	MoveLimit(FVector2D(700.f, 800.f))
{
 	PrimaryActorTick.bCanEverTick = true;

	PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));
	RootComponent = PawnCollision;

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
	PawnMesh->SetupAttachment(PawnCollision, NAME_None);

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));

	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));
}

void APlayerPawn::PossessedBy(AController * NewController)
{
	PlayerController = Cast<APlayerController>(NewController);
}

bool APlayerPawn::CanBeDamaged_Implementation()
{
	return bCanBeDamaged;
}

void APlayerPawn::ExplodePawn_Implementation()
{
	SetActorEnableCollision(false);

	ShootComponent->StopShooting();

	PawnMesh->SetMaterial(0, RecoverMaterial);
}

void APlayerPawn::RecoverPawn_Implementation()
{
	SetActorEnableCollision(true);

	ShootComponent->StartShooting();

	PawnMesh->SetMaterial(0, PawnMaterial);
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();


	PawnMaterial = PawnMesh->GetMaterial(0);
	//UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(Material, this);
}

float APlayerPawn::TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController * InstigatedBy, AActor * DamageCauser)
{
	if (!CanBeDamaged_Implementation()) return 0.f;
	ExplodePawn();
	Super::TakeDamage(Damage, DamageEvent, InstigatedBy, DamageCauser);
	PawnDamaged.Broadcast();
	return Damage;
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &APlayerPawn::OnTouchPress);
	InputComponent->BindTouch(IE_Repeat, this, &APlayerPawn::OnTouchMove);
}



void APlayerPawn::OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location)
{
	FVector2D TouchDeltaMove = FVector2D(TouchLocation.X - Location.X, TouchLocation.Y - Location.Y);

	TouchDeltaMove = TouchDeltaMove * TouchMoveSensetivity;

	FVector NewLocation = GetActorLocation();
	NewLocation.X = FMath::Clamp(NewLocation.X + TouchDeltaMove.Y, -MoveLimit.Y, MoveLimit.Y);
	NewLocation.Y = FMath::Clamp(NewLocation.Y + TouchDeltaMove.X*-1.f, -MoveLimit.X, MoveLimit.X);
	
	SetActorLocation(NewLocation);

	TouchLocation = FVector2D(Location.X, Location.Y);
}

void APlayerPawn::OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location)
{
	TouchLocation = FVector2D(Location.X, Location.Y);
}




