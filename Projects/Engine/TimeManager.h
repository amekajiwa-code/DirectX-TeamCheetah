#pragma once
#include <chrono>

class TimeManager
{
private:
	TimeManager(){}
	~TimeManager(){}
private:
	static TimeManager* _instance;
public:
	static TimeManager* GetInstance()
	{
		if (_instance == nullptr)
			_instance = new TimeManager();

		return _instance;
	}
private:
	LARGE_INTEGER _frequency;
	LARGE_INTEGER _current;
	LARGE_INTEGER _frame;
	float		  _secPerFrame;
	LARGE_INTEGER _fps;
	int _framePerSecond;
	int _elapsedFPS;
	LARGE_INTEGER _eventStart;
	LARGE_INTEGER _eventElapsed;
	bool _eventRunning;
	float _eventTime;
public:
	void Start();
	void Stop();
	void Reset();
public:
	void Init();
	void Update();
public:
	int GetFPS();
	float GetDeltaTime();

};

