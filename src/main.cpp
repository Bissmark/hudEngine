#include <iostream>
#include "window.h"

#define WIDTH 1200
#define HEIGHT 800

int main(int argc, char** argv) {
    Window window(WIDTH, HEIGHT, "Engine");

    while (!window.isClosed())
    {
        window.Update();
    }

    return 0;
}