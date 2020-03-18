// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayChessPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CollisionQueryParams.h"
#include "SpawnGameModeBase.h"
#include "DrawDebugHelpers.h"
#include "CHESS/General.h"
#include "MyChess.h"
#include "Dot.h"


// Sets default values
APlayChessPawn::APlayChessPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletaMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletaMeshComp"));
	RootComponent = SkeletaMeshComp;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArm);

	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnPhysicalMaterial = true;
}


// Called when the game starts or when spawned
void APlayChessPawn::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void APlayChessPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// Called to bind functionality to input
void APlayChessPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("LookUp", this, &APlayChessPawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APlayChessPawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("MouseRight", IE_Pressed, this, &APlayChessPawn::MouseRight);
}



// 鼠标右键点击事件，先储存要移动的象棋，在判断移动的位置
void APlayChessPawn::MouseRight()
{
	ASpawnGameModeBase* GM = GetWorld()->GetAuthGameMode<ASpawnGameModeBase>();

	// CameraComp->GetOwner()->GetActorEyesViewPoint(CameraLocation, CameraRotation);

	// 获得控制器摄像机的位置和角度
	CameraComp->GetSocketWorldLocationAndRotation(CameraTransform, CameraLocation, CameraRotation);

	// 射线长度
	GetCameraStartLocation = CameraLocation;
	GetCameraEndLocation = CameraLocation + CameraRotation.Vector() * 20000;

	// 射线碰撞判断
	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, GetCameraStartLocation, GetCameraEndLocation, COLLISION_WEAPON, QueryParams);
	DrawDebugLine(GetWorld(), GetCameraStartLocation, GetCameraEndLocation, FColor::Red, false, 5.0f, 5, 0.0f);

	// 选中的象棋
	if (Cast<AGeneral>(Hit.GetActor()))
	{
		CastGeneral = Cast<AGeneral>(Hit.GetActor());

		if (GM && CastGeneral->GetWaveState() == WaveState)
		{
			// 更新可移动的位置
			CastGeneral->OperationSetWalkerLocation();

			// 显示可移动的位置
			GM->GetTureWalkerLocation(CastGeneral);

			UE_LOG(LogTemp, Log, TEXT("%s"), *CastGeneral->GetName());
		}
	}

	// 要移动的点
	if (Cast<ADot>(Hit.GetActor()))
	{
		WalkerDot = Cast<ADot>(Hit.GetActor());

		if (GM && CastGeneral)
		{
			// GmaeMode 移动位置
			GM->SetWalkerLocation(CastGeneral, WalkerDot->DotLocation, WalkerDot);

			// 成功移动时，把选中的象棋变量设置为空
			if (GM->NotNoll)
			{
				CastGeneral = nullptr;

				GM->NotNoll = false;
			}
			UE_LOG(LogTemp, Log, TEXT("%s"), *WalkerDot->GetName());
		}
	}
}