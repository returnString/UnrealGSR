#include "NeulogGSRPrivatePCH.h"
#include "NeulogModule.h"
#include "NeulogSensor.h"

DEFINE_LOG_CATEGORY(Neulog);

INeulogSensorPtr FNeulogGSRModule::OpenSensorOnPort(const FString& PortName)
{
	return MoveTemp(MakeUnique<FNeulogSensor>(PortName));
}

INeulogSensorPtr FNeulogGSRModule::FindSensor()
{
	for (const auto& PortInfo : serial::list_ports())
	{
		if (PortInfo.hardware_id == "USB\\VID_10C4&PID_EA60&REV_0100")
		{
			FString PortID(UTF8_TO_TCHAR(PortInfo.port.c_str()));
			UE_LOG(Neulog, Log, TEXT("Autodetection found port %s, attempting"), *PortID);
			auto Sensor = OpenSensorOnPort(PortID);
			if (Sensor->Start() == NeulogError::None)
			{
				return Sensor;
			}
		}
	}

	return nullptr;
}

IMPLEMENT_MODULE(FNeulogGSRModule, NeulogGSR)