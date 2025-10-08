#include <SDL3/SDL.h>
#include <string>

class Window
{
    public:
        Window(int width, int height, const std::string& title);
        ~Window();

        void Update();

        bool isClosed();
    private:
        SDL_Window* m_window;
        bool m_isClosed = false;
};