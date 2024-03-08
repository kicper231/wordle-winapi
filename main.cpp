
#define NOMINMAX
#include "wordle.h"
#include "game.h"



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    wordle app{ hInstance };
    

        
        app.run(nCmdShow);
        
        return 0;
}
