#include "window.h"

Window::Window(int width, int height, const std::string& title)
{
    SDL_Init(SDL_INIT_VIDEO);
    m_window = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_OPENGL);
}

Window::~Window()
{
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool Window::isClosed()
{
    return m_isClosed;
}

void Window::Update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            m_isClosed = true;
        }
    }
}