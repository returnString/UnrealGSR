#pragma once

class FNeulogSensor : public INeulogSensor
{
public:
	explicit FNeulogSensor(const FString& PortName);

	virtual bool Connected() const override { return IsConnected; }
	virtual bool GetValue(float& Value) override;

private:
	serial::Serial Port;
	bool IsConnected = false;
};