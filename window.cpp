#include "window.h"


Window::Window() {
    g_pApplicationCursor = new Mouse;
}
Window::~Window() {
}

void Window::Render() {
    g_pApplicationCursor->Render();
}

void Window::Process() {
    g_pApplicationCursor->Process();
}
