#include "NeulogGSRPrivatePCH.h"
#include "NeulogModule.h"
#include "NeulogSensor.h"

DEFINE_LOG_CATEGORY(Neulog);

INeulogSensorPtr FNeulogGSRModule::GetPort(const FString& PortName)
{
	if (auto Port = Ports.Find(PortName))
	{
		return *Port;
	}
	
	return Ports.Add(PortName, MakeShareable(new FNeulogSensor(PortName)));
}

IMPLEMENT_MODULE(FNeulogGSRModule, NeulogGSR)