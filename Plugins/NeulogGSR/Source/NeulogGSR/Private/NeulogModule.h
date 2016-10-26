#pragma once

class FNeulogGSRModule : public INeulogGSRModule
{
public:
	virtual INeulogSensorPtr OpenSensorOnPort(const FString& PortName) final;
	virtual INeulogSensorPtr FindSensor() final;
};