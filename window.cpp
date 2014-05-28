#include "window.h"


Window::Window() {
    _initGameMap();
    g_pApplicationCursor = new Mouse;
}
Window::~Window() {
}

void Window::Render(const DQ::PointF& _ptOffset) {
    for(int i = 0; i < (int) m_vGameBlock.size(); ++i)
    {
        m_vGameBlock[i]->Render();
    }
    g_pApplicationCursor->Render();
}

void Window::Process() {
    g_pApplicationCursor->Process();
}

void Window::clearBlocks() {

    for(int i = 0; i < (int) m_vGameBlock.size(); ++i) 
    {
        delete m_vGameBlock[i];
    }
    m_vGameBlock.clear();
}
void Window::_initGameMap() {
    m_vGameBlock.clear();
    GameBlock* block;
    parserXmlMap pars("data/tiled_bit.tmx");
    for(int i = 0; i < (int) pars.getContains().size(); ++i) 
    {
        bitRow vRow = pars.getRow(i);
        for (int r = 0; r < (int) vRow.size(); ++r) 
        {
            block = createBlock((GameBlockType) vRow[r], DQ::PointI(r,i));
            if (block) m_vGameBlock.push_back(block);
        }
    }

}