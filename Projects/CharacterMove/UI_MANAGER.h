#pragma once

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_dx11.h"

class UI_MANAGER
{
private:
	static UI_MANAGER* _instance;
public:
	static UI_MANAGER* GetInstance()
	{
		if (_instance == nullptr)
			_instance = new UI_MANAGER();

		return _instance;
	}
private:
	UI_MANAGER() {}
	~UI_MANAGER() {}
public:
	void Init();
	void Update();
private:
	// Our state
	bool show_demo_window = false;
	bool show_another_window = false;
	bool show_hp_window = true;
	bool show_chat_window = true;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	//채팅 멤버
	char buffer[256] = "";
	std::vector<std::string> chatMessages; // 채팅 메시지를 저장할 벡터
	bool isScrollBottom = false;

	// Main loop
	bool done = false;
};

