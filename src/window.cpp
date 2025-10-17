#include "window.h"
#include <iostream>

Window::Window(int width, int height, const std::string& title)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return;
    }
    
    // Set OpenGL attributes before creating window
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    m_window = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!m_window)
    {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        return;
    }
    
    m_glContext = SDL_GL_CreateContext(m_window);
    if (!m_glContext)
    {
        std::cerr << "SDL_GL_CreateContext failed: " << SDL_GetError() << std::endl;
        return;
    }
    
    SDL_GL_MakeCurrent(m_window, m_glContext);
    SDL_GL_SetSwapInterval(1); // Enable vsync
    
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cerr << "GLEW Init failed: " << glewGetErrorString(err) << std::endl;
        return;
    }
    
    std::cout << "OpenGL initialized successfully" << std::endl;
    
    // Now create the editor and pass it the window/context
    m_editor = std::make_unique<Editor>(m_window, m_glContext);
}

Window::~Window()
{
    // Destroy editor first (before OpenGL context)
    m_editor.reset();
    
    if (m_glContext)
    {
        SDL_GL_DestroyContext(m_glContext);
    }
    if (m_window)
    {
        SDL_DestroyWindow(m_window);
    }
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
        // Let ImGui handle the event first
        ImGui_ImplSDL3_ProcessEvent(&event);
        
        if (event.type == SDL_EVENT_QUIT)
        {
            m_isClosed = true;
        }
    }
    
    // Clear the screen
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Update editor (which renders ImGui)
    if (m_editor)
    {
        m_editor->Update();
    }
}