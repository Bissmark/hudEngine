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

        SDL_Window* m_window;
        SDL_GLContext m_glContext;
    private:
        void InitImGui();
        void ShutdownImGui();
};