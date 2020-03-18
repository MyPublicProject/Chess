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


// ���ڡ����ж�����
void ACannon::SetWalkerLocation()
{
	// ��տ��ƶ�λ������
	TrueWalkerLocation = NullTrueWalkerLocation;

	// GetActorLocation()�������ҷֱ��ж�

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


// ɽ
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


// ţ
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


// �����ĵ���
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


// ��ʼ������
void ACannon::InitializationVariable()
{
	CannonTrue = true; 
	NiuCannonTrue = true;
	LDotLocation = GetActorLocation();
}
