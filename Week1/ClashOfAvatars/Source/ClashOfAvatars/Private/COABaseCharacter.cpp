// Fill out your copyright notice in the Description page of Project Settings.


#include "COABaseCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACOABaseCharacter::ACOABaseCharacter()  :
	Health(0.0f),
	MaxHealth(0.0f),
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

	if (!bDead)
	{
		Health =FMath ::Min(MaxHealth,Health+HealingRate*DeltaTime);
	}
	
}

float ACOABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
									AActor* DamageCauser)
{
	if (bDead) return 0.0f;
	DamageAmount = ModifyDamage(DamageAmount);
	Health -= DamageAmount;
	GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Red, FString::Printf(TEXT("Health: %f"), Health));

	if (Health <= 0)
	{
		bDead = true;
		APlayerController * PlayerController = Cast<APlayerController>(GetController());
		if(PlayerController) DisableInput(PlayerController);
		
	}

	return DamageAmount;
}


	









