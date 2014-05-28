#ifndef WINDOW_H
#define WINDOW_H


#include "parserXmlMap.h"
#include "mouse.h"

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

    std::vector<GameBlock*> m_vGameBlock;
};

#endif //WINDOW_H