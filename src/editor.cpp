#include "editor.h"

Editor::Editor(SDL_Window* window, SDL_GLContext glContext)
    : m_window(window), m_glContext(glContext)
{
    InitImGui();
}

Editor::~Editor()
{
    ShutdownImGui();
}

void Editor::Update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    static float deltaTime = 0.0f;
    static Uint64 lastTime = SDL_GetPerformanceCounter();
    Uint64 currentTime = SDL_GetPerformanceCounter();
    deltaTime = (currentTime - lastTime) / (float)SDL_GetPerformanceFrequency();
    lastTime = currentTime;
    float fps = deltaTime > 0.0f ? 1.0f / deltaTime : 0.0f;

    // Enable docking for moveable windows like in game engines
    ImGuiIO& io = ImGui::GetIO();
    // if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    // {
    //     ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
    // }

    // Your editor windows
    ImGui::Begin("Stats");
    ImGui::Text("FPS: %.1f", fps);
    ImGui::End();

    ImGui::Begin("Scene Hierarchy");
    ImGui::Text("Scene objects will go here");
    ImGui::End();

    ImGui::Begin("Properties");
    ImGui::Text("Object properties will go here");
    ImGui::End();

    ImGui::Begin("Viewport");
    ImGui::Text("Game view will go here");
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Handle multi-viewport (if enabled)
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
        SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
    }

    SDL_GL_SwapWindow(m_window);
}

void Editor::InitImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    
    // Enable docking and viewports
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForOpenGL(m_window, m_glContext);
    ImGui_ImplOpenGL3_Init("#version 330 core");
}

void Editor::ShutdownImGui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}