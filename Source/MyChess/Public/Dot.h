// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Dot.generated.h"

enum class EWaveSrare : uint8;

UCLASS()
class MYCHESS_API ADot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADot();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MeshComp")
	class UStaticMeshComponent* StaticComp;

	UPROPERTY(EditDefaultsOnly, Category = "Material")
	class UMaterialInterface* BeginMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Material")
	class UMaterialInterface* Material;
	
public:

	FVector DotLocation;

	void SetMateryals();

	void SetBeginMateryals();

protected:

	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	EWaveSrare WaveState;

public:

	void SetWaveState(EWaveSrare NewState);

	bool TrueWaveState(EWaveSrare TureState);

};
