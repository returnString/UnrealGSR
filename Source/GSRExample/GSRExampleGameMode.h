// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "NeulogGSR.h"
#include "GSRExampleGameMode.generated.h"

UCLASS(minimalapi)
class AGSRExampleGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AGSRExampleGameMode();

	virtual void Tick(float DeltaSeconds) override;

private:
	INeulogSensorPtr NeulogSensor;
};



