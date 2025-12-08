#include "raylib.h"
#include "rlgl.h"

#include <mpv/client.h>
#include <mpv/render_gl.h>

#include <string.h>

bool mpvHasEvents = false;
bool mpvHasRenderUpdate = false;

static void *get_proc_address_mpv(void* fn_ctx, const char* name)
{
    return rlGetProcAddress(name);
}

static void on_mpv_events(void* ctx)
{
    mpvHasEvents = true;
}

static void on_mpv_render_update(void* ctx)
{
    mpvHasRenderUpdate = true;
}

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "raylib - PGEtinker Classic Example");
    
    SetTargetFPS(60);

    // create a framebuffer to use with mpv
    RenderTexture2D mpv_target = LoadRenderTexture(screenWidth, screenHeight);
    
    mpv_handle* mpv = mpv_create();
    if(!mpv)
    {
        TraceLog(LOG_FATAL, "mpv: context init failed.");
    }
    
    // use libmpv module for output
    mpv_set_option_string(mpv, "vo", "libmpv");

    if(mpv_initialize(mpv) < 0)
    {
        TraceLog(LOG_FATAL, "mpv: init failed.");
    }

    // tell mpv to give me all the debug messages
    mpv_request_log_messages(mpv, "debug");
    mpv_opengl_init_params ogl_params[] = {{
        .get_proc_address = get_proc_address_mpv,
    }};
    mpv_render_param params[] = {
        {MPV_RENDER_PARAM_API_TYPE, (void*)MPV_RENDER_API_TYPE_OPENGL},
        {MPV_RENDER_PARAM_OPENGL_INIT_PARAMS, ogl_params},
        {MPV_RENDER_PARAM_ADVANCED_CONTROL, (int[]){1}},
        {MPV_RENDER_PARAM_INVALID},
    };

    mpv_render_context* mpv_gl;
    if(mpv_render_context_create(&mpv_gl, mpv, params) < 0)
    {
        TraceLog(LOG_FATAL, "mpv: failed to initialize mpv GL context");
    }
    mpv_set_wakeup_callback(mpv, on_mpv_events, NULL);
    mpv_render_context_set_update_callback(mpv_gl, on_mpv_render_update, NULL);
    
    const char* cmd[] = {"loadfile", "video.mp4", NULL};
    mpv_command_async(mpv, 0, cmd);

    // Main game loop
    while(!WindowShouldClose())
    {
        bool mpvRedraw = false;

        if(mpvHasEvents)
        {
            while(true)
            {
                mpv_event* e = mpv_wait_event(mpv, 0);
                if(e->event_id == MPV_EVENT_NONE)
                {
                    break;
                }

                if(e->event_id == MPV_EVENT_LOG_MESSAGE)
                {
                    mpv_event_log_message* msg = (mpv_event_log_message*)e->data;
                    if(strstr(msg->text, "DR image"))
                    {
                        TraceLog(LOG_INFO, "mpv: %s", msg->text);
                    }

                    continue;
                }
                TraceLog(LOG_INFO, "mpv event: %s", mpv_event_name(e->event_id));
            }
            // reset trigger
            mpvHasEvents = false;
        }

        if(mpvHasRenderUpdate)
        {
            uint64_t flags = mpv_render_context_update(mpv_gl);
            if(flags & MPV_RENDER_UPDATE_FRAME)
            {
                mpvRedraw = true;
            }
            
            // reset trigger
            mpvHasRenderUpdate = false;
        }

        BeginDrawing();
            if(mpvRedraw)
            {
                BeginTextureMode(mpv_target);
                    mpv_opengl_fbo fbo[] = {{
                        .fbo = (int)mpv_target.id,
                        .w = mpv_target.texture.width,
                        .h = mpv_target.texture.height,
                    }};
                    mpv_render_param params[] = {
                        {MPV_RENDER_PARAM_OPENGL_FBO, fbo},
                        {MPV_RENDER_PARAM_FLIP_Y, (int[]){1}},
                        {MPV_RENDER_PARAM_INVALID},
                    };
                    rlEnableFramebuffer(mpv_target.id);
                    mpv_render_context_render(mpv_gl, params);
                    rlDisableFramebuffer();
                EndTextureMode();
            }

            ClearBackground(PURPLE);
            DrawTexture(mpv_target.texture, 0, 0, WHITE);
            DrawRectangleLinesEx({0.5f, -0.5f, screenWidth - 0.5f, screenHeight + 0.5f}, 1.0f, YELLOW);
            DrawFPS(5, 5);
        EndDrawing();


    }
    
    mpv_render_context_free(mpv_gl);
    UnloadRenderTexture(mpv_target);
    mpv_destroy(mpv);
    CloseWindow();

    return 0;
}

