// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

#include "TBPlayerController.h"
#include "Commands/MoveCommand.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AGameManager::OnActorClicked(AActor* Actor, FKey button)
{
	//Hala daha command çalıştırıyosa
	if (CurrentCommand.IsValid()&&CurrentCommand->IsExecuting())return;

	AAGameSlot*Slot=Cast<AAGameSlot>(Actor);

	//Clicked on a non slot actor
	if (!Slot)return;

	//Player bastıysa

	if (!ThePLayer)
	{
		UE_LOG(LogTemp,Error,TEXT("No Player Unit Detected"))
		return;
	}

	//Boş slot varsa move command i player için
	if (Slot->Unit ==nullptr)
	{
		//Oyuncuyu hareket ettir
		TSharedRef<MoveCommand> Cmd=
			MakeShared<MoveCommand>(ThePLayer->Slot->GridPosition,Slot->GridPosition);
		CommandPool.Add(Cmd);
		Cmd->Execute();
		CurrentCommand = Cmd;
	}


	
}

void AGameManager::CreateLevelActors(FSLevelInfo& Info)
{
	ThePLayer=nullptr;

	for (auto UnitInfo : Info.Units)
	{
		if (AAGameSlot*Slot =GameGrid->GetSlot(UnitInfo.StartPosition))
		{
			Slot->SpawnUnitHere(UnitInfo.UnitClass);
			if (Slot->Unit && Slot ->Unit->IsControlledByThePlayer())
			{
				ThePLayer=Slot->Unit;
			}
		}
		
	}
}

bool AGameManager::UndoLastMove()
{
	if (CommandPool.Num() < 1)
	{
		return false;

	}

	TSharedRef<Commend> Cmd  = CommandPool.Pop();
	Cmd->Revert();
	CurrentCommand = Cmd;
	return true;

}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	if (auto PlayerController =GWorld->GetFirstPlayerController<ATBPlayerController>())
		
	{

		PlayerController->GameManager =this;
	}

	if (Levels.IsValidIndex(CurrentLevel))
	{
		CreateLevelActors(Levels[CurrentLevel]);
	}
	
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentCommand.IsValid())
	{
		CurrentCommand->Update(DeltaTime);
	}

}



