#pragma once

#include "ModuleManager.h"

class INeulogSensor
{
public:
	virtual bool Connected() const = 0;
	virtual bool GetValue(float& Value) = 0;
};

using INeulogSensorPtr = TSharedPtr<INeulogSensor>;

class INeulogGSRModule : public IModuleInterface
{
public:
	virtual INeulogSensorPtr GetPort(const FString& PortName) = 0;

	static INeulogGSRModule& Get()
	{
		return FModuleManager::LoadModuleChecked<INeulogGSRModule>("NeulogGSR");
	}

	static bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("NeulogGSR");
	}
};