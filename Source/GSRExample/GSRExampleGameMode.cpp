// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "GSRExample.h"
#include "GSRExampleGameMode.h"
#include "GSRExampleCharacter.h"

#include <DrawDebugHelpers.h>

DEFINE_LOG_CATEGORY_STATIC(SampleLog, Log, All);

AGSRExampleGameMode::AGSRExampleGameMode()
	: GSRHistory(3000, 0, 4, true)
{
	if (INeulogGSRModule::IsAvailable())
	{
		auto& GSR = INeulogGSRModule::Get();
		NeulogSensor = GSR.FindSensor();
	}

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AGSRExampleGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (UWorld* World = GetWorld())
	{
		auto Character = UGameplayStatics::GetPlayerCharacter(World, 0);
		DrawDebugFloatHistory(*World, GSRHistory, Character->GetTransform(), FVector2D(500, 100), FColor::Red, false, -1.f, 1);

		if (NeulogSensor.IsValid())
		{
			//UE_LOG(SampleLog, Log, TEXT("Got value: %.2f"), NeulogSensor->GetValue());
			GSRHistory.AddSample(NeulogSensor->GetValue());
		}
	}
}
