// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CHESS/General.h"
#include "OrdinarySoldier.generated.h"

class ADot;
class ASpawnGameModeBase;
/**
 * 
 */
UCLASS()
class MYCHESS_API AOrdinarySoldier : public AGeneral
{
	GENERATED_BODY()

private:

	virtual void GetWalkerLocation() override;

	virtual void SetWalkerLocation() override;

	void OrdinaryLocaion(FVector NewLocation);

	void TureWave(FVector TureLocation);
};
