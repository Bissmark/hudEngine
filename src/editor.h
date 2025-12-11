#pragma once

#include <SDL3/SDL.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl3.h"
#include "imgui/imgui_impl_opengl3.h"

class Editor
{
public:
    Editor(SDL_Window* window, SDL_GLContext glContext);
    ~Editor();

    void Update();
    
    // Event handling for ImGui
    void HandleEvent(const SDL_Event* event);

private:
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
    
    // Editor state
    bool m_isInitialized;
    
    void InitImGui();
    void ShutdownImGui();
    
    // UI rendering functions
    void RenderMainMenuBar();
    void RenderStatsWindow();
    void RenderSceneHierarchy();
    void RenderPropertiesPanel();
    void RenderViewport();
    void RenderInspector();
};