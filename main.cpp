#include "window.h"

#pragma comment (lib, "hge.lib")
#pragma comment (lib, "hgehelp.lib")
#pragma comment (lib, "tinyxmlD.lib")

HGE *hge = 0;

Window* window;

// Main process loop.
bool FrameFunc()
{
    if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;
    window->Process();
    return false;
}

// Main draw loop.
bool RenderFunc()
{
    hge->Gfx_BeginScene();
    hge->Gfx_Clear(DQ::colorConvert("gray").convertToDword());

    window->Render();

    hge->Gfx_EndScene();
    return false;

}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    hge = DQ::cloneHGE();
    if (!hge) return 1;

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
        window = new Window;
        hge->System_Start();
    }
    hge->System_Shutdown();
    hge->Release();

    return 0;
}

