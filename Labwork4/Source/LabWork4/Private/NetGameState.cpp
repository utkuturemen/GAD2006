// Fill out your copyright notice in the Description page of Project Settings.


#include "NetGameState.h"

ANetGameState::ANetGameState():
	WinningPlayer(-1)
{
	
}



void ANetGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&QuickLifeTimeProps) const
{
	Super::GetLifetimeReplicatedProps(QuickLifeTimeProps);
	DOREPLIFETIME(ANetGameState,WinningPlayer);
	
}
void ANetGameState::OnRep_Winner()
{
	if (WinningPlayer>0)
	{
		OnVictory();
	}
}

ANetPlayerState* ANetGameState::GetPlayerStateByIndex(int PlayerIndex)
{
	for (APlayerState*PS :PlayerArray)
	{
		ANetPlayerState*State =Cast<ANetPlayerState>(PS);
		if (State&&State->PlayerIndex == PlayerIndex)
		{
			return State;
		}
	}
	return nullptr;
}

void ANetGameState::TriggerRestart_Implementation()
{
	OnRestart();
}


