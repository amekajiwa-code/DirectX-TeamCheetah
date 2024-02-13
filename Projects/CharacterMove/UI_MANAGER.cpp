#include "pch.h"
#include "UI_MANAGER.h"

UI_MANAGER* UI_MANAGER::_instance = nullptr;

void UI_MANAGER::Init()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); //(void)io;

    //한글 폰트 추가 - add kor font
    io.Fonts->AddFontFromFileTTF("../../../../Resources/Font/Warhaven_Bold.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesKorean());

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls



    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(g_gameDesc.hWnd);
    DEVICE();
    DC();
    ImGui_ImplDX11_Init(nullptr, nullptr);
}

void UI_MANAGER::Update()
{
    if (!done)
    {

    }
}
