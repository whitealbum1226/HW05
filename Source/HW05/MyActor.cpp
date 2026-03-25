// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Engine/Engine.h"

// Sets default values
AMyActor::AMyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(0.f, 50.f, 0.f));
	// FVector 가 float 3개 묶은 좌표 타입

	StepCount = 0; // Tick 사용을 위한 기반
	MaxSteps = 10; // Tick 마무리를 위한 기반

	TotalDistance = 0.f;
	EventCount = 0;
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (StepCount < MaxSteps)
	{
		float RandomDistance = FMath::RandRange(100.f, 1000.f);
		// 랜덤 거리
		float RandomAngle = FMath::RandRange(-90.f, 90.f);
		// 랜덤 각도
		int RandomEvent = FMath::RandRange(0, 1);
		FVector PrevLocation = GetActorLocation();
		// 이동 직전 위치(거리 계산용)

		Move(RandomDistance);
		Turn(RandomAngle);

		FVector CurrentLocation = GetActorLocation();
		// 이동 직후 위치(거리 계산용)
		float Distance = FVector::Dist(PrevLocation, CurrentLocation);
		TotalDistance += Distance;

		if (RandomEvent == 1)
		{
			TriggerEvent();
			++EventCount;
		}

		PrintStatus(StepCount + 1);
		// StepCount + 1 값을 보내 n번째인지 확인
		++StepCount;
	}
	else if (StepCount == MaxSteps)
	{
		// 마지막 출력을 위해 사용
		if (GEngine)
		{
			FString FinalMsg = FString::Printf(
				TEXT("최종 결과 - 총 이동 거리: %.1f / 총 이벤트 발생 횟수: %d"),
				TotalDistance,
				EventCount
			);// 총 거리와 이벤트 발생 횟수

			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, FinalMsg);
		}
		++StepCount;
	}

}

void AMyActor::Move(float Distance)
{
	FVector NewLocation = GetActorLocation();
	int RandomMove = FMath::RandRange(0, 2);
	// 벡터 변수를 생성하고 현재 위치를 받아옴
	if (RandomMove == 0)// X,Y,Z중 랜덤으로 선택 이동
	{
		NewLocation.X += Distance;
	}
	else if (RandomMove == 1)
	{
		NewLocation.Y += Distance;
	}
	else
	{
		NewLocation.Z += Distance;
	}
	SetActorLocation(NewLocation);
	// 위치에 값을 Set에 보냄
}

void AMyActor::Turn(float Angle)
{
	FRotator NewRotation = GetActorRotation();
	int RandomTurn = FMath::RandRange(0, 2);

	if (RandomTurn == 1)
	{
		NewRotation.Roll += Angle;
	}
	else if (RandomTurn == 2)
	{
		NewRotation.Yaw += Angle;
	}
	else
	{
		NewRotation.Pitch += Angle;
	}

	SetActorRotation(NewRotation);
}

void AMyActor::PrintStatus(int Step) const
{
	if (GEngine)
	{
		FVector NewLocation = GetActorLocation();
		FRotator NewRotation = GetActorRotation();
		// FRotator는 float 3개 묶은 각도 타입

		FString LocationMsg = FString::Printf(
			TEXT("[Step %d] 이동: X=%.1f Y=%.1f Z=%.1f"),
			Step,
			NewLocation.X,
			NewLocation.Y,
			NewLocation.Z
		);// X,Y,Z의 좌표를 입력받음

		FString RotationMsg = FString::Printf(
			TEXT("[Step %d] 회전: Pitch=%.1f Yaw=%.1f Roll=%.1f"),
			Step,
			NewRotation.Pitch,
			NewRotation.Yaw,
			NewRotation.Roll
		);// Pitch,Yaw,Roll의 회전(각도)값을 입력받음

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, LocationMsg);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, RotationMsg);
		// 위 2개는 출력문
	}
}

void AMyActor::TriggerEvent()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,
			TEXT("와 50% 확률 당첨! 보상은 내 사랑~"));
		// 따로도 가능
	}
}