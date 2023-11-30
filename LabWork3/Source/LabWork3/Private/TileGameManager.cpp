// Fill out your copyright notice in the Description page of Project Settings.


#include "TileGameManager.h"

#include "TilePlayerController.h"
#include "GameFramework/PlayerInput.h"

// Sets default values
ATileGameManager::ATileGameManager() :
	GridSize(100),
	GridOffset(0,0,0.5f),
	MapExtendsInGrids(25)

{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	GridSelection = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GridMesh"));
	GridSelection->SetupAttachment(RootComponent);

	SelectedShow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GridMeshDisplay"));
	SelectedShow->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneMesh(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> GridMaterial(TEXT("Material'/Game/UI/MAT_GridSlot.MAT_GridSlot'"));

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> GridDisplayMaterial(TEXT("/Script/Engine.Material'/Game/Materials/M_Atlas.M_Atlas'"));


	GridSelection->SetStaticMesh(PlaneMesh.Object);
	GridSelection->SetMaterial(0, GridMaterial.Object);
	GridSelection->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//GridSelectionDisplay->SetStaticMesh(TileTypes[CurrentTileIndex]->InstancedMesh->GetStaticMesh());
	SelectedShow->SetMaterial(0, GridDisplayMaterial.Object);
	SelectedShow->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void ATileGameManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (auto PlayerController = Cast<ATilePlayerController>(GWorld->GetFirstPlayerController()))
	{
		PlayerController->GameManager = this;
	}
	SelectedShow->SetStaticMesh(TileTypes[CurrentTileIndex]->InstancedMesh->GetStaticMesh());

	
}

// Called every frame
void ATileGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileGameManager::OnActorInteraction(AActor* HitActor, FVector& Location, bool IsPressed)
{
	//No tile types?
	if (TileTypes.Num() == 0) return;

	FVector GridLoc = GridOffset;
	GridLoc.X = FMath::GridSnap(Location.X, GridSize);
	GridLoc.Y = FMath::GridSnap(Location.Y, GridSize);
	GridLoc.Z = Location.Z;

	UPlayerInput* KeyInput = GWorld->GetFirstPlayerController()->PlayerInput;

	
	if (KeyInput->WasJustPressed(EKeys::LeftMouseButton))
	{
		int GridX = GridLoc.X / GridSize + MapExtendsInGrids;
		int GridY = GridLoc.Y / GridSize + MapExtendsInGrids;

		if (GridX <0 || GridY < 0 || GridX >= MapExtendsInGrids*2 || GridY >= MapExtendsInGrids*2)
		{
			//Can not place ot of the grid
			return;
		}

		//Already a tile here?
		if (Map[GridX][GridY] != nullptr) return;

		if (TileTypes.IsValidIndex(CurrentTileIndex))
		{
			ATileBase* SelectedTile = TileTypes[CurrentTileIndex];
			Map[GridX][GridY] = SelectedTile;

			FTransform TileTransform(GridLoc + GridOffset);
			TileTransform = FTransform(FRotator(0, RotationIndex * 90, 0), TileTransform.GetLocation(), TileTransform.GetScale3D());
			SelectedTile->InstancedMesh->AddInstance(SelectedTile->InstancedMesh->GetRelativeTransform() * TileTransform, true);
	

		}
		
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s - %f, %f, %f"), HitActor ? *HitActor->GetActorLabel() : TEXT("None"), Location.X, Location.Y, Location.Z);
	}
	else if (KeyInput->WasJustPressed(EKeys::MouseScrollDown))
	{
		CurrentTileIndex = (CurrentTileIndex + 1) % TileTypes.Num();
		

		SelectedShow->SetStaticMesh(TileTypes[CurrentTileIndex]->InstancedMesh->GetStaticMesh());
	}
	else if (KeyInput->WasJustPressed(EKeys::MouseScrollUp))
	{
		CurrentTileIndex = (CurrentTileIndex - 1) % TileTypes.Num();

		if (CurrentTileIndex<0)
		{
			CurrentTileIndex = TileTypes.Num() - 1;
		}
		

		SelectedShow->SetStaticMesh(TileTypes[CurrentTileIndex]->InstancedMesh->GetStaticMesh());
	}
	else
	{
		GridSelection->SetWorldLocation(GridLoc + GridOffset);
		SelectedShow->SetWorldLocation(GridLoc + GridOffset);
	}

	if (KeyInput->WasJustPressed(EKeys::RightMouseButton))
	{
		AddActorLocalRotation(FRotator(0,90,0), false, 0, ETeleportType::None);
		RotationIndex++;
		if (RotationIndex == 4) RotationIndex = 0;
	}
}