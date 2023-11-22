// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Commend.h"

/**
 * 
 */
class MoveCommand :public Commend
{
public:
	MoveCommand(FSGridPosition Src,FSGridPosition Dst);
	~MoveCommand();

	virtual void Execute() override;
	virtual void Revert() override;

	UPROPERTY(EditAnywhere)
	


private:
	FSGridPosition Source, Destination;
};
