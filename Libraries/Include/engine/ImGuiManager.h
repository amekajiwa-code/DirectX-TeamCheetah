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

	void AddMessage(char message[50])
	{
		// 받은 문자열을 std::string으로 변환
		std::string newMessage(message);

		// chatMessages 벡터에 추가
		otherChatMessages.push_back(newMessage);
	}

	std::vector<std::string> GetLatestMessages()
	{
		return chatMessages;
	}
private:
	//
	float hp = 0.68f;
	float mp = 0.81f;
	//윈도우 활성화 여부
	bool show_hp_window = true;
	bool show_chat_window = true;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	//채팅 멤버
	char buffer[256] = "";
	std::vector<std::string> chatMessages; // 채팅 메시지를 저장할 벡터
	std::vector<std::string> otherChatMessages; // 다른 유저 채팅 메시지를 저장할 벡터
	bool isScrollBottom = false;
};

#define MANAGER_IMGUI() ImGuiManager::GetInstance()