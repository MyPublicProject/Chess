// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CHESS/General.h"
#include "Car.generated.h"

class ADot;
/**
 * 
 */
UCLASS()
class MYCHESS_API ACar : public AGeneral
{
	GENERATED_BODY()

private:

	virtual void GetWalkerLocation() override;

	virtual void SetWalkerLocation() override;

	void CarWaveState(FVector NewLocation);

	bool CarTrue;
};
