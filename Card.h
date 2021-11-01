//
// Created by blast on 2021/5/26.
//

#ifndef COMPUTER_PROGRAMMING_FINAL_PROJECT_CARD_H
#define COMPUTER_PROGRAMMING_FINAL_PROJECT_CARD_H
#include "Sanjuandata.h"
#include <stdbool.h>

void init_deck();
int load_card_texture();
void destroy_card_texture();
void check_effect(player_t *player);
card_t *add_card(card_t *cards, card_t newCard);
card_t *delete_card_from_list(card_t *cardList, card_t *card);
card_t *choose_card(card_t *cards);
bool same_card(card_t *cards1, card_t *cards2);
bool has_crane(card_t *ground);
bool has_library(card_t *ground);
bool has_MarketHall(card_t *ground);
bool has_marketStand(card_t *ground);
bool has_palace(card_t *ground);
bool has_poorHouse(card_t *ground);
bool has_preFecture(card_t *ground);
bool has_Quarry(card_t *ground);
bool has_Smithy(card_t *ground);
bool has_Well(card_t *ground);
bool has_Archive(card_t *ground);
bool has_BlackMarket(card_t *ground);
void free_card_list(card_t *card);
void discard_all_card(card_t *cards);
void get_Price();
int sell(card_t *card);
extern card_t indigoPlant;



#endif //COMPUTER_PROGRAMMING_FINAL_PROJECT_CARD_H
