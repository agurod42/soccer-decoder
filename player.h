#ifndef PLAYER_H
#define PLAYER_H

enum player_position { GOALKEEPER, DEFENDER, MIDFIELDER, STRIKER };

struct player {
    char                 *name;
    enum player_position position;
    float                skill;
    float                athletic_decay;
    int                  experience;
};

typedef struct player player_t;

#endif