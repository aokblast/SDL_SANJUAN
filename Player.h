//
// Created by blast on 2021/5/31.
//

#ifndef COMPUTER_PROGRAMMING_FINAL_PROJECT_PLAYER_H
#define COMPUTER_PROGRAMMING_FINAL_PROJECT_PLAYER_H

#include "Sanjuandata.h"
#include "stdbool.h"

player_t *init_player(int playerNum, int initCard);
void clear_player(player_t *player);
card_t *player_choose_Card(player_t *self, card_t **cards);
career_t player_choose_career(player_t *self);
bool check_card_on_ground(card_t *ground, card_t *card);

#endif //COMPUTER_PROGRAMMING_FINAL_PROJECT_PLAYER_H
