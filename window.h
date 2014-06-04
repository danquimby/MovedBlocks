#ifndef WINDOW_H
#define WINDOW_H

#include <list>

#include "parserXmlMap.h"
#include "mouse.h"
#include "characters.h"

static const DQ::SizeI  SizeScene = DQ::SizeI(1024,768);
static const DQ::PointF pointCentr = DQ::PointF((float) SizeScene.width() / 2.f, (float) SizeScene.height() / 2.f);

/*
* Main window.
*
*/
class Window : public AnimationMovePosition, public IDrawaibleObjects
{
public:
    Window();
    ~Window();

    // @override method for render to scene.
    void Render(const DQ::PointF& = DQ::PointF());

    // @override method for processing object.
    void Process();

    void clearBlocks();
private:
    void _initGameMap();

    // Contains game block.
    std::list<GameBlock*> m_vGameBlock;
    typedef std::list<GameBlock*>::iterator itBlock;

    // Contains complex of game block.
    std::list<GameCharacter*> m_vComplexGameBlock;
    typedef std::list<GameCharacter*>::iterator itComplexBlock;

    // Pointer main engine.
    HGE* hge;

    // Default equal wScreen / 2 , hScreen / 2.
    DQ::PointF   m_ptPositionVirtualScreen;
    DQ::PointF   m_ptVectorDirection;

    GameBlock*   m_pLastGameBlock;
    GameBlock*   m_pTargetGameBlock;
};

#endif //WINDOW_H