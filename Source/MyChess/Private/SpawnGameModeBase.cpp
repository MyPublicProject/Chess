// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnGameModeBase.h"
#include "Containers/Array.h"
#include "PlayChessPawn.h"
#include "General.h"
#include "Dot.h"



void ASpawnGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SpaceBetween = 1000;

	GetSpawnDotLocation();

	NotNoll = false;
}


// ��������
void ASpawnGameModeBase::GetSpawnDotLocation()
{
	FVector Origin = { 0,0,0 };

	// X
	for (int i = 0; i < 9; i++)
	{
		Origin.X = i * SpaceBetween;

		for (int x = 0; x < 10; x++)
		{
			// �������λ��
			Origin.Y = x * SpaceBetween;

			AllLocation.Add(Origin);

			// ����ԭ��
			FActorSpawnParameters SpawnParams;

			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			CurrentDot = GetWorld()->SpawnActor<ADot>(StarterDotClass, Origin, FRotator::ZeroRotator, SpawnParams);

			if (CurrentDot)
			{
				// �����������ײ
				// CurrentDot->SetActorEnableCollision(false);

				CurrentDot->DotLocation = Origin;

				// CurrentDot->SetMateryals();

				AllSpawnActor.Add(CurrentDot);
			}
		}
	}
	SpawnChessClass();
}


// ��������
void ASpawnGameModeBase::SpawnChessClass()
{
	// ���������λ�� Red
	TArray<FVector> SpawnOriginsOne = { { 0, 0, 0 },{ 1000, 0, 0 },{ 2000, 0, 0 },{ 3000, 0, 0 },{ 4000, 0, 0 },{ 5000, 0, 0 },{ 6000, 0, 0 },{ 7000, 0, 0 },{ 8000, 0, 0 },{ 1000, 2000, 0 },{ 7000, 2000, 0 },{ 0, 3000, 0 },{ 2000, 3000, 0 },{ 4000, 3000, 0 },{ 6000, 3000, 0 },{ 8000, 3000, 0 } };

	// Black
	TArray<FVector> SpawnOriginsTwo = { { 0, 9000, 0 },{ 1000, 9000, 0 },{ 2000, 9000, 0 },{ 3000, 9000, 0 },{ 4000, 9000, 0 },{ 5000, 9000, 0 },{ 6000, 9000, 0 },{ 7000, 9000, 0 },{ 8000, 9000, 0 },{ 1000, 7000, 0 },{ 7000, 7000, 0 },{ 0, 6000, 0 },{ 2000, 6000, 0 },{ 4000, 6000, 0 },{ 6000, 6000, 0 },{ 8000, 6000, 0 } };

	TArray<TSubclassOf<AGeneral>> SpawnClass = { StarterCarClass,StarterHorseClass,StarterChancellorClass,StarterFillAnOfficeClass,StarterGeneralClass,StarterFillAnOfficeClass ,StarterChancellorClass,StarterHorseClass,StarterCarClass,StarterCannonClass,StarterCannonClass,StarterOrdinarySoldierClass,StarterOrdinarySoldierClass,StarterOrdinarySoldierClass,StarterOrdinarySoldierClass,StarterOrdinarySoldierClass };

	// 	TArray<FVector> SpawnPlayPawn = { {4000,-2000,5000},{4000,11000,5000} };
	// 
	// 	TArray<EWaveSrare> SpawnWaveSrare = {EWaveSrare::TheRedTeam,EWaveSrare::TheBlackTeam};

	FActorSpawnParameters SpawnGeneral;

	SpawnGeneral.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// 	for (int i = 0; i < SpawnPlayPawn.Num(); i++)
	// 	{
	// 		MyPlayerPawn = GetWorld()->SpawnActor<APlayChessPawn>(GeneralPlayer, SpawnPlayPawn[i], FRotator::ZeroRotator, SpawnGeneral);
	// 		MyPlayerPawn->WaveState = SpawnWaveSrare[i];
	// 	}
	
	if (SpawnOriginsOne.Num() == SpawnClass.Num())
	{
		for (int i = 0; i < SpawnOriginsOne.Num(); i++)
		{
			// Red
			SpawnGeneralActor = GetWorld()->SpawnActor<AGeneral>(SpawnClass[i], SpawnOriginsOne[i], FRotator::ZeroRotator, SpawnGeneral);

			// ��ӵ�������
			RedChess.Add(SpawnGeneralActor);
			RedAndBlackChess.Add(SpawnGeneralActor);

			// �������屾��Ķ���
			SpawnGeneralActor->SetWaveState(EWaveSrare::TheRedTeam);

			// ������������λ�õ�Ķ���
			if (AllLocation.Find(SpawnOriginsOne[i],Index))
			{
				Cast<ADot>(AllSpawnActor[Index])->SetWaveState(EWaveSrare::TheRedTeam);
			}

			// Black
			SpawnGeneralActor = GetWorld()->SpawnActor<AGeneral>(SpawnClass[i], SpawnOriginsTwo[i], FRotator::ZeroRotator, SpawnGeneral);

			// ��ӵ�������
			BlackChess.Add(SpawnGeneralActor);
			RedAndBlackChess.Add(SpawnGeneralActor);

			// �������屾��Ķ���
			SpawnGeneralActor->SetWaveState(EWaveSrare::TheBlackTeam);

			// ������������λ�õ�Ķ���
			if (AllLocation.Find(SpawnOriginsTwo[i], Index))
			{
				Cast<ADot>(AllSpawnActor[Index])->SetWaveState(EWaveSrare::TheBlackTeam);
			}
		}
	}
}


