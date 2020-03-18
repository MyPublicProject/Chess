// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CHESS/General.h"
#include "King.generated.h"

/**
 * 
 */
UCLASS()
class MYCHESS_API AKing : public AGeneral
{
	GENERATED_BODY()
	
public:
	// ɾ���Լ�
	virtual void DestroySelfActor() override;
};
