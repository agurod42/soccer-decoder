#ifndef MATCH_C
#define MATCH_C

#include <stdlib.h>

#include "distributions.h"
#include "match.h"

#define MATCH_ACTIONS 100
#define MATCH_DURATION_SECS 90 * 60

match_t *match_new(team_t team_a, team_t team_b) {
    match_t *match = malloc(sizeof(match_t));
    match->team_a = malloc(sizeof(match_team_t));
    *match->team_a = (match_team_t) { team_a.name, 0, 0, 0, 0 };
    match->team_b = malloc(sizeof(match_team_t));
    *match->team_b = (match_team_t) { team_b.name, 0, 0, 0, 0 };
    match->attacking_team = match->team_a;
    match->defending_team = match->team_b;
    match->current_field_zone = MIDFIELD;
    match->score_a = match->score_b = 0;
    match->team_a->goalkeeper_skill = team_a.goalkeeper.skill;
    match->team_b->goalkeeper_skill = team_b.goalkeeper.skill;

    for (int i = 0; i < 10; i++) {
        match_team_t* match_teams[] = { match->team_a, match->team_b };
        team_t teams[] = { team_a, team_b };
        for (int j = 0; j < 2; j++) {
            switch (teams[j].players[i].position) {
                case GOALKEEPER: // to avoid -Wswitch
                    break;
                case DEFENDER:
                    match_teams[j]->defensive_skill += teams[j].players[i].skill;
                    break;
                case MIDFIELDER:
                    match_teams[j]->defensive_skill += 0.5 * teams[j].players[i].skill;
                    match_teams[j]->midfield_skill  += teams[j].players[i].skill;
                    match_teams[j]->offensive_skill += 0.5 * teams[j].players[i].skill;
                    break;
                case STRIKER:
                    match_teams[j]->offensive_skill += teams[j].players[i].skill;
                    break;
            }
        }
    }

    return match;
}

match_t *match_simulate(team_t team_a, team_t team_b) {
    match_t *match = match_new(team_a, team_b);
    
    for (int i = 0; i < MATCH_ACTIONS; i++) {
        match_team_t *battle_winner = match_battle(match);
        if (battle_winner == match->attacking_team) {
            if (match->attacking_team == match->team_a) {
                if (match->current_field_zone == GOAL_B) {
                    match->score_a++;
                    match->current_field_zone = MIDFIELD;
                    match_change_ball(match);
                } else {
                    match->current_field_zone++;
                }
            } else /* if (match->attacking_team == match->team_b) */ {
                if (match->current_field_zone == GOAL_A) {
                    match->score_b++;
                    match->current_field_zone = MIDFIELD;
                    match_change_ball(match);
                } else {
                    match->current_field_zone--;
                }
            }
        } else {
            match->current_field_zone = MIDFIELD;
            match_change_ball(match);
        }
    }

    return match;
}

match_team_t *match_battle(match_t *match) {
    float team_a_skill = 0;
    float team_d_skill = 0;

    switch (match->current_field_zone) {
        case FIELD_A:
        case FIELD_B:
            team_a_skill = match->attacking_team->offensive_skill;
            team_d_skill = match->defending_team->defensive_skill;
            break;
        case GOAL_A:
        case GOAL_B:
            team_a_skill = match->attacking_team->offensive_skill;
            team_d_skill = match->defending_team->goalkeeper_skill;
            break;
        case MIDFIELD:
            team_a_skill = match->attacking_team->midfield_skill;
            team_d_skill = match->defending_team->midfield_skill;
            break;
    }

    float random_a = randomGamma(team_a_skill, 0.5);
    float random_d = randomGamma(team_d_skill, 0.5);

    if (random_a > random_d) {
        return match->attacking_team;
    } else {
        return match->defending_team;
    }
}

void match_change_ball(match_t *match) {
    match->attacking_team = match->attacking_team == match->team_a ? match->team_b : match->team_a;
    match->defending_team = match->defending_team == match->team_a ? match->team_b : match->team_a;
}

#endif