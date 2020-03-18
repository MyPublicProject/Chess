// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CHESS/General.h"
#include "Cannon.generated.h"

class ADot;

/**
 * 
 */
UCLASS()
class MYCHESS_API ACannon : public AGeneral
{
	GENERATED_BODY()

private:

	// ÅÚ´ò¸ôÉ½Å£

	virtual void GetWalkerLocation() override;

	virtual void SetWalkerLocation() override;

	// É½
	void CannonWaveState(FVector NewLocation);

	// Å£
	void TargetCannonWaveState(FVector NewLocation);

	bool CannonTrue;

	bool NiuCannonTrue;

	void Cannon(FVector NewLocation);

	void InitializationVariable();
};
