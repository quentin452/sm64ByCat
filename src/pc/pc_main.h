#ifndef _PC_MAIN_H
#define _PC_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

void game_deinit(void);
void game_exit(void);

void pc_request_gameloop_wait(void);
void pc_wait_for_audio(void);
bool pc_check_audio_rendering(void);
bool pc_check_gameloop_wait(void);

#ifdef __cplusplus
}
#endif

#endif // _PC_MAIN_H
