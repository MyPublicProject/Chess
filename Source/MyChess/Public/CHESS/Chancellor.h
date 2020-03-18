// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CHESS/General.h"
#include "Chancellor.generated.h"

/**
 * 
 */
UCLASS()
class MYCHESS_API AChancellor : public AGeneral
{
	GENERATED_BODY()

private:

	virtual void GetWalkerLocation() override;

	virtual void MobileCondition(int MyIndex) override;
};
