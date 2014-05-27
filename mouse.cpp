#include "mouse.h"

Mouse* g_pApplicationCursor = 0;

Mouse::Mouse() {
    m_nMouseType = MOUSE_NORMAL;
    m_pHGE = DQ::cloneHGE();

#ifdef _DEBUG
    m_nTextureCursor = m_pHGE->Texture_Load("../data/cursor.png");
#else
    m_nTextureCursor = m_pHGE->Texture_Load("data/cursor.png");
#endif
    m_pImageCursor = new hgeSprite(m_nTextureCursor,0,0,32,32);
}

Mouse::~Mouse() {
    m_pHGE->Texture_Free(m_nTextureCursor);
    delete m_pImageCursor;
}

void Mouse::setMouseType(const MouseType _type) {
    m_nMouseType = _type;
}

void Mouse::Render() {
    m_pImageCursor->Render(m_MouseEvent.m_ptMousePosition.X(), m_MouseEvent.m_ptMousePosition.Y());
}

void Mouse::Process() {
    float xPos, yPos;
    m_pHGE->Input_GetMousePos(&xPos, &yPos);
    m_MouseEvent.m_ptMousePosition = DQ::PointF(xPos, yPos);
    m_MouseEvent.m_bPressedLButton = m_pHGE->Input_GetKeyState(HGEK_LBUTTON);
    m_MouseEvent.m_bPressedRButton = m_pHGE->Input_GetKeyState(HGEK_RBUTTON);
}

MouseEvent Mouse::getCurrentEvent() const {
    return m_MouseEvent;
}