// ��ʾ���ƶ���λ��
void ASpawnGameModeBase::GetTureWalkerLocation(AGeneral* CurrentGeneral)
{
	InitializeSetBeginMateryals();
	// ���ÿ���λ�õĲ���
	if (CurrentGeneral)
	{
		for (int i = 0; i < CurrentGeneral->TrueWalkerLocation.Num(); i++)
		{
			for (int j = 0; j < AllLocation.Num(); j++)
			{
				if (CurrentGeneral->TrueWalkerLocation[i] == AllLocation[j])
				{
					ADot* AD = Cast<ADot>(AllSpawnActor[j]);
					if (AD)
					{
						AD->SetMateryals();
					}
				}
			}
	 	}
	}
}


// �ƶ�����
void ASpawnGameModeBase::SetWalkerLocation(AGeneral* CurrentGeneral,FVector SetCurrentGeneral,ADot* SerWalkerDot)
{
	// �ж�Ҫ�ƶ��ĵ��Ƿ�Ϊ���ƶ�λ��
	if (CurrentGeneral && CurrentGeneral->TrueWalkerLocation.Find(SetCurrentGeneral) != -1)
	{
		// �ƶ����ԭ����λ������Ϊ Looker
		if (AllLocation.Find(CurrentGeneral->GetActorLocation(),Index))
		{
			// �ƶ�֮ǰ�ĵ�
			Cast<ADot>(AllSpawnActor[Index])->SetWaveState(EWaveSrare::Looker);

			// �ƶ���ĵ�
			SerWalkerDot->SetWaveState(CurrentGeneral->GetWaveState());

		}

		// ɾ��Ҫ�ƶ�λ�õ�����
		DelayerChess(SetCurrentGeneral);

		// ��������λ�ã��������ж��ƶ���λ���Ƿ�������
		CurrentGeneral->SetActorLocation(SetCurrentGeneral);

		// �ɹ�����λ��
		NotNoll = true;

		InitializeSetBeginMateryals();
	}
}


//  ��ʼ����Ĳ���
void ASpawnGameModeBase::InitializeSetBeginMateryals()
{
	for (int x = 0; x < AllLocation.Num(); x++)
	{
		ADot* AD = Cast<ADot>(AllSpawnActor[x]);
		if (AD)
		{
			AD->SetBeginMateryals();
		}
	}
}


// ɾ��Ҫ�ƶ�λ�õ�����
void ASpawnGameModeBase::DelayerChess(FVector NewLocation)
{
	for (int i = 0; i < RedAndBlackChess.Num(); i++)
	{
		if (Cast<AGeneral>(RedAndBlackChess[i])->GetActorLocation() == NewLocation)
		{
			Cast<AGeneral>(RedAndBlackChess[i])->DestroySelfActor();

			RedAndBlackChess.SetNum(i);
		}
	}
}
