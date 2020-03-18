// Fill out your copyright notice in the Description page of Project Settings.


#include "FillAnOffice.h"
#include "Dot.h"

// ���ˡ����ж�����
void AFillAnOffice::MobileCondition(int MyIndex)
{
	if (One1 == 1000 && Two2 == 1000 && AllWalkerDotLocation.Find(WalkerDotLocation[MyIndex], GeneraIndex))
	{
		if (!Cast<ADot>(AllWalkerDot[GeneraIndex])->TrueWaveState(WaveState))
		{
			TrueWalkerLocation.Add(WalkerDotLocation[MyIndex]);
		}
	}
}
