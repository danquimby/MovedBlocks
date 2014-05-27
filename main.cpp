

#include "helpers.h"
#include <math.h>

#include <vector>

#pragma comment (lib, "hge.lib")
#pragma comment (lib, "hgehelp.lib")
#pragma comment (lib, "tinyxmlD.lib")


HGE *hge = 0;

hgeSprite*	sprite;
bool FrameFunc()
{
    if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;
    //		pGame->process();
    return false;
}
bool RenderFunc()
{
    hge->Gfx_BeginScene();
    hge->Gfx_Clear(0xff000000);
    sprite->Render(0,0);
    //		pGame->draw();
    hge->Gfx_EndScene();
    return false;

}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{


    hge = hgeCreate(HGE_VERSION);
    if (!hge){
        //MessageBox(NULL, (LPCTSTR)hge->System_GetErrorMessage(), (LPCTSTR)"Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
        return 1;
    }
    hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
    hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
    hge->System_SetState(HGE_TITLE, "tittle ");
    hge->System_SetState(HGE_WINDOWED, true);
    hge->System_SetState(HGE_USESOUND, false);
    hge->System_SetState(HGE_SCREENWIDTH, 1024);
    hge->System_SetState(HGE_SCREENHEIGHT, 768);
    hge->System_SetState(HGE_SCREENBPP, 32);

    if(hge->System_Initiate())
    {
        hge->System_Start();
    }
    hge->System_Shutdown();
    hge->Release();

    return 0;
}

