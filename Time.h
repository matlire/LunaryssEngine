#pragma once

#include <chrono>

using namespace std;

class Time
{
public:
	double GetTime();
	double GetDeltaTime();
	void Update();
private:
	double DeltaTime;
	double Time;
};