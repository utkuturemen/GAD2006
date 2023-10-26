// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "COABaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "COAAvatar.generated.h"

/**
 * 
 */
UCLASS()
class ACOAAvatar : public ACOABaseCharacter
{
	GENERATED_BODY()

public:
	ACOAAvatar();

	UPROPERTY(VisibleAnywhere, Category = "COA")
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = "COA")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category="COA")
	float RunSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="COA")
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="COA")
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="COA")
	float StaminaGainRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="COA")
	float StaminaDrainRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="COA")
	bool StaminaDrained;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="COA")
	bool IsRunning;


	UFUNCTION(BlueprintCallable, Category="COA")
	void SetStamina(float NewStamina);

	UFUNCTION(BlueprintCallable, Category="COA")
	float GetStamina();


	

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Tick(float DeltaTime) override;
	void BeginPlay() override;
	void OnConstruction(const FTransform& Transform) override;


private:
	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void RunPressed();
	void RunRealesed();

	void UpdateMovementParams();
};
