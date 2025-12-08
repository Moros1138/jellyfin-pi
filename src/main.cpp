#include <mpv/client.h>

int main(int argc, char* argv[])
{
    if(argc != 2)
        return -1;

    mpv_handle *ctx = mpv_create();
    
    mpv_initialize(ctx);
    
    const char *cmd[] = {"loadfile", argv[1], NULL};
    
    mpv_command(ctx, cmd);
    while(true)
    {
        mpv_event *event = mpv_wait_event(ctx, -1);
        if (event->event_id == MPV_EVENT_SHUTDOWN)
            break;
    }

    mpv_terminate_destroy(ctx);
    return 0;
}
