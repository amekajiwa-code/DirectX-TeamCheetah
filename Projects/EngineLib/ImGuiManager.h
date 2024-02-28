#pragma once
#include "GUIInterface.h"

class ImGuiManager
{
	using GuiList = vector<shared_ptr<GUIInterface>>;
private:
	static ImGuiManager* _instance;
public:
	static ImGuiManager* GetInstance()
	{
		if (_instance == nullptr)
			_instance = new ImGuiManager();

		return _instance;
	}
private:
	ImGuiManager();
	~ImGuiManager();
public:
	void Init();
	void Update();
	void Render();

	void AddMessage(char message[50]);

	std::vector<std::string> GetLatestMessages() { return chatMessages; }
	void UpdateHp(uint32 maxHp, uint32 hp);
	void UpdateMp(uint32 maxMp, uint32 mp);
	void UpdatePicked(bool isPicked, uint32 maxHp = 0, uint32 hp = 0, wstring name = L"");
	void NotifyPlayerAlive(bool isAlive) { show_death_window = !isAlive;}
	int GetAttackQueueSize();
private:
	//Player Stat
	float _hp = 1.0f;
	float _mp = 1.0f;
	char* _name;
	//Picked Object Stat
	float _pickedHp = 1.0f;
	//Rebirth
	queue<bool> _rebirthQueue;
	//윈도우 활성화 여부
	bool show_hp_window = true;
	bool show_picked_hp_window = false;
	bool show_chat_window = true;
	bool show_death_window = false;
	bool show_nickname_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	//채팅 멤버
	char buffer[256] = "";
	char nameBuffer[256] = "";
	std::vector<std::string> chatMessages; // 채팅 메시지를 저장할 벡터
	std::vector<std::string> otherChatMessages; // 다른 유저 채팅 메시지를 저장할 벡터
	bool isScrollBottom = false;
};