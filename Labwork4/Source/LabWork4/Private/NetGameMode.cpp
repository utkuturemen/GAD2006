// Fill out your copyright notice in the Description page of Project Settings.


#include "NetGameMode.h"
#include "NetBaseCharacter.h"


ANetGameModeBase::ANetGameModeBase()
{
	DefaultPawnClass = ANetBaseCharacter::StaticClass();
}