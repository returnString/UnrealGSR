// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "GSRExample.h"
#include "GSRExampleGameMode.h"
#include "GSRExampleCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(SampleLog, Log, All);

AGSRExampleGameMode::AGSRExampleGameMode()
{
	if (INeulogGSRModule::IsAvailable())
	{
		auto& GSR = INeulogGSRModule::Get();
		NeulogSensor = GSR.GetPort("COM3");
		if (!NeulogSensor->Connected())
		{
			NeulogSensor = nullptr;
		}
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

	if (NeulogSensor.IsValid())
	{
		float Value;
		if (NeulogSensor->GetValue(Value))
		{
			UE_LOG(SampleLog, Log, TEXT("Got value: %.2f"), Value);
		}
		else
		{
			UE_LOG(SampleLog, Error, TEXT("Got no value"));
		}
	}
}
