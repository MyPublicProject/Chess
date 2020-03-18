// Fill out your copyright notice in the Description page of Project Settings.


#include "OrdinarySoldier.h"
#include "SpawnGameModeBase.h"
#include "Dot.h"


void AOrdinarySoldier::GetWalkerLocation() 
{
	GetSpawnAllDot();
}


//“兵”的判断条件
void AOrdinarySoldier::SetWalkerLocation()
{
	TrueWalkerLocation = NullTrueWalkerLocation;

	GetDotLocation = GetActorLocation();

	//@ Plyer 1  // GetDotLocation.Y <= 4000 判断是否过河

	if (WaveState == EWaveSrare::TheRedTeam)
	{
		if (GetDotLocation.Y <= 4000)
		{
			GetDotLocation.Y += 1000;

			OrdinaryLocaion(GetDotLocation);

			return;
		}

		if (GetDotLocation.Y > 4000)
		{
			GetDotLocation.Y += 1000; OrdinaryLocaion(GetDotLocation);
			GetDotLocation.X += 1000; OrdinaryLocaion(GetDotLocation);
			GetDotLocation.X -= 1000; OrdinaryLocaion(GetDotLocation);
		}
	}

	//@ Plyer 2  // GetDotLocation.Y <= 4000 判断是否过河

	if (WaveState == EWaveSrare::TheBlackTeam)
	{
		if (GetDotLocation.Y > 4000)
		{
			GetDotLocation.Y -= 1000;

			OrdinaryLocaion(GetDotLocation);

			return;
		}

		if (GetDotLocation.Y <= 4000)
		{
			GetDotLocation.Y -= 1000; OrdinaryLocaion(GetDotLocation);
			GetDotLocation.X += 1000; OrdinaryLocaion(GetDotLocation);
			GetDotLocation.X -= 1000; OrdinaryLocaion(GetDotLocation);
		}
	}
}


void AOrdinarySoldier::OrdinaryLocaion(FVector NewLocation)
{
	TureWave(NewLocation);
	GetDotLocation = GetActorLocation();
}


void AOrdinarySoldier::TureWave(FVector TureLocation)
{
	if (AllWalkerDotLocation.Find(TureLocation, GeneraIndex))
	{
		if (!Cast<ADot>(AllWalkerDot[GeneraIndex])->TrueWaveState(WaveState))
		{
			TrueWalkerLocation.Add(TureLocation);
		}
	}
}
