#pragma once

class FNeulogSensor : public FRunnable, public INeulogSensor
{
public:
	explicit FNeulogSensor(const FString& PortName);

	virtual uint32 Run() override;
	virtual void Stop() override { ExitRequested = true; }
	
	virtual NeulogError Start() override;
	virtual float GetValue() override { return CurrentValue; }

private:
	serial::Serial Port;
	TUniquePtr<FRunnableThread> Thread;
	FString PortID;
	volatile float CurrentValue = 0;
	volatile bool ExitRequested = false;
};