#include "window.h"

Window::Window() {
    m_pLastGameBlock = 0;
    g_pApplicationCursor = new Mouse;
    _initGameMap();

    // Set default virtual center.
    m_ptPositionVirtualScreen.clean(); /*= pointCentr*/;
}

Window::~Window() {
}

void Window::Render(const DQ::PointF& _ptOffset) {
    DQ::PointF vec = m_ptPositionVirtualScreen + pointCentr;
    for(itBlock it = m_vGameBlock.begin(); it != m_vGameBlock.end(); it++)
    {
        (*it)->Render(vec);
    }
    for(itComplexBlock it = m_vComplexGameBlock.begin(); it != m_vComplexGameBlock.end(); it++)
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
        for(itBlock it = m_vGameBlock.begin(); it != m_vGameBlock.end(); it++)
        {
            DQ::RectF rtAreaObject(calculationFromGrid((*it)->positionGrid()), DQ::Size<float> (SPRITE_WIDTH, SPRITE_HEIGHT));
            rtAreaObject += vec;
            if (rtAreaObject.entrance(evt.m_ptMousePosition))
            {
                // Hit to object.
                if (m_pLastGameBlock) 
                {
                    m_pTargetGameBlock = (*it);
                    setNewPositionsForMoved(calculationFromGrid(m_pLastGameBlock->positionGrid()), calculationFromGrid(m_pTargetGameBlock->positionGrid()));
                    Sleep(200);
                }
            }
        }
    }
    if (m_nSpeed > 0.f) 
    {// if m_nSpeed equal 0 than position target equal position object.
        m_ptPositionVirtualScreen += updatePositions();
        m_pLastGameBlock = m_pTargetGameBlock;

    }

}

void Window::clearBlocks() {

    for(itBlock it = m_vGameBlock.begin(); it != m_vGameBlock.end(); it++)
    {
        delete (*it);
    }
    for(itComplexBlock it = m_vComplexGameBlock.begin(); it != m_vComplexGameBlock.end(); it++)
    {
        delete (*it);
    }
    m_vComplexGameBlock.clear();
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
    m_pLastGameBlock = (*m_vGameBlock.begin());

    for(int i = 0; i < (int) pars.getComplexObjects().size(); ++i)
    {
        BitObjectItem item = pars.getComplexObjects()[i];
        m_vComplexGameBlock.push_back(
            new GameCharacter(item.m_pPosition,BodyComplex(ContainsComplexObject(item.m_szSizeObject,item.m_sData)))
            );
    }
    
    //character = new GameCharacter(DQ::PointI(1,1),BodyComplex(ContainsComplexObject(DQ::SizeI(2,2),"1,1,2,2",",")));
}