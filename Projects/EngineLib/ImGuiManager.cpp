#include "pch.h"
#include "ImGuiManager.h"

ImGuiManager* ImGuiManager::_instance = nullptr;

ImGuiManager::ImGuiManager()
{
}

ImGuiManager::~ImGuiManager()
{

}
void ImGuiManager::Init()
{
	//ImGui Main
	{
		// Show the window
		::ShowWindow(g_gameDesc.hWnd, SW_SHOWDEFAULT);
		::UpdateWindow(g_gameDesc.hWnd);
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
		//한글 폰트 추가 - add kor font
		io.Fonts->AddFontFromFileTTF("../../Resources/Font/Warhaven_Bold.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesKorean());
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		// Setup Platform/Renderer backends
		ImGui_ImplWin32_Init(g_gameDesc.hWnd);
		ImGui_ImplDX11_Init(DEVICE().Get(), DC().Get());
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

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Hp Window", &show_hp_window);
        ImGui::Checkbox("Chat Window", &show_chat_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::End();
    }


    // show_hp_window
    if (show_hp_window)
    {
        // Set the window size to a fixed value
        ImGui::SetNextWindowSize(ImVec2(300, 75), ImGuiCond_Always);
        // Set the window position to the top-left corner
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);

        // 윈도우의 배경색을 투명도(alpha)에 따라 설정
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
        ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));

        ImGui::Begin("My Window", &show_hp_window, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

        ImGui::PopStyleColor(3); // Push한 스타일을 복원

        ImGui::Text("Warrior");
        //Progress Bar
         // Push a custom color for ProgressBar
        ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.8f, 0.2f, 0.2f, 1.0f));

        // Use the ProgressBar function without specifying a custom color
        ImGui::ProgressBar(0.7f);

        // Pop the custom color after using it
        ImGui::PopStyleColor();

        /*if (ImGui::Button("Close Me"))
            show_hp_window = false;*/
        ImGui::End();
    }

    // show_chat_window
    if (show_chat_window)
    {
        float windowSizeX = 400;
        float windowSizeY = 200;
        // Set the window size to a fixed value
        ImGui::SetNextWindowSize(ImVec2(windowSizeX, windowSizeY), ImGuiCond_Always);
        // Get the main display size to calculate the position
        ImVec2 displaySize = ImGui::GetIO().DisplaySize;
        // Set the window position to the bottom-left corner
        ImGui::SetNextWindowPos(ImVec2(0, displaySize.y - ImGui::GetFrameHeightWithSpacing() - windowSizeY), ImGuiCond_Always);

        ImGui::Begin("Chat window", &show_chat_window);

        // 채팅 메시지 출력 리스트
        ImGui::BeginChild("ChatMessages", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));
        for (const auto& message : chatMessages)
        {
            ImGui::TextWrapped("%s", message.c_str());
        }
        ImGui::EndChild();

        // 채팅 입력박스
        if (ImGui::InputText("##ChatInput", buffer, sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue))
        {
            // Enter 키를 누르면 "Send" 버튼과 동일한 동작 수행
            chatMessages.push_back(buffer);
            buffer[0] = '\0'; // 입력박스 초기화

            isScrollBottom = true;
        }

        //채팅 입력버튼
        ImGui::SameLine();
        if (ImGui::Button("Send") && buffer[0] != '\0') // 버튼을 클릭하면 메시지를 보냄 (비어있지 않은 경우)
        {
            chatMessages.push_back(buffer);
            buffer[0] = '\0'; // 입력박스 초기화

            isScrollBottom = true;
        }

        ImGui::SetScrollHereY(1.0f); // 스크롤을 가장 아래로 내리기
        ImGui::End();
    }
}

void ImGuiManager::Render()
{
	//ImGui Main
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
}