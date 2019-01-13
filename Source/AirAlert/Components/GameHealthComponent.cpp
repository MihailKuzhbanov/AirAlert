// Fill out your copyright notice in the Description page of Project Settings.

#include "GameHealthComponent.h"


// Sets default values for this component's properties
UGameHealthComponent::UGameHealthComponent()
	:
	Healths(3)
{

	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGameHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}

void UGameHealthComponent::ChangeHealth(int ByValue)
{
	Healths += ByValue;

	HealthsChanged.Broadcast(ByValue);
	if (Healths <= 0)
	{
		HealthsEnded.Broadcast();
	}
}

int UGameHealthComponent::GetHealth()
{
	return Healths;
}



