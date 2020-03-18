// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpawnGameModeBase.generated.h"


class ADot;
class AGeneral;
class APlayChessPawn;


UCLASS()
class MYCHESS_API ASpawnGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	void GetSpawnDotLocation();

	class ADot* CurrentDot;

	UPROPERTY(EditDefaultsOnly, Category = "Dot")
	TSubclassOf<ADot> StarterDotClass; 

	UPROPERTY(EditDefaultsOnly, Category = "Dot")
	int SpaceBetween; 

protected:

 	// class AGeneral* CurrentGeneral;
 
	// 	UPROPERTY(EditDefaultsOnly, Category = "General")
	// 	TSubclassOf<APlayChessPawn> GeneralPlayer;

	/*APlayChessPawn* MyPlayerPawn;*/

	UPROPERTY(EditDefaultsOnly, Category = "General")
	TSubclassOf<AGeneral> StarterGeneralClass;

	UPROPERTY(EditDefaultsOnly, Category = "General")
	TSubclassOf<AGeneral> StarterFillAnOfficeClass;

	UPROPERTY(EditDefaultsOnly, Category = "General")
	TSubclassOf<AGeneral> StarterChancellorClass;

	UPROPERTY(EditDefaultsOnly, Category = "General")
	TSubclassOf<AGeneral> StarterHorseClass;

	UPROPERTY(EditDefaultsOnly, Category = "General")
	TSubclassOf<AGeneral> StarterCarClass;

	UPROPERTY(EditDefaultsOnly, Category = "General")
	TSubclassOf<AGeneral> StarterCannonClass;

	UPROPERTY(EditDefaultsOnly, Category = "General")
	TSubclassOf<AGeneral> StarterOrdinarySoldierClass;

	void SpawnChessClass();

	AGeneral* SpawnGeneralActor;

	int32 Index;

public:

	TArray<FVector> AllLocation;

	TArray<ADot*> AllSpawnActor;

	void GetTureWalkerLocation(AGeneral* CurrentGeneral);

	void SetWalkerLocation(AGeneral* CurrentGeneral, FVector SetCurrentGeneral, ADot* SerWalkerDot);
	
	void InitializeSetBeginMateryals();

	bool NotNoll;

protected:

	void DelayerChess(FVector NewLocation);

	TArray<AGeneral*> RedChess;

	TArray<AGeneral*> BlackChess;

	TArray<AGeneral*> RedAndBlackChess;

};
