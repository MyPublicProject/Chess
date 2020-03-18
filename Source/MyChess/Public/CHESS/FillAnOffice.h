// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CHESS/General.h"
#include "FillAnOffice.generated.h"

/**
 * 
 */
UCLASS()
class MYCHESS_API AFillAnOffice : public AGeneral
{
	GENERATED_BODY()
	
private:

	virtual void MobileCondition(int MyIndex) override;

};
