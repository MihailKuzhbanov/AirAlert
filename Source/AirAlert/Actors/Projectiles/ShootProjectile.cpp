// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AShootProjectile::AShootProjectile()
	:
	ProjectileSpeed(2000.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollision"));
	RootComponent = Collision;


	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	Mesh->SetupAttachment(Collision, NAME_None);
	Mesh->SetCollisionProfileName("NoCollision");


}

// Called when the game starts or when spawned
void AShootProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		Collision->IgnoreActorWhenMoving(GetOwner(), true);
		UE_LOG(LogTemp, Log, TEXT("OWNER"));
	}

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AShootProjectile::OnProjectileOverlap);
	
}

void AShootProjectile::OnProjectileOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool Sweep, const FHitResult& Hit)
{
//	AController* Instigator = GetOwner()->GetOwner();
//	UGameplayStatics::ApplyDamage(OtherActor, Damage, , this, UDamageType::StaticClass());
	UE_LOG(LogTemp, Log, TEXT("Projectile Ovelapped"));
}

// Called every frame
void AShootProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(FVector(ProjectileSpeed*DeltaTime, 0.f , 0.f));
}

