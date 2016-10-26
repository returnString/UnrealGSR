#include "NeulogGSRPrivatePCH.h"
#include "NeulogModule.h"
#include "NeulogSensor.h"

DEFINE_LOG_CATEGORY(Neulog);

INeulogSensorPtr FNeulogGSRModule::GetPort(const FString& PortName)
{
	return MoveTemp(MakeUnique<FNeulogSensor>(PortName));
}

IMPLEMENT_MODULE(FNeulogGSRModule, NeulogGSR)