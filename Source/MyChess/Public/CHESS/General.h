// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "General.generated.h"

class ADot;

UENUM(BlueprintType)
enum class EWaveSrare : uint8
{
	Looker, // 观看者

	TheRedTeam,

	TheBlackTeam,
};


UCLASS()
class MYCHESS_API AGeneral : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AGeneral();

// 象棋移动的判断和函数
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MeshComp")
	class UStaticMeshComponent* StaticMesh;

	virtual void GetWalkerLocation();

	virtual void SetWalkerLocation();

	virtual void MobileCondition(int MyIndex);

	FVector GetDotLocation;

	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	FVector LDotLocation;

	int One1, Two2;

public:

	void OperationSetWalkerLocation();

	TArray<FVector> WalkerDotLocation;

	TArray<FVector> TrueWalkerLocation;

	TArray<FVector> NullTrueWalkerLocation;

// 判断阵营
protected:

	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	EWaveSrare WaveState;

public:

	void SetWaveState(EWaveSrare NewState);

	EWaveSrare GetWaveState();

	// 获的棋盘上所有点
	void GetSpawnAllDot();

	int32 GeneraIndex;

	TArray<ADot*> AllWalkerDot;

	TArray<FVector> AllWalkerDotLocation;

public:
	// 删除自己
	virtual void DestroySelfActor();

};