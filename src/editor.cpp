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
    // Check if context is valid before proceeding
    if (!m_window || !m_glContext) {
        return;
    }

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
    
    // FIX 1: Enable docking properly with ID
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        static ImGuiID dockspace_id = 0;
        dockspace_id = ImGui::DockSpaceOverViewport();
    }

    // Your editor windows
    if (ImGui::Begin("Stats"))
    {
        ImGui::Text("FPS: %.1f", fps);
        ImGui::Text("Delta Time: %.3f ms", deltaTime * 1000.0f);
    }
    ImGui::End();

    if (ImGui::Begin("Scene Hierarchy"))
    {
        ImGui::Text("Scene objects will go here");
        
        // Example tree with proper ID handling
        if (ImGui::TreeNode("Scene Root"))
        {
            if (ImGui::TreeNode("Child Object 1"))
            {
                ImGui::Text("Component 1");
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Child Object 2"))
            {
                ImGui::Text("Component 2");
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }
    }
    ImGui::End();

    if (ImGui::Begin("Properties"))
    {
        ImGui::Text("Object properties will go here");
    }
    ImGui::End();

    if (ImGui::Begin("Viewport"))
    {
        ImGui::Text("Game view will go here");
        
        // Get available region for rendering
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        ImGui::Text("Viewport Size: %.0fx%.0f", viewportPanelSize.x, viewportPanelSize.y);
    }
    ImGui::End();

    static bool showDemoWindow = false;
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("View"))
        {
            ImGui::MenuItem("Demo Window", nullptr, &showDemoWindow);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    
    if (showDemoWindow)
    {
        ImGui::ShowDemoWindow(&showDemoWindow);
    }

    // FIX 3: Improved Inspector with proper IDs and error checking
    if (ImGui::Begin("Inspector"))
    {
        if (ImGui::CollapsingHeader("Transform"))
        {
            ImGui::Text("Position");
            
            // Use proper unique IDs and float inputs for transform
            static float position[3] = {0.0f, 0.0f, 0.0f};
            ImGui::PushID("Position");
            ImGui::DragFloat3("##pos", position, 0.1f);
            ImGui::PopID();
            
            ImGui::Text("Rotation");
            static float rotation[3] = {0.0f, 0.0f, 0.0f};
            ImGui::PushID("Rotation");
            ImGui::DragFloat3("##rot", rotation, 1.0f);
            ImGui::PopID();
            
            ImGui::Text("Scale");
            static float scale[3] = {1.0f, 1.0f, 1.0f};
            ImGui::PushID("Scale");
            ImGui::DragFloat3("##scale", scale, 0.01f);
            ImGui::PopID();
        }
        
        // FIX 4: Configuration dropdown with proper handling
        if (ImGui::CollapsingHeader("Configuration"))
        {
            static int currentItem = 0;
            const char* items[] = { "Debug", "Release", "Profile" };
            
            ImGui::Text("Build Configuration:");
            if (ImGui::Combo("##config", &currentItem, items, IM_ARRAYSIZE(items)))
            {
                // Handle configuration change here
                ImGui::Text("Configuration changed to: %s", items[currentItem]);
            }
            
            static bool vsync = true;
            if (ImGui::Checkbox("VSync", &vsync))
            {
                // Handle vsync change
            }
            
            static float renderScale = 1.0f;
            if (ImGui::SliderFloat("Render Scale", &renderScale, 0.1f, 2.0f))
            {
                // Handle render scale change
            }
        }
    }
    ImGui::End();

    // FIX 5: Error checking before rendering
    ImGui::Render();
    
    // Check if render data is valid
    ImDrawData* draw_data = ImGui::GetDrawData();
    if (draw_data && draw_data->Valid)
    {
        ImGui_ImplOpenGL3_RenderDrawData(draw_data);
    }

    // Handle multi-viewport (if enabled)
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
        SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
        
        if (backup_current_window && backup_current_context)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
        }
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

    // FIX 6: Set proper viewport flags for multi-viewport
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui::StyleColorsDark();

    // FIX 7: Check initialization success
    bool sdl_init_success = ImGui_ImplSDL3_InitForOpenGL(m_window, m_glContext);
    bool opengl_init_success = ImGui_ImplOpenGL3_Init("#version 330 core");
    
    if (!sdl_init_success || !opengl_init_success)
    {
        // Handle initialization failure
        SDL_Log("Failed to initialize ImGui implementations");
    }
}

void Editor::ShutdownImGui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}