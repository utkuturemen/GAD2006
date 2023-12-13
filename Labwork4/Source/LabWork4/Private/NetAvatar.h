#pragma once

#include "CoreMinimal.h"
#include "NetBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"
#include "NetAvatar.generated.h"

/**
 * 
 */
UCLASS()
class ANetAvatar : public ANetBaseCharacter
{
	GENERATED_BODY()
	
public:
	
	ANetAvatar();

	UPROPERTY(BlueprintReadWrite)
	UCameraComponent* Camera;

	UPROPERTY(BlueprintReadWrite)
	USpringArmComponent* SpringArm;


	UPROPERTY(BlueprintReadWrite)
	float SpeedMult;

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_PlayerSpeedChanged)
	float Speed;

	UFUNCTION()
	void OnRep_PlayerSpeedChanged();

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Server, Reliable)
	void SetSpeedInServer(float _speed);

private:
	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void RunPressed();
	void RunReleased();
};