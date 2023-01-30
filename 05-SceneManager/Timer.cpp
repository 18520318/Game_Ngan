#include "Timer.h"

Timer::Timer(bool useGameTime, long timeout) {
	this->useGameTime = useGameTime;
	this->timeleft = this->timeout = timeout;
	this->state = TimerState::STOPPED;
	this->startPoint = GetTickCount64();
}

void Timer::SetTimeOut(long timeout) {
	AddTimeOut(timeout - this->timeout);
}

void Timer::AddTimeOut(long timeout) {
	this->timeleft += timeout;
	this->timeout += timeout;
}

TimerState Timer::GetState()
{
	return state;
}

void Timer::Start() {
	this->state = TimerState::RUNNING;
	this->startPoint = GetTickCount64();
}

void Timer::Stop() {
	this->state = TimerState::STOPPED;
}

void Timer::Reset() {
	this->state = TimerState::STOPPED;
	this->timeleft = timeout;
}

void Timer::Update(unsigned long dt) {
	if (state != TimerState::RUNNING) return;

	if (useGameTime) {
		this->timeleft -= dt;
	}
	else {
		this->timeleft = timeout - (GetTickCount64() - startPoint);
	}

	if (timeleft < 0) {
		state = TimerState::TIMEOVER;
		timeleft = 0;
	}
}
