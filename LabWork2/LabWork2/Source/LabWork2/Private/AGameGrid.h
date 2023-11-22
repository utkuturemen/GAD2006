

#pragma once

#include "CoreMinimal.h"
#include "AGameSlot.h"
#include "GameFramework/Actor.h"
#include "AGameGrid.generated.h"

UCLASS()
class AAGameGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAGameGrid();

	virtual  void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AAGameSlot>GridClass;

	UPROPERTY(EditAnywhere)
	int NumRows;

	UPROPERTY(EditAnywhere)
	int NumCols;

	UPROPERTY(VisibleAnywhere)
	TArray<UChildActorComponent*> GridActors;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AAGameSlot * GetSlot(FSGridPosition&Position);
	static AAGameSlot* FindSlot(FSGridPosition Position);

private:

	static AAGameGrid*GameGrid;

};
