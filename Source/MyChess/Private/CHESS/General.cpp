#include "General.h"
#include "SpawnGameModeBase.h"
#include "Components/StaticMeshComponent.h"
#include "Dot.h"


// Sets default values
AGeneral::AGeneral()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetWorldScale3D({ 2,2,0.3 });
	RootComponent = StaticMesh;
}


// Called when the game starts or when spawned
void AGeneral::BeginPlay()
{
	Super::BeginPlay();
}


void AGeneral::GetWalkerLocation()
{
	int X[3] = { -1,1,0 };

	int Y[3] = { 0,1,2 };

	//@ Player1
	if (WaveState == EWaveSrare::TheRedTeam)
	{	
		GetDotLocation = { 4000,0,0 };

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				LDotLocation.X = GetDotLocation.X + (X[i] * 1000);

				LDotLocation.Y = GetDotLocation.Y + (Y[j] * 1000);

				WalkerDotLocation.Add(LDotLocation);
			}
		}
	}

	//@ Player2
	if (WaveState == EWaveSrare::TheBlackTeam)
	{
		GetDotLocation = { 4000,9000,0 };

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				LDotLocation.X = GetDotLocation.X + (X[i] * 1000);

				LDotLocation.Y = GetDotLocation.Y - (Y[j] * 1000);

				WalkerDotLocation.Add(LDotLocation);
			}
		}
	}

	GetSpawnAllDot();
}


// 获得可移动的位置
void AGeneral::SetWalkerLocation()
{
	TrueWalkerLocation = NullTrueWalkerLocation;

	//@ Player 1 and Player 2
	for (int i = 0; i < WalkerDotLocation.Num(); i++)
	{
		One1 = GetActorLocation().X - WalkerDotLocation[i].X;
		Two2 = GetActorLocation().Y - WalkerDotLocation[i].Y;

		if (One1 < 0){One1 *= -1;}

		if (Two2 < 0){Two2 *= -1;}

		MobileCondition(i);
	}
}


// “帅”的判断条件，继承修改
void AGeneral::MobileCondition(int MyIndex)
{
	if (One1 + Two2 == 1000 && AllWalkerDotLocation.Find(WalkerDotLocation[MyIndex], GeneraIndex))
	{
		if (!Cast<ADot>(AllWalkerDot[GeneraIndex])->TrueWaveState(WaveState))
		{
			TrueWalkerLocation.Add(WalkerDotLocation[MyIndex]);
		}
	}
}


// 在 PlayChessPawn 中调用，右键点击更新可移动的位置
void AGeneral::OperationSetWalkerLocation()
{
	SetWalkerLocation();
}


// 设置阵营
void AGeneral::SetWaveState(EWaveSrare NewState)
{
	WaveState = NewState;

	GetWalkerLocation();
}


EWaveSrare AGeneral::GetWaveState()
{
	return WaveState;
}


void AGeneral::GetSpawnAllDot()
{
	ASpawnGameModeBase* GM = GetWorld()->GetAuthGameMode<ASpawnGameModeBase>();

	AllWalkerDot = GM->AllSpawnActor;

	AllWalkerDotLocation = GM->AllLocation;
}


void AGeneral::DestroySelfActor()
{
	Destroy();
}
