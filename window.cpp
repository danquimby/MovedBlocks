#include "window.h"

GameBlock* block;

Window::Window() {
    g_pApplicationCursor = new Mouse;
    block = new GameBlock(GAME_BLOCK_TREE1);
    block->setPositionObject(DQ::PointI(1,0));
}
Window::~Window() {
}

void Window::Render(const DQ::PointF& _ptOffset) {
    block->Render();
    g_pApplicationCursor->Render();
}

void Window::Process() {
    g_pApplicationCursor->Process();
}
