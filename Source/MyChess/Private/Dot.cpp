#include "Dot.h"
#include "General.h"
#include "Components/SphereComponent.h"
#include "Materials/MaterialInterface.h"


// Sets default values
ADot::ADot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticComp"));
	StaticComp->SetWorldScale3D({ 0.5,0.5,0.5 });
	RootComponent = StaticComp;
	if (BeginMaterial){StaticComp->SetMaterial(0, BeginMaterial);}
}


// Called when the game starts or when spawned
void ADot::BeginPlay()
{
	Super::BeginPlay();
}


void ADot::SetMateryals()
{
	StaticComp->SetWorldScale3D({ 3,3,3 });
	if (Material)
	{
		StaticComp->SetMaterial(0, Material);
	}
}


void ADot::SetBeginMateryals()
{
	StaticComp->SetWorldScale3D({ 0.5,0.5,0.5 });
	if (BeginMaterial)
	{
		StaticComp->SetMaterial(0, BeginMaterial);
	}
}


void ADot::SetWaveState(EWaveSrare NewState)
{
	WaveState = NewState;
}


bool ADot::TrueWaveState(EWaveSrare TureState)
{
	if (WaveState == TureState)
	{
		return true;
	}
	else
	{
		return false;
	}
}
