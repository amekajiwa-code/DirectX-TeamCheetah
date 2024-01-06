#pragma once
#include "GUIInterface.h"

#pragma region Declaration
class GUIFile;
class GUIView;
#pragma endregion

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
private:
	GuiList _guiList;
private:
	void GuiCreate();
	void GuiUpdate();
	void GuiRender();
public:
	template<typename T>
	shared_ptr<T> GetGui();
public:
	void Init();
	void Update();
	void Render();
};

#define MANAGER_IMGUI() ImGuiManager::GetInstance()

template<typename T>
inline shared_ptr<T> ImGuiManager::GetGui()
{
	for (const auto& gui : _guiList)
	{
		auto result = dynamic_pointer_cast<T>(gui);

		if (result)
		{
			return result;
		}
	}
}
