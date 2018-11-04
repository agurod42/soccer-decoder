#ifndef TEAM_H
#define TEAM_H

#include "player.h"

enum game_style { BALL_POSETION = 1, COUNTER_ATTACK };

struct team {
    char*           name;
    player_t        goalkeeper;
    player_t        players[10];
    int             trainer_skill;
    enum game_style style;
    int             field_factor;
};

typedef struct team team_t;

#endif