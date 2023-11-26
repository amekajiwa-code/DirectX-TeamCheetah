#include "pch.h"
#include "TimeManager.h"

TimeManager* TimeManager::_instance = nullptr;

GameTimer::GameTimer()
{
	_type = TimerType::Nomal;
	_isActive = true;
	Init();
}

GameTimer::~GameTimer()
{
}

void GameTimer::Init()
{
	_deltaTime = 0.0;
	_gameTime = 0.0;
	_frameTime = 0.0;

	_fps = 0;
	_fpsCountig = 0;

	_timeInfo = { 0, };

	_start = chrono::steady_clock::now();
	_elapsedTime = chrono::duration<double, std::milli>::zero();
}

bool GameTimer::Update()
{
	if (_isActive)
	{
		_end = chrono::steady_clock::now();
		_elapsedTime = chrono::duration<double, std::milli>(_end - _start);
		_deltaTime = _elapsedTime.count() * 0.001;

		_gameTime += _deltaTime;
		_frameTime += _deltaTime;
		_fpsCountig++;

		if (_frameTime > 1.0)
		{
			_fps = _fpsCountig / (uint32)_frameTime;

			_frameTime = 0.0;
			_fpsCountig = 0;
		}

		_start = _end;

		return true;
	}

	return false;
}

const double& GameTimer::GetDeltaTime() const
{
	return _deltaTime;
}

const double& GameTimer::GetGameTime() const
{
	return _gameTime;
}

const uint32& GameTimer::GetFPS() const
{
	return _fps;
}

const LocalTimeInfo& GameTimer::GetLocalTimeInfo()
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

void GameTimer::SetActivity(const bool& active)
{
	if (_isActive == false && active == true)
	{
		Init();
		_isActive = active;
	}

	_isActive = active;
}


EventTimer::EventTimer()
{
	_type = TimerType::Event;
	Init();
}

EventTimer::~EventTimer()
{
}

void EventTimer::Init()
{
	_isRunning = false;
	_isActive = true;

	_eventTime = 0.0;
	_elapsedTime = chrono::duration<double, std::milli>::zero();
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
	_isRunning = true;

	_start = chrono::steady_clock::now();
}

const double& EventTimer::GetElapsedTime()
{
	if (_isActive)
	{
		if (_isRunning)
		{
			_elapsedTime = chrono::duration<double, std::milli>(chrono::steady_clock::now() - _start);
			_eventTime = _elapsedTime.count() * 0.001;

			return _eventTime;
		}
		else
		{
			_elapsedTime = chrono::duration<double, std::milli>(_end - _start);
			_eventTime = _elapsedTime.count() * 0.001;

			return _eventTime;
		}
	}

	return NULL;
}


TimeManager::TimeManager()
{
	_timer = make_shared<GameTimer>();
}

void TimeManager::Init()
{
	_timer->Init();
}

void TimeManager::Update()
{
	_timer->Update();
}

void TimeManager::SetActivity(const bool& active)
{
	_timer->SetActivity(active);
}

const double& TimeManager::GetDeltaTime()
{
	return _timer->GetDeltaTime();
}
const double& TimeManager::GetGameTime()
{
	return _timer->GetGameTime();
}
const uint32& TimeManager::GetFPS()
{
	return _timer->GetFPS();
}
const LocalTimeInfo& TimeManager::GetLocalTimeInfo()
{
	return _timer->GetLocalTimeInfo();
}