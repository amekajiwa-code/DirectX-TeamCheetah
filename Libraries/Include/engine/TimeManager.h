#pragma once
#include <chrono>
#include <ctime>

enum class TimerType : uint8
{
	None,
	Nomal,
	Event,
	End
};

enum
{
	TIMER_TYPE_COUNT = static_cast<uint8>(TimerType::End) - 1,
};

struct LocalTimeInfo
{
	struct tm _tm;
	chrono::system_clock::duration epoch;
};

class GameTimer
{
	using SystemTime_point = chrono::system_clock::time_point;
	using SteadyTime_point = chrono::steady_clock::time_point;
public:
	GameTimer();
	virtual ~GameTimer();
private:
	double _deltaTime;
	double _gameTime;
	double _frameTime;
	SystemTime_point _localTime;
	uint32 _fps;
	uint32 _fpsCountig;
	LocalTimeInfo _timeInfo;
protected:
	TimerType _type;
	bool _isActive;
protected:
	SteadyTime_point _start;
	SteadyTime_point _end;
	chrono::duration<double, std::milli> _elapsedTime;
public:
	virtual void Init();
	virtual bool Update();
public:
	const double& GetDeltaTime() const;
	const double& GetGameTime() const;
	const uint32& GetFPS() const;
	const LocalTimeInfo& GetLocalTimeInfo();
public:
	bool GetActivity() const { return _isActive; }
	void SetActivity(const bool& active);
};

class EventTimer : public GameTimer
{
public:
	EventTimer();
	virtual ~EventTimer();
private:
	bool _isRunning;
	double _eventTime;
public:
	virtual void Init() override;
	virtual bool Update() { return false; }
public:
	bool Start();
	bool Stop();
	void Reset();
public:
	const double& GetElapsedTime();
public:
	const double& GetDeltaTime() = delete;
	const double& GetGameTime() = delete;
	const uint32& GetFPS() = delete;
	const LocalTimeInfo& GetLocalTimeInfo() = delete;
};

class TimeManager
{
public:
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
	shared_ptr<GameTimer>	_timer;
public:
	void Init();
	void Update();
public:
	void SetActivity(const bool& active);
public:
	const double& GetDeltaTime();
	const double& GetGameTime();
	const uint32& GetFPS();
	const LocalTimeInfo& GetLocalTimeInfo();
};

