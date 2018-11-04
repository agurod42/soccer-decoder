#ifndef MATCH_H
#define MATCH_H

#include "team.h"

enum field_zone { GOAL_A = 1, FIELD_A, MIDFIELD, FIELD_B, GOAL_B };

struct match_team {
    char  *name;
    float goalkeeper_skill;
    float defensive_skill;
    float midfield_skill;
    float offensive_skill;
};

typedef struct match_team match_team_t;

struct match {
    match_team_t    *team_a, *team_b;
    match_team_t    *attacking_team, *defending_team;
    enum field_zone current_field_zone;
    int             score_a, score_b;
};

typedef struct match match_t;

match_t *match_simulate(team_t team_a, team_t team_b);
match_team_t *match_battle(match_t *match);
void match_change_ball(match_t *match);

#endif