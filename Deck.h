//
// Created by blast on 2021/5/29.
//

#ifndef COMPUTER_PROGRAMMING_FINAL_PROJECT_DECK_H
#define COMPUTER_PROGRAMMING_FINAL_PROJECT_DECK_H

#include "Sanjuandata.h"

extern card_t deck[128];

void shuffle();
card_t draw();
void disard_card(card_t card);

#endif //COMPUTER_PROGRAMMING_FINAL_PROJECT_DECK_H
