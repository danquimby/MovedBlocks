#include "window.h"

Window::Window() {
    g_pApplicationCursor = new Mouse;
    _initGameMap();

    // Set default virtual center.
    m_ptPositionVirtualScreen = pointCentr;
    m_ptPositionVirtualScreen = m_ptPositionVirtualScreen.negative();
  //  m_ptPositionVirtualScreen = m_vGameBlock[m_vGameBlock.size() - 1]->positionView().negative();
}

Window::~Window() {
}

void Window::Render(const DQ::PointF& _ptOffset) {
    DQ::PointF vec = m_ptPositionVirtualScreen + pointCentr;
    for(iterator it = m_vGameBlock.begin(); it != m_vGameBlock.end(); it++)
    {
        (*it)->Render(vec);
    }
    g_pApplicationCursor->Render();
}

void Window::Process() {
    hge = DQ::cloneHGE();
    g_pApplicationCursor->Process();

    if (hge->Input_GetKeyState(HGEK_LEFT)) 
    {
        m_ptPositionVirtualScreen.setX(m_ptPositionVirtualScreen.X() + 1.f);
    }
    if (hge->Input_GetKeyState(HGEK_RIGHT)) 
    {
        m_ptPositionVirtualScreen.setX(m_ptPositionVirtualScreen.X() - 1.f);
    }
    if (hge->Input_GetKeyState(HGEK_DOWN)) 
    {
        m_ptPositionVirtualScreen.setY(m_ptPositionVirtualScreen.Y() - 1.f);
    }
    if (hge->Input_GetKeyState(HGEK_UP)) 
    {
        m_ptPositionVirtualScreen.setY(m_ptPositionVirtualScreen.Y() + 1.f);
    }

    MouseEvent evt = g_pApplicationCursor->getCurrentEvent();
    if (evt.m_bPressedLButton) {
        DQ::PointF vec = m_ptPositionVirtualScreen + pointCentr;
        for(iterator it = m_vGameBlock.begin(); it != m_vGameBlock.end(); it++)
        {
            DQ::RectF rtAreaObject((*it)->positionView(), DQ::Size<float> (SPRITE_WIDTH, SPRITE_HEIGHT));
            rtAreaObject += vec;
            if (rtAreaObject.entrance(evt.m_ptMousePosition))
            {
                // Hit to object.
            }
        }

    }
}

void Window::clearBlocks() {

    for(iterator it = m_vGameBlock.begin(); it != m_vGameBlock.end(); it++)
    {
        delete (*it);
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