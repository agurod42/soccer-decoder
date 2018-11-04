#ifndef HISTORY_C
#define HISTORY_C

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "history.h"

history_t *history_new() {
    history_t *history = malloc(sizeof(history_t));
    *history = (history_t) {
        0,
        { 0, 0 },
        { 0, 0 },
        {},
        0
    };
    return history;
}

void history_add_match(history_t *history, match_t *match) {
    if (match->score_a > match->score_b) {
        history->wons[0]++;
    }
    else if (match->score_a < match->score_b) {
        history->wons[1]++;
    }
    else {
        history->draws++;
    }

    history->goals[0] += match->score_a;
    history->goals[1] += match->score_b;

    char* match_score = malloc(sizeof(char) * 6);
    snprintf(match_score, 6, "%2d-%2d", match->score_a, match->score_b);

    for (int i = 0; i < history->scores_arr_length; i++) {
        if (strcmp(history->scores[i].score, match_score) == 0) {
            history->scores[i].ocurrences++;
            return;
        }
    }

    history->scores[history->scores_arr_length] = (history_score_t) { match_score, 1 };
    history->scores_arr_length++;
}

void history_print(history_t *history) {
    printf("team a wons: %d\r\n", history->wons[0]);
    printf("team b wons: %d\r\n", history->wons[1]);
    printf("draws: %d\r\n", history->draws);
    printf("team a goals: %d\r\n", history->goals[0]);
    printf("team b goals: %d\r\n", history->goals[1]);
    printf("scores:\r\n");
    for (int i = 0; i < history->scores_arr_length; i += sizeof(history_score_t)) {
        printf("  %s: %d\r\n", history->scores[i].score, history->scores[i].ocurrences);
    }
}

#endif