// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayChessPawn.generated.h"

enum class EWaveSrare : uint8;

class ASpawnGameModeBase;

UCLASS()
class APlayChessPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayChessPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USkeletalMeshComponent* SkeletaMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCameraComponent* CameraComp;


	FName CameraTransform;

	FVector CameraLocation; 

	FRotator CameraRotation;

	FVector GetCameraStartLocation;

	FVector GetCameraEndLocation;
 
 	FCollisionQueryParams QueryParams;
 
	class ADot* WalkerDot;

	class AGeneral* CastGeneral;

 	void MouseRight();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameState")
	EWaveSrare WaveState;
};
