#pragma once
#include <SDL3/SDL.h>
#include <GL/glew.h>
#include <string>
#include <memory>
#include "editor.h"

class Window
{
    public:
        Window(int width, int height, const std::string& title);
        ~Window();

        void Update();
        bool isClosed();
        SDL_Window* GetSDLWindow() { return m_window; }
        SDL_GLContext GetGLContext() { return m_glContext; }
    private:
        SDL_Window* m_window;
        SDL_GLContext m_glContext;
        std::unique_ptr<Editor> m_editor;
        bool m_isClosed = false;
};