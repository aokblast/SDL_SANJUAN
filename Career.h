//
// Created by blast on 2021/5/26.
//

#ifndef COMPUTER_PROGRAMMING_FINAL_PROJECT_CAREER_H
#define COMPUTER_PROGRAMMING_FINAL_PROJECT_CAREER_H
#include "Sanjuandef.h"
#include "Sanjuandata.h"

void execute_prev(player_t *player);
void execute_norm(player_t *player);
int load_career_texture();
void free_career_texture();
card_t *init_career_list();
career_t get_career(card_t *careers);
void destroy_career_list(card_t *cards);



extern card_t *careers;



#endif //COMPUTER_PROGRAMMING_FINAL_PROJECT_CAREER_H
