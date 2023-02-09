#pragma once
#include "Utils.h"

enum class TimerState
{
	RUNNING,
	TIMEOVER,
	STOPPED
};

class Timer
{
private:
	bool useGameTime;

	TimerState state;

	long timeleft;

	long timeout;

	long startPoint;

public:
	Timer(bool useGameTime, long timeout = 0);

	void SetTimeOut(long timeout);

	void AddTimeOut(long timeout);

	TimerState GetState();

	void Start();

	void Stop();

	void Reset();

	void Update(unsigned long dt);

	int GetTime() { return timeleft; }

};

