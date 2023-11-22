// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AGameGrid.h"
#include "UnitBase.h"
#include "Commands/Commend.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"


USTRUCT(BlueprintType)
struct FSUnitInfo
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AUnitBase> UnitClass;

	UPROPERTY(EditAnywhere)
	FSGridPosition StartPosition;
	
};

USTRUCT(BlueprintType)
struct FSLevelInfo
{
	GENERATED_USTRUCT_BODY();
	UPROPERTY(EditAnywhere)
	TArray<FSUnitInfo> Units;
};
UCLASS()
class AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

	void OnActorClicked(AActor*Actor,FKey button);

	void CreateLevelActors(FSLevelInfo&Info);

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int CurrentLevel;

	UPROPERTY(EditAnywhere)
	TArray<FSLevelInfo> Levels;

	UPROPERTY(EditAnywhere)
	AAGameGrid*GameGrid;

	UFUNCTION(BlueprintCallable)
	bool UndoLastMove();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	AUnitBase*ThePLayer;
	TArray<TSharedRef<Commend>>CommandPool;
	TSharedPtr<Commend>        CurrentCommand;
};
