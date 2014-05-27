#ifndef MOUSE_H
#define MOUSE_H

#include "objects.h"
#include "helpers.h"
#include "hge/hgeanim.h"

struct MouseEvent {
    DQ::PointF  m_ptMousePosition;
    bool        m_bPressedLButton;
    bool        m_bPressedRButton;
};
enum MouseType {
    MOUSE_NORMAL,
    MOUSE_WAIT
};

class Mouse : public IDrawaibleObjects
{
public:
    Mouse();
    ~Mouse();

    /*
    * @param Number enum for choice view cursor.
    */
    void setMouseType(const MouseType );

    // @override method for render to scene.
    void Render(const DQ::PointF& = DQ::PointF());

    // @override method for processing object.
    void Process();

    // Get current state of mouse.
    MouseEvent getCurrentEvent() const;

private:
    hgeSprite*  m_pImageCursor;
    HGE*        m_pHGE;
    unsigned    m_nMouseType;
    HTEXTURE    m_nTextureCursor;
    MouseEvent  m_MouseEvent;
};

extern Mouse*   g_pApplicationCursor;
#endif //MOUSE_H
