#pragma once

class FNeulogGSRModule : public INeulogGSRModule
{
public:
	virtual INeulogSensorPtr GetPort(const FString& PortName);

private:
	TMap<FString, INeulogSensorPtr> Ports;
};