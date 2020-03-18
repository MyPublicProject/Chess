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


// 生成棋盘
void ASpawnGameModeBase::GetSpawnDotLocation()
{
	FVector Origin = { 0,0,0 };

	// X
	for (int i = 0; i < 9; i++)
	{
		Origin.X = i * SpaceBetween;

		for (int x = 0; x < 10; x++)
		{
			// 获得生成位置
			Origin.Y = x * SpaceBetween;

			AllLocation.Add(Origin);

			// 生成原点
			FActorSpawnParameters SpawnParams;

			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			CurrentDot = GetWorld()->SpawnActor<ADot>(StarterDotClass, Origin, FRotator::ZeroRotator, SpawnParams);

			if (CurrentDot)
			{
				// 不启用类的碰撞
				// CurrentDot->SetActorEnableCollision(false);

				CurrentDot->DotLocation = Origin;

				// CurrentDot->SetMateryals();

				AllSpawnActor.Add(CurrentDot);
			}
		}
	}
	SpawnChessClass();
}


// 生成象棋
void ASpawnGameModeBase::SpawnChessClass()
{
	// 生成象棋的位置 Red
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

			// 添加到数组里
			RedChess.Add(SpawnGeneralActor);
			RedAndBlackChess.Add(SpawnGeneralActor);

			// 设置象棋本身的队列
			SpawnGeneralActor->SetWaveState(EWaveSrare::TheRedTeam);

			// 设置生成象棋位置点的队列
			if (AllLocation.Find(SpawnOriginsOne[i],Index))
			{
				Cast<ADot>(AllSpawnActor[Index])->SetWaveState(EWaveSrare::TheRedTeam);
			}

			// Black
			SpawnGeneralActor = GetWorld()->SpawnActor<AGeneral>(SpawnClass[i], SpawnOriginsTwo[i], FRotator::ZeroRotator, SpawnGeneral);

			// 添加到数组里
			BlackChess.Add(SpawnGeneralActor);
			RedAndBlackChess.Add(SpawnGeneralActor);

			// 设置象棋本身的队列
			SpawnGeneralActor->SetWaveState(EWaveSrare::TheBlackTeam);

			// 设置生成象棋位置点的队列
			if (AllLocation.Find(SpawnOriginsTwo[i], Index))
			{
				Cast<ADot>(AllSpawnActor[Index])->SetWaveState(EWaveSrare::TheBlackTeam);
			}
		}
	}
}


// 显示可移动的位置
void ASpawnGameModeBase::GetTureWalkerLocation(AGeneral* CurrentGeneral)
{
	InitializeSetBeginMateryals();
	// 设置可以位置的材质
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


// 移动象棋
void ASpawnGameModeBase::SetWalkerLocation(AGeneral* CurrentGeneral,FVector SetCurrentGeneral,ADot* SerWalkerDot)
{
	// 判断要移动的点是否为可移动位置
	if (CurrentGeneral && CurrentGeneral->TrueWalkerLocation.Find(SetCurrentGeneral) != -1)
	{
		// 移动后把原来的位置设置为 Looker
		if (AllLocation.Find(CurrentGeneral->GetActorLocation(),Index))
		{
			// 移动之前的点
			Cast<ADot>(AllSpawnActor[Index])->SetWaveState(EWaveSrare::Looker);

			// 移动后的点
			SerWalkerDot->SetWaveState(CurrentGeneral->GetWaveState());

		}

		// 删除要移动位置的象棋
		DelayerChess(SetCurrentGeneral);

		// 设置象棋位置，在这里判断移动的位置是否有象棋
		CurrentGeneral->SetActorLocation(SetCurrentGeneral);

		// 成功设置位置
		NotNoll = true;

		InitializeSetBeginMateryals();
	}
}


//  初始化点的材质
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


// 删除要移动位置的象棋
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
