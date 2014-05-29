#ifndef WINDOW_H
#define WINDOW_H


#include "parserXmlMap.h"
#include "mouse.h"

static const DQ::SizeI  SizeScene = DQ::SizeI(1024,768);
static const DQ::PointF pointCentr = DQ::PointF((float) SizeScene.Width() / 2.f, (float) SizeScene.Height() / 2.f);

/*
* Main window.
*
*/
class Window : public IDrawaibleObjects
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
    std::vector<GameBlock*> m_vGameBlock;

    // Pointer main engine.
    HGE* hge;

    // Default equal wScreen / 2 , hScreen / 2.
    DQ::PointF   m_ptPositionVirtualScreen;
    DQ::PointF   m_ptVectorDirection;
};

#endif //WINDOW_H