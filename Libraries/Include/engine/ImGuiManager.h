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
private:
	bool show_hp_window = true;
	bool show_chat_window = true;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	//ä�� ���
	char buffer[256] = "";
	std::vector<std::string> chatMessages; // ä�� �޽����� ������ ����
	bool isScrollBottom = false;
};

#define MANAGER_IMGUI() ImGuiManager::GetInstance()