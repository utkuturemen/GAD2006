// Fill out your copyright notice in the Description page of Project Settings.


#include "Commands/MoveCommand.h"

#include "AGameGrid.h"



MoveCommand::MoveCommand(FSGridPosition Src, FSGridPosition Dst) :
Source(Src),
	Destination(Dst)
{
	
}

MoveCommand::~MoveCommand()
{
}

void MoveCommand::Execute()
{
	UE_LOG(LogTemp,Warning,TEXT("Executing MoveCommand..."));
	AAGameSlot* SlotA = AAGameGrid :: FindSlot(Source);
	AAGameSlot* SlotB = AAGameGrid ::FindSlot(Destination);

	AUnitBase*UnitA =SlotA->Unit;
	check(UnitA);
	UnitA->AssignToSlot(SlotB);
	SlotB->SetState(GS_Highlighted);
	
}

void MoveCommand::Revert()
{


	UE_LOG(LogTemp, Warning, TEXT("Executing revert command..."));
	AAGameSlot* SlotA = AAGameGrid::FindSlot(Source);
	AAGameSlot* SlotB = AAGameGrid::FindSlot(Destination);

	AUnitBase* UnitA = SlotB->Unit;
	check(UnitA);
	UnitA->AssignToSlot(SlotA);
	SlotB->SetState(GS_Default);
}
