# UnrealGSR
Galvanic skin response (GSR), also known as skin conductance, can be used as a measure of emotional response. This plugin allows you to measure GSR in Unreal Engine 4, using the [NeuLog GSR sensor module](https://neulog.com/gsr/). This has applications for both controlled playtest analytics and also purpose-built games.

Tested on Unreal 4.13 and Windows-only for now.

# Installation
Copy the NeulogGSR plugin to your game's Plugins directory.

# Usage
```c++
if (INeulogGSRModule::IsAvailable())
{
	INeulogGSRModule& GSR = INeulogGSRModule::Get();
	INeulogSensorPtr NeulogSensor = GSR.FindSensor();
	
	...
	
	float CurrentGSRValue = NeulogSensor->GetValue();
}
```

# Sample Game Graph
The sample game in this repository includes a quick in-world graph of the GSR history:

![GSR example graph](http://i.imgur.com/zIL8NFl.png)
