// Fill out your copyright notice in the Description page of Project Settings.


#include "King.h"

void AKing::DestroySelfActor()
{
	Super::DestroySelfActor();

	UE_LOG(LogTemp, Log, TEXT("GAME OVER!"));
}