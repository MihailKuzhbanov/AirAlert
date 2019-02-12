#include "ShootProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


AShootProjectile::AShootProjectile()
	:
	ProjectileSpeed(2000.f),
	Causer(0)
{
 	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollision"));
	RootComponent = Collision;
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	Mesh->SetupAttachment(Collision, NAME_None);
	Mesh->SetCollisionProfileName("NoCollision");

	
}

void AShootProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		
		UBoxComponent* OwnerCollision = GetOwner()->FindComponentByClass<UBoxComponent>();
		Collision->IgnoreComponentWhenMoving(OwnerCollision, true);
		OwnerCollision->IgnoreComponentWhenMoving(Collision, true);

		Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AShootProjectile::OnProjectileOverlap);
	
}

void AShootProjectile::OnProjectileOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool Sweep, const FHitResult& Hit)
{
	if (!OtherActor || !Cast<APawn>(OtherActor)) return;
	
	if (!GetOwner()) return;
	APawn* PawnOwner = Cast<APawn>(GetOwner());
	if (!PawnOwner) return;
	AController* Instigator = PawnOwner->GetController();

	UGameplayStatics::ApplyDamage(OtherActor, Damage, Instigator, this, UDamageType::StaticClass());
	
	Destroy();
}

void AShootProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(FVector(ProjectileSpeed*DeltaTime, 0.f , 0.f));
}

