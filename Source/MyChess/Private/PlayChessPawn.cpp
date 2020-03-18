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



// ����Ҽ�����¼����ȴ���Ҫ�ƶ������壬���ж��ƶ���λ��
void APlayChessPawn::MouseRight()
{
	ASpawnGameModeBase* GM = GetWorld()->GetAuthGameMode<ASpawnGameModeBase>();

	// CameraComp->GetOwner()->GetActorEyesViewPoint(CameraLocation, CameraRotation);

	// ��ÿ������������λ�úͽǶ�
	CameraComp->GetSocketWorldLocationAndRotation(CameraTransform, CameraLocation, CameraRotation);

	// ���߳���
	GetCameraStartLocation = CameraLocation;
	GetCameraEndLocation = CameraLocation + CameraRotation.Vector() * 20000;

	// ������ײ�ж�
	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, GetCameraStartLocation, GetCameraEndLocation, COLLISION_WEAPON, QueryParams);
	DrawDebugLine(GetWorld(), GetCameraStartLocation, GetCameraEndLocation, FColor::Red, false, 5.0f, 5, 0.0f);

	// ѡ�е�����
	if (Cast<AGeneral>(Hit.GetActor()))
	{
		CastGeneral = Cast<AGeneral>(Hit.GetActor());

		if (GM && CastGeneral->GetWaveState() == WaveState)
		{
			// ���¿��ƶ���λ��
			CastGeneral->OperationSetWalkerLocation();

			// ��ʾ���ƶ���λ��
			GM->GetTureWalkerLocation(CastGeneral);

			UE_LOG(LogTemp, Log, TEXT("%s"), *CastGeneral->GetName());
		}
	}

	// Ҫ�ƶ��ĵ�
	if (Cast<ADot>(Hit.GetActor()))
	{
		WalkerDot = Cast<ADot>(Hit.GetActor());

		if (GM && CastGeneral)
		{
			// GmaeMode �ƶ�λ��
			GM->SetWalkerLocation(CastGeneral, WalkerDot->DotLocation, WalkerDot);

			// �ɹ��ƶ�ʱ����ѡ�е������������Ϊ��
			if (GM->NotNoll)
			{
				CastGeneral = nullptr;

				GM->NotNoll = false;
			}
			UE_LOG(LogTemp, Log, TEXT("%s"), *WalkerDot->GetName());
		}
	}
}