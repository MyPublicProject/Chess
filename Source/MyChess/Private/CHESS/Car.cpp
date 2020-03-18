// Fill out your copyright notice in the Description page of Project Settings.


#include "Car.h"
#include "Dot.h"
#include "SpawnGameModeBase.h"


void ACar::GetWalkerLocation()
{
	ASpawnGameModeBase* GM = GetWorld()->GetAuthGameMode<ASpawnGameModeBase>();

	WalkerDotLocation = GM->AllLocation;

	AllWalkerDot = GM->AllSpawnActor;
}


//���������ж�����
void ACar::SetWalkerLocation()
{
	// ��տ��ƶ�λ������
	TrueWalkerLocation = NullTrueWalkerLocation;

	// GetActorLocation()�������ҷֱ��ж�
	CarTrue = true;LDotLocation = GetActorLocation();
	while (CarTrue)
	{
		LDotLocation.X -= 1000;
		CarWaveState(LDotLocation);
	}

	CarTrue = true;LDotLocation = GetActorLocation();
	while (CarTrue)
	{
		LDotLocation.X += 1000;
		CarWaveState(LDotLocation);
	}

	CarTrue = true;LDotLocation = GetActorLocation();
	while (CarTrue)
	{
		LDotLocation.Y -= 1000;
		CarWaveState(LDotLocation);
	}

	CarTrue = true;LDotLocation = GetActorLocation();
	while (CarTrue)
	{
		LDotLocation.Y += 1000;
		CarWaveState(LDotLocation);
	}
}


// ����ר���жϺ���
void ACar::CarWaveState(FVector NewLocation)
{
	if (WalkerDotLocation.Find(NewLocation, GeneraIndex))
	{
		if (Cast<ADot>(AllWalkerDot[GeneraIndex])->TrueWaveState(EWaveSrare::Looker))
		{
			TrueWalkerLocation.Add(WalkerDotLocation[GeneraIndex]);
			return;
		}
		else if (!Cast<ADot>(AllWalkerDot[GeneraIndex])->TrueWaveState(WaveState))
		{
			TrueWalkerLocation.Add(WalkerDotLocation[GeneraIndex]);
			CarTrue = false;
			return;
		}
		else
		{
			CarTrue = false;
			return;
		}
	}
	else 
	{
		CarTrue = false;
	}
}
