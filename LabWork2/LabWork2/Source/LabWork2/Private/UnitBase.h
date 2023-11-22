// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnitBase.generated.h"


class AAGameSlot;

UCLASS()
class AUnitBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnitBase();

	void AssignToSlot(AAGameSlot*NewSlot);

	UFUNCTION(BlueprintImplementableEvent,BlueprintPure)
	bool IsControlledByThePlayer();

	UPROPERTY(EditAnywhere)
	FVector StartOffset;

	UPROPERTY(EditAnywhere)
	AAGameSlot*Slot;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
