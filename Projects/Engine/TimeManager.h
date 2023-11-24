#pragma once
#include <chrono>
#include <ctime>

enum class TimerType : uint8
{
	None,
	Frame,
	Event,
	Global,
	End
};

enum
{
	TIMER_TYPE_COUNT = static_cast<uint8>(TimerType::End ) - 1,
	MAX_EVENT_TIMER_COUNT = (size_t)100
};

struct LocalTimeInfo
{
	struct tm _tm;
	chrono::system_clock::duration epoch;
};

class Timer
{
public:
	Timer();
	virtual ~Timer(){}
protected:
	TimerType	_type;
	bool		_isActive;
	bool		_isRunning;
protected:
	std::chrono::steady_clock::time_point	_start;
	std::chrono::steady_clock::time_point	_end;
	std::chrono::duration<double>			_elapsedTime;
public:
	virtual bool Update(){}
public:
	virtual bool Start() = 0;
	virtual bool Stop() = 0;
	virtual void Reset() = 0;
public:
	virtual double GetElapsedTime() { return 0.0; }
	bool GetActivity() const { return _isActive; }
public:
	void SetActivity(const bool& act) { if (_isActive  == false && act == true) Reset(); _isActive = act; }
};

class FrameTimer : public Timer
{
public:
	FrameTimer();
	virtual ~FrameTimer();
private:
	double _framePerSec;
	uint16 _fps;
	uint16 _fpsCountig;
public:
	virtual bool Update() override;
public:
	virtual bool Start() override;
	virtual bool Stop() override;
	virtual void Reset() override;
public:
	virtual double GetElapsedTime() override;
	uint16& GetFPS();
};

class EventTimer : public Timer
{
public:
	EventTimer();
	virtual ~EventTimer();
public:
	virtual bool Update() override;
public:
	virtual bool Start() override;
	virtual bool Stop() override;
	virtual void Reset() override;
public:
	virtual double GetElapsedTime() override;
};

class GlobalTimer : public Timer
{
public:
	GlobalTimer();
	virtual ~GlobalTimer();
private:
	chrono::system_clock::time_point _localTime;
	double			_gameTime;
	LocalTimeInfo	_timeInfo;
public:
	virtual bool Update() override;
public:
	virtual bool Start() override;
	virtual bool Stop() override;
	virtual void Reset() override;
public:
	virtual double GetElapsedTime() override;
	const LocalTimeInfo& GetLocalTimeInfo();
};

class TimeManager
{
private:
	TimeManager();
	~TimeManager() {}
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
	shared_ptr<FrameTimer>	_fTimer;
	std::array<shared_ptr<EventTimer>, MAX_EVENT_TIMER_COUNT> _eventTimerArray;
	shared_ptr<GlobalTimer>	_gTimer;
private:
	int _activeTimer;
public:
	void Init();
	void Update();
public:
	shared_ptr<FrameTimer> GetFrameTimer() { return _fTimer; }
	shared_ptr<EventTimer> GetEventTimer();
	shared_ptr<GlobalTimer> GetGlobalTimer() { return _gTimer; }
};

