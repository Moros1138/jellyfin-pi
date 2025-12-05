#include <mpv/client.h>
#include "raylib.h"
#include "rlgl.h"

#include <iostream>
#include <stdlib.h>

//------------------------------------------------------------------------------------
// Global Varialbes
//------------------------------------------------------------------------------------
const int screenWidth = 1280;
const int screenHeight = 720;

//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// Update
//------------------------------------------------------------------------------------
void update()
{
    // Update
    //----------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
        // clear canvas to color
        ClearBackground(PURPLE);
        
        // draw yellow border
        DrawRectangleLinesEx({0.5f, -0.5f, screenWidth, screenHeight + 0.5f}, 1.0f, YELLOW);
        
        // draw fps
        DrawFPS(5, 5);

    EndDrawing();
    
    //----------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "raylib - PGEtinker Classic Example");
    
#if(__EMSCRIPTEN__)
    // Set our game to run at 60 frames-per-second
    emscripten_set_main_loop(update, 60, 1);
#else
    SetTargetFPS(0);

    // Main game loop
    while(!WindowShouldClose())
    {
        update();
    }
#endif
    
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

// int main(int argc, char* argv[])
// {
//     if(argc != 2)
//         return -1;

//     mpv_handle *ctx = mpv_create();
    
//     mpv_initialize(ctx);
    
//     const char *cmd[] = {"loadfile", argv[1], NULL};
    
//     mpv_command(ctx, cmd);
//     while(true)
//     {
//         mpv_event *event = mpv_wait_event(ctx, -1);
//         if (event->event_id == MPV_EVENT_SHUTDOWN)
//             break;
//     }

//     mpv_terminate_destroy(ctx);
//     return 0;
// }

