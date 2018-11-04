#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "history.h"
#include "match.h"
#include "player.h"
#include "team.h"

int main(int argc, char** argv) {
    team_t team_a = (team_t) {
        "Blue Team",
        (player_t) { "G1", GOALKEEPER, 8.0, 0.25, 1 },
        {
            (player_t) { "D1", DEFENDER, 9.0, 0.25, 1 },
            (player_t) { "D2", DEFENDER, 8.0, 0.25, 1 },
            (player_t) { "D3", DEFENDER, 9.0, 0.25, 1 },
            (player_t) { "M1", MIDFIELDER, 7.5, 0.25, 1 },
            (player_t) { "M2", MIDFIELDER, 8.0, 0.25, 1 },
            (player_t) { "M3", MIDFIELDER, 9.0, 0.25, 1 },
            (player_t) { "M4", MIDFIELDER, 7.5, 0.25, 1 },
            (player_t) { "M5", MIDFIELDER, 9.0, 0.25, 1 },
            (player_t) { "S1", STRIKER, 8.5, 0.25, 1 },
            (player_t) { "S2", STRIKER, 8.5, 0.25, 1 }
        },
        BALL_POSETION,
        76
    };

    team_t team_b = (team_t) {
        "Red Team",
        (player_t) { "G1", GOALKEEPER, 9.0, 0.25, 1 },
        {
            (player_t) { "D1", DEFENDER, 8.5, 0.25, 1 },
            (player_t) { "D2", DEFENDER, 7.0, 0.25, 1 },
            (player_t) { "D3", DEFENDER, 7.0, 0.25, 1 },
            (player_t) { "D4", DEFENDER, 7.5, 0.25, 1 },
            (player_t) { "M1", MIDFIELDER, 9.0, 0.25, 1 },
            (player_t) { "M2", MIDFIELDER, 9.0, 0.25, 1 },
            (player_t) { "M3", MIDFIELDER, 9.5, 0.25, 1 },
            (player_t) { "M4", MIDFIELDER, 10.0, 0.25, 1 },
            (player_t) { "S1", STRIKER, 8.0, 0.25, 1 },
            (player_t) { "S2", STRIKER, 7.0, 0.25, 1 }
        },
        COUNTER_ATTACK,
        84
    };

    srand(time(NULL));

    history_t *history = history_new();

    for (int i = 0; i < 1000; i++) {
        match_t *match = match_simulate(team_a, team_b);
        
        history_add_match(history, match);

        free(match->team_a);
        free(match->team_b);
        free(match);
    }

    history_print(history);
}