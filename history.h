#ifndef HISTORY_H
#define HISTORY_H

#include "match.h"

struct history_score {
    char* score;
    int   ocurrences;
};

typedef struct history_score history_score_t;

struct history {
    int             draws;
    int             goals[2];
    int             wons[2];
    history_score_t scores[1000];
    int             scores_arr_length;
};

typedef struct history history_t;

history_t *history_new();
void history_add_match(history_t *history, match_t *match);
void history_print(history_t *history);

#endif