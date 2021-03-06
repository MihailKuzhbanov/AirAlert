#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ShootComponent.h"
#include "PlayerPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPawnDamagedEvent);

UCLASS()
class AIRALERT_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:

	APlayerPawn();

protected:

	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* InstigatedBy, AActor* DamageCauser) override;

	void OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location);

	void OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location);
	
	virtual void PossessedBy(AController* NewController) override;
		
	APlayerController* PlayerController;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
	FVector2D MoveLimit;

private:

	FVector2D TouchLocation;

	bool Touching;

	UMaterialInterface* PawnMaterial;

public:	
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Healths")
		bool CanBeDamaged();
		bool CanBeDamaged_Implementation();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		UBoxComponent* PawnCollision;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
		UStaticMeshComponent* PawnMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		UCameraComponent* PawnCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
		UShootComponent* ShootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controls")
		float TouchMoveSensetivity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controls")
		float RecoverTime;

	UPROPERTY(BlueprintAssignable, Category = "Healths")
		FPawnDamagedEvent PawnDamaged;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Healths")
		void ExplodePawn();
		void ExplodePawn_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Healths")
		void RecoverPawn();
		void RecoverPawn_Implementation();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
		UMaterialInterface* RecoverMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
		UParticleSystem* DestroyVFX;

};
