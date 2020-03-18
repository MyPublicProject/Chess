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

	// �ڴ��ɽţ

	virtual void GetWalkerLocation() override;

	virtual void SetWalkerLocation() override;

	// ɽ
	void CannonWaveState(FVector NewLocation);

	// ţ
	void TargetCannonWaveState(FVector NewLocation);

	bool CannonTrue;

	bool NiuCannonTrue;

	void Cannon(FVector NewLocation);

	void InitializationVariable();
};
