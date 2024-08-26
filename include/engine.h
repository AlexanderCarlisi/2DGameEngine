#ifndef ENGINE_H
#define ENGINE_H

#define STATE_RUNNING 0
#define STATE_ENDED 1

void engine_start();
void set_state(int newState);
// int get_state();

#endif