#include "NeulogGSRPrivatePCH.h"
#include "NeulogSensor.h"

namespace NeulogProtocol
{
	constexpr static uint8 Prefix = 'U';
	constexpr static uint8 RequestMessage[] = { Prefix, 16, 1, 49, 0, 0, 0, 151 };
	constexpr static uint8 StartMessage[] = { Prefix, 'N', 'e', 'u', 'L', 'o', 'g', '!' };
	constexpr static uint8 StartResponse[] = { 'O', 'K', '-', 'V' };

	constexpr static size_t ConnectMessageSize = 7;
	constexpr static size_t DataMessageSize = 8;
	constexpr static size_t StringLength = 6;

	uint8 GetResultCharacter(uint8 Chr)
	{
		switch (Chr)
		{
			case 10: return '.';
			case 11: return '+';
			case 12: return '-';
			default: return Chr + '0';
		}
	}
}

FNeulogSensor::FNeulogSensor(const FString& PortName)
{
	UE_LOG(Neulog, Log, TEXT("Opening %s"), *PortName);
	std::string StdPortName(TCHAR_TO_UTF8(*PortName));

	Port.setPort(StdPortName);
	Port.setBaudrate(115200);
	Port.setBytesize(serial::eightbits);
	Port.setStopbits(serial::stopbits_two);
	Port.setTimeout(0, 1000, 0, 1000, 0);
	Port.open();

	if (!Port.isOpen())
	{
		UE_LOG(Neulog, Error, TEXT("Failed to open"));
		return;
	}

	size_t Written = Port.write(NeulogProtocol::StartMessage, sizeof(NeulogProtocol::StartMessage));
	if (Written != sizeof(NeulogProtocol::StartMessage))
	{
		UE_LOG(Neulog, Error, TEXT("Wrote %zu bytes, expected %zu"), Written, sizeof(NeulogProtocol::StartMessage));
		return;
	}

	uint8 Buffer[NeulogProtocol::ConnectMessageSize];
	size_t Read = Port.read(Buffer, sizeof(Buffer));
	if (Read != sizeof(Buffer))
	{
		UE_LOG(Neulog, Error, TEXT("Read %zu bytes, expected %zu"), Read, sizeof(Buffer));
		return;
	}

	if (memcmp(Buffer, NeulogProtocol::StartResponse, sizeof(NeulogProtocol::StartResponse)))
	{
		UE_LOG(Neulog, Error, TEXT("Response was incorrect"));
		return;
	}

	IsConnected = true;
	UE_LOG(Neulog, Log, TEXT("Connected successfully"));
}

bool FNeulogSensor::GetValue(float& Value)
{
	size_t Written = Port.write(NeulogProtocol::RequestMessage, sizeof(NeulogProtocol::RequestMessage));
	if (Written != sizeof(NeulogProtocol::RequestMessage))
	{
		UE_LOG(Neulog, Error, TEXT("Wrote %zu bytes, expected %zu"), Written, sizeof(NeulogProtocol::RequestMessage));
		return false;
	}

	uint8 Buffer[NeulogProtocol::DataMessageSize];
	size_t Read = Port.read(Buffer, sizeof(Buffer));
	if (Read != sizeof(Buffer))
	{
		UE_LOG(Neulog, Error, TEXT("Read %zu bytes, expected %zu"), Read, sizeof(Buffer));
		return false;
	}

	if (Buffer[0] != NeulogProtocol::Prefix)
	{
		UE_LOG(Neulog, Error, TEXT("Expected prefix %u, got %u"), NeulogProtocol::Prefix, Buffer[0]);
		return false;
	}

	ANSICHAR StringBuffer[NeulogProtocol::StringLength];
	StringBuffer[sizeof(StringBuffer) - 1] = 0;

	size_t StringIndex = 0;
	for (int i = 4; i < sizeof(Buffer) - 1; ++i)
	{
		uint8 Byte = Buffer[i];
		StringBuffer[StringIndex++] = NeulogProtocol::GetResultCharacter(Byte / 16);
		StringBuffer[StringIndex++] = NeulogProtocol::GetResultCharacter(Byte % 16);
	}

	Value = FCStringAnsi::Atof(StringBuffer);
	return true;
}