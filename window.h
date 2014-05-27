#ifndef WINDOW_H
#define WINDOW_H


#include "mouse.h"
#include "helpers.h"

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
    void Render();

    // @override method for processing object.
    void Process();

private:

};

#endif //WINDOW_H