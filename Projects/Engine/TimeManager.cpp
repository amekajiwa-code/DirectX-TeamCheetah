#include "pch.h"
#include "TimeManager.h"
#include <algorithm>

TimeManager* TimeManager::_instance = nullptr;

Timer::Timer()
{
	_isRunning = false;
	_isActive = false;
	_type = TimerType::None;

	_elapsedTime = chrono::duration<double>::zero();
	_end = chrono::steady_clock::now();
	_start = chrono::steady_clock::now();
}

FrameTimer::FrameTimer()
{
	_type = TimerType::Frame;
	_isActive = true;

	_fps = 0;
	_fpsCountig = 0;
	_framePerSec = 0.0;
}

FrameTimer::~FrameTimer()
{
}

bool FrameTimer::Update()
{
	if (_isActive)
	{
		if (_isRunning)
		{
			_end = chrono::steady_clock::now();
			_elapsedTime = chrono::duration_cast<chrono::milliseconds>(_end - _start);

			_framePerSec += _elapsedTime.count();

			_start = _end;

			return true;
		}
	}

	return false;
}

bool FrameTimer::Start()
{
	if (_isRunning)
	{
		return false;
	}
	else
	{
		_start = chrono::steady_clock::now();
		_isRunning = true;

		return true;
	}
}

bool FrameTimer::Stop()
{
	if (_isRunning == false)
	{
		return false;
	}
	else
	{
		_isRunning = false;

		return true;
	}
}

void FrameTimer::Reset()
{
	_fps = 0;
	_fpsCountig = 0;
	_framePerSec = 0.0;
	_isRunning = false;
	_elapsedTime = chrono::duration<double>::zero();

	_end = chrono::steady_clock::now();
	_start = chrono::steady_clock::now();
}

double FrameTimer::GetElapsedTime()
{
	return _elapsedTime.count();
}

uint16& FrameTimer::GetFPS()
{
	if (_isActive)
	{
		if (_isRunning)
		{
			if (_framePerSec >= 1.0)
			{
				_fps = _fpsCountig;
				_fpsCountig = 0;
				_framePerSec -= 1.0;
			}
			_fpsCountig++;

			return _fps;
		}
	}
	else
	{
		uint16 fail = 0;
		return fail;
	}
}

EventTimer::EventTimer()
{
	_type = TimerType::Event;
	_isActive = true;
}

EventTimer::~EventTimer()
{
}

bool EventTimer::Update()
{
	if (_isActive)
	{
		if (_isRunning)
		{
			_elapsedTime += chrono::duration<double, std::milli>(_end - _start);

			return true;
		}
	}

	return false;
}

bool EventTimer::Start()
{
	if (_isRunning)
	{
		return false;
	}
	else
	{
		_start = chrono::steady_clock::now();
		_isRunning = true;

		return true;
	}
}

bool EventTimer::Stop()
{
	if (_isRunning == false)
	{
		return false;
	}
	else
	{
		_end = chrono::steady_clock::now();
		_isRunning = false;

		return true;
	}
}

void EventTimer::Reset()
{
	_isRunning = false;

	_elapsedTime = chrono::duration<double>::zero();
	_end = chrono::steady_clock::now();
	_start = chrono::steady_clock::now();
}

double EventTimer::GetElapsedTime()
{
	return _elapsedTime.count();
}

GlobalTimer::GlobalTimer()
{
	_type = TimerType::Global;
	_isActive = true;
	_gameTime = 0.0;
	_timeInfo = { 0, };
}

GlobalTimer::~GlobalTimer()
{
}

bool GlobalTimer::Update()
{
	if (_isActive)
	{
		if (_isRunning)
		{
			_end = chrono::steady_clock::now();
			_elapsedTime = chrono::duration<double, std::milli>(_end - _start);

			_gameTime += _elapsedTime.count();

			_start = _end;


			return true;
		}
	}

	return false;
}

bool GlobalTimer::Start()
{
	if (_isRunning)
	{
		return false;
	}
	else
	{
		_start = chrono::steady_clock::now();
		_isRunning = true;

		return true;
	}
}

bool GlobalTimer::Stop()
{
	if (_isRunning == false)
	{
		return false;
	}
	else
	{
		_isRunning = false;

		return true;
	}
}

void GlobalTimer::Reset()
{
	_timeInfo = { 0, };
	_isRunning = false;
	_gameTime = 0.0;

	_elapsedTime = chrono::duration<double>::zero();
	_end = chrono::steady_clock::now();
	_start = chrono::steady_clock::now();
	_localTime = chrono::system_clock::now();
}

double GlobalTimer::GetElapsedTime()
{
	return _gameTime;
}

const LocalTimeInfo& GlobalTimer::GetLocalTimeInfo()
{
	_timeInfo = { 0, };

	_localTime = chrono::system_clock::now();
	_timeInfo.epoch = _localTime.time_since_epoch() % 1000;

	time_t tt = chrono::system_clock::to_time_t(_localTime);

	localtime_s(&_timeInfo._tm, &tt);
	_timeInfo._tm.tm_year += 1900;
	_timeInfo._tm.tm_mon += 1;

	return _timeInfo;
}

TimeManager::TimeManager()
{
	_activeTimer = 0;
	for (int i = 0; i < _eventTimerArray.size(); ++i)
	{
		_eventTimerArray[i] = make_shared<EventTimer>();
	}
	_fTimer = make_shared<FrameTimer>();
	_gTimer = make_shared<GlobalTimer>();
}

void TimeManager::Init()
{
	_fTimer->Start();
	_gTimer->Start();
}

void TimeManager::Update()
{
	_fTimer->Update();
	_gTimer->Update();
}

shared_ptr<EventTimer> TimeManager::GetEventTimer()
{
	for (auto& timer : _eventTimerArray)
	{
		if (timer->GetActivity() == false)
		{
			timer->SetActivity(true);
			_activeTimer++;
			return timer;
		}
	}
}