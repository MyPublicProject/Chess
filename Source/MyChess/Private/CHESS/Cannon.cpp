// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "SpawnGameModeBase.h"
#include "Dot.h"

void ACannon::GetWalkerLocation()
{
	ASpawnGameModeBase* GM = GetWorld()->GetAuthGameMode<ASpawnGameModeBase>();

	WalkerDotLocation = GM->AllLocation;

	AllWalkerDot = GM->AllSpawnActor;
}


// “炮”的判断条件
void ACannon::SetWalkerLocation()
{
	// 清空可移动位置数组
	TrueWalkerLocation = NullTrueWalkerLocation;

	// GetActorLocation()上下左右分别判断

	InitializationVariable();
	while (CannonTrue || NiuCannonTrue)
	{
		LDotLocation.X -= 1000;
		Cannon(LDotLocation);
	}

	InitializationVariable();
	while (CannonTrue || NiuCannonTrue)
	{
		LDotLocation.X += 1000;
		Cannon(LDotLocation);
	}

	InitializationVariable();
	while (CannonTrue || NiuCannonTrue)
	{
		LDotLocation.Y -= 1000;
		Cannon(LDotLocation);
	}

	InitializationVariable();
	while (CannonTrue || NiuCannonTrue)
	{
		LDotLocation.Y += 1000;
		Cannon(LDotLocation);
	}
}


// 山
void ACannon::CannonWaveState(FVector NewLocation)
{
	if (WalkerDotLocation.Find(NewLocation, GeneraIndex))
	{
		if (Cast<ADot>(AllWalkerDot[GeneraIndex])->TrueWaveState(EWaveSrare::Looker))
		{
			TrueWalkerLocation.Add(WalkerDotLocation[GeneraIndex]);
			return;
		}
		else
		{
			CannonTrue = false;
			return;
		}
	}
	else
	{
		CannonTrue = false;
	}
}


// 牛
void ACannon::TargetCannonWaveState(FVector NewLocation)
{

		if (WalkerDotLocation.Find(NewLocation, GeneraIndex))
		{
			if (Cast<ADot>(AllWalkerDot[GeneraIndex])->TrueWaveState(EWaveSrare::Looker))
			{
				return;
			}
			else if (!Cast<ADot>(AllWalkerDot[GeneraIndex])->TrueWaveState(WaveState))
			{
				TrueWalkerLocation.Add(WalkerDotLocation[GeneraIndex]);
				NiuCannonTrue = false;
				return;
			}
			else
			{
				NiuCannonTrue = false;
				return;
			}
		}
		else
		{
			NiuCannonTrue = false;
		}
}


// 函数的调用
void ACannon::Cannon(FVector NewLocation)
{
	if (CannonTrue && NiuCannonTrue)
	{
		CannonWaveState(NewLocation);
		return;
	}
	if (!CannonTrue && NiuCannonTrue)
	{
		TargetCannonWaveState(NewLocation);
	}
}


// 初始化变量
void ACannon::InitializationVariable()
{
	CannonTrue = true; 
	NiuCannonTrue = true;
	LDotLocation = GetActorLocation();
}
