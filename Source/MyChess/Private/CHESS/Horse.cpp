// Fill out your copyright notice in the Description page of Project Settings.


#include "Horse.h"
#include "Dot.h"
#include "SpawnGameModeBase.h"


void AHorse::GetWalkerLocation()
{
	ASpawnGameModeBase* GM = GetWorld()->GetAuthGameMode<ASpawnGameModeBase>();

	WalkerDotLocation = GM->AllLocation;

	AllWalkerDot = GM->AllSpawnActor;;
}


// ���������ж�����
void AHorse::MobileCondition(int MyIndex)
{
	// ONE IF ��Ѱ�ҿ��ƶ��ĵ�
	// TWO IF �Ƿ����Լ��ӵ���
	// THERE and FIVE IF �ж��Ƿ�������

	if (One1 == 1000 && Two2 == 2000)
	{
		if (!Cast<ADot>(AllWalkerDot[MyIndex])->TrueWaveState(WaveState))
		{
			LDotLocation.X = GetActorLocation().X;
			LDotLocation.Y = (GetActorLocation().Y + WalkerDotLocation[MyIndex].Y) / 2;
			if (WalkerDotLocation.Find(LDotLocation, GeneraIndex))
			{
				if (Cast<ADot>(AllWalkerDot[GeneraIndex])->TrueWaveState(EWaveSrare::Looker))
				{
					TrueWalkerLocation.Add(WalkerDotLocation[MyIndex]);
				}
			}
		}
	}

	if (One1 == 2000 && Two2 == 1000)
	{
		if (!Cast<ADot>(AllWalkerDot[MyIndex])->TrueWaveState(WaveState))
		{
			LDotLocation.X = (GetActorLocation().X + WalkerDotLocation[MyIndex].X) / 2;
			LDotLocation.Y = GetActorLocation().Y;
			if (WalkerDotLocation.Find(LDotLocation, GeneraIndex))
			{
				if (Cast<ADot>(AllWalkerDot[GeneraIndex])->TrueWaveState(EWaveSrare::Looker))
				{
					TrueWalkerLocation.Add(WalkerDotLocation[MyIndex]);
				}
			}
		}
	}
}