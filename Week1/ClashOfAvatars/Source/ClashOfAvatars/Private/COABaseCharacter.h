// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "COABaseCharacter.generated.h"

UCLASS()
class ACOABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACOABaseCharacter();
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="COA")
	bool bDead;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="COA")
	float Health;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="COA")
	float MaxHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="COA")
	float HealingRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="COA")
	float WalkSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="COA")
	bool Update;
	
	UFUNCTION(BlueprintImplementableEvent)
	float ModifyDamage(float IncomingDamage);
	
	UFUNCTION(BlueprintCallable, Category="COA")
	void SetHealth(float NewHealth);
	
	UFUNCTION(BlueprintCallable, Category="COA")
	float GetHealth();

public:
	virtual void Tick(float DeltaTime) override;
	virtual  float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
};
