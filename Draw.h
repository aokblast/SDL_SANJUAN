//
// Created by blast on 2021/6/2.
//

#ifndef COMPUTER_PROGRAMMING_FINAL_PROJECT_DRAW_H
#define COMPUTER_PROGRAMMING_FINAL_PROJECT_DRAW_H
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "Sanjuandata.h"

extern SDL_Texture *cardBack;
extern SDL_Texture *trading_1;
extern SDL_Texture *trading_2;
extern SDL_Texture *trading_3;
extern SDL_Texture *trading_4;
extern SDL_Texture *trading_5;

void draw_ground();
void draw_choose_card(card_t *cards);
card_t *get_choose(card_t *cards, SDL_Point *point);
bool in_ConfirmButton(SDL_Point point);
bool draw_confirm_msg_and_choose_answer(char *msg);
void draw_bot_choose_msg_and_wait_for_confirm(int playerID, void *param);



#endif //COMPUTER_PROGRAMMING_FINAL_PROJECT_DRAW_H
