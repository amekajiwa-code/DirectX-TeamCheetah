#include "pch.h"
#include "ImGuiManager.h"
#include "GUIFile.h"
#include "GUIView.h"
#include "AssetManager.h"

ImGuiManager* ImGuiManager::_instance = nullptr;

ImGuiManager::ImGuiManager()
{
}

ImGuiManager::~ImGuiManager()
{

}

void ImGuiManager::GuiCreate()
{
	int guiSize = static_cast<int>(GUIType::End) - 1;

	_guiList.reserve(guiSize);
	//File
	_guiList.push_back(make_shared<GUIFile>());
	//View
	_guiList.push_back(make_shared<GUIView>());
	//SceneTest
}

void ImGuiManager::GuiUpdate()
{
	if (ImGui::BeginMainMenuBar())
	{
		for (const auto& gui : _guiList)
		{
			gui->Update();
		}

		//MainMenuBar End
		ImGui::EndMainMenuBar();
	}
}

void ImGuiManager::GuiRender()
{
	for (int i = 0; i < _guiList.size(); i++)
	{
		if (_guiList[i] != nullptr)
			_guiList[i]->Render();
	}
}

void ImGuiManager::Init()
{
	MANAGER_ASSET()->Init();

	//ImGui Main
	{
		// Show the window
		::ShowWindow(g_gameDesc.hWnd, SW_SHOWDEFAULT);
		::UpdateWindow(g_gameDesc.hWnd);
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		// Setup Platform/Renderer backends
		ImGui_ImplWin32_Init(g_gameDesc.hWnd);
		ImGui_ImplDX11_Init(DEVICE().Get(), DC().Get());
	}
	//Gui Create
	{
		GuiCreate();
	}
}

void ImGuiManager::Update()
{
	//ImGui Main
	{
		// Start the Dear ImGui frame
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		ImGuizmo::SetOrthographic(false);
		ImGuizmo::BeginFrame();
	}
	//Gui Update
	{
		GuiUpdate();
	}
}

void ImGuiManager::Render()
{
	//Gui Render
	{
		GuiRender();
	}
	//ImGui Main
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
}
