// Fill out your copyright notice in the Description page of Project Settings.


#include "COABaseCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACOABaseCharacter::ACOABaseCharacter()  :

	MaxHealth(0.0f),
	Health(0.0f),
	HealingRate(10.0f),
	WalkSpeed(200.0f)
	
{
 	
	PrimaryActorTick.bCanEverTick = true;

	MaxHealth = 100;
	

}

void ACOABaseCharacter::SetHealth(float NewHealth)
{
	Health = NewHealth;
}

float ACOABaseCharacter::GetHealth()
{
	return Health;
}




void ACOABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->bOrientRotationToMovement=true;
	GetCharacterMovement()->MaxWalkSpeed=WalkSpeed;
}

void ACOABaseCharacter::OnConstruction(const FTransform& Transform)
{
	Health = MaxHealth;
	Update=false;
	
}

// Called every frame
void ACOABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}








