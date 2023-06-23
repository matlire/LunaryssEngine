#include "Time.h"

using namespace std;

double Time::GetTime()
{
	return	this->Time;
}

double Time::GetDeltaTime()
{
	return this->DeltaTime;
}

void Time::Update()
{
	chrono::duration<double> t = chrono::system_clock::now().time_since_epoch();
	this->DeltaTime = t.count() - this->Time;
	this->Time = t.count();
}