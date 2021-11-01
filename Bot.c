//
// Created by blast on 2021/6/1.
//

#include "Bot.h"
#include "GameMain.h"
#include "Card.h"
#include "Career.h"
#include "Player.h"
#include "Draw.h"
#include <stdlib.h>

extern int cost;

career_t bot_level_1_choose_career(player_t *player){
    card_t *trav = careers;
    int length = 0;
    while(trav != NULL) trav = trav->next, ++length;
    length = rand() % length;
    trav = careers;
    while(length >  0) trav = trav->next, --length;
    careers = delete_card_from_list(careers, trav);
    draw_bot_choose_msg_and_wait_for_confirm(player->playerNum, trav->cardName);
    career_t result = get_career(trav);
    free(trav);

    return result;
}

card_t * bot_level_1_choose_card(player_t *self, card_t **cards){
    card_t *chooseList = NULL, *choosen = NULL, *trav = *cards;
    int length = 0;
    switch(presentPhase){
        case PH_PRODUCER:
            while(trav != NULL){
                if(trav->buildingType == FACTORY && trav->tokens == NULL){
                    chooseList = add_card(chooseList, *trav);
                    ++length;
                }
                trav = trav->next;
            }
            if(chooseList == NULL) return NULL;
            length = rand() % length;
            trav = chooseList;
            choosen = *cards;
            while(length > 0) trav = trav->next, --length;
            while(!same_card(choosen, trav) || choosen->tokens != NULL) choosen= choosen->next;
            return choosen;
        case PH_DISCARD:
            while(trav != NULL) trav = trav->next, ++length;
            if(length == 0) return NULL;
            length = rand() % length;
            choosen = *cards;
            while(length >  0) choosen = choosen->next, --length;
            *cards = delete_card_from_list(*cards, choosen);
            return choosen;
        case PH_BUILDER:
            while(trav != NULL){
                if((trav->cost + self->cost_off) <= (self->totalHand - 1) && !check_card_on_ground(self->ground, trav)){
                    chooseList = add_card(chooseList, *trav);
                    ++length;
                }
                trav = trav->next;
            }
            if(chooseList == NULL) return NULL;
            length = rand() % length;
            trav = chooseList;
            choosen = *cards;
            while(length > 0) trav = trav->next, --length;
            while(!same_card(choosen, trav)) choosen = choosen->next;
            *cards = delete_card_from_list(*cards, choosen);
            cost = choosen->cost - ((has_Smithy(self->ground) && trav->buildingType == FACTORY) ? 1: 0) - ((has_Quarry(self->ground) && trav->buildingType == SPECIAL) ? 1: 0);
            return choosen;
        case PH_COUNCILLOR:
            trav = *cards;
            while(trav != NULL) trav = trav->next, ++length;
            if(length == 0) return NULL;
            length = rand() % length;
            choosen  = *cards;
            while(length > 0) choosen = choosen->next, --length;
            *cards = delete_card_from_list(*cards, choosen);
            return choosen;
        case PH_PROSPECTOR:
            trav = *cards;
            while(trav != NULL) trav = trav->next, ++length;
            if(length == 0) return NULL;
            length = rand() % length;
            choosen  = *cards;
            while(length > 0) choosen = choosen->next, --length;
            *cards = delete_card_from_list(*cards, choosen);
            return choosen;
        case PH_ROUND:
            trav = *cards;
            while(trav != NULL) trav = trav->next, ++length;
            if(length == 0) return NULL;
            length = rand() % length;
            choosen  = *cards;
            while(length > 0) choosen = choosen->next, --length;
            *cards = delete_card_from_list(*cards, choosen);
            return choosen;
        case PH_TRADER:
            trav = *cards;
            while (trav != NULL) {
                if (trav->buildingType == FACTORY && trav->tokens != NULL) {
                    chooseList = add_card(chooseList, *trav);
                    ++length;
                }
                trav = trav->next;

            }
            if (chooseList == NULL) {
                return NULL;
            }
            length = rand() % length;
            trav = chooseList;
            choosen = *cards;
            while(length > 0) trav = trav->next, --length;
            while(!same_card(choosen, trav)) choosen = choosen->next;
            return choosen;
        case PH_CHOOSECARD:
            while (trav != NULL) {
                ++length;
                trav = trav->next;
            }
            length = rand() % length;
            trav = *cards;
            while(length > 0) trav = trav->next, --length;
            *cards = delete_card_from_list(*cards, trav);
            return trav;
    }
}

career_t bot_level_2_choose_career(player_t *player){
    card_t *trav = careers;
    int length = 0;
    while(trav != NULL) trav = trav->next, ++length;
    length = rand() % length;
    trav = careers;
    while(length >  0) trav = trav->next, --length;
    careers = delete_card_from_list(careers, trav);
    draw_bot_choose_msg_and_wait_for_confirm(player->playerNum, trav->cardName);
    career_t result = get_career(trav);
    free(trav);

    return result;
}

card_t * bot_level_2_choose_card(player_t *self, card_t **cards){
    card_t *chooseList = NULL, *choosen = NULL, *trav = *cards;
    int maxCost = 0;
    switch(presentPhase){
        case PH_PRODUCER:
            while(trav != NULL){
                if(trav->buildingType == FACTORY && trav->tokens == NULL){
                    if(trav->cost > maxCost) choosen = trav, maxCost = trav->cost;
                }
                trav = trav->next;
            }
            return choosen;
        case PH_DISCARD:
            while(trav != NULL){
                if(trav->cost > maxCost) {
                        maxCost = trav->cost;
                        choosen = trav;
                }
                trav = trav->next;
            }
            *cards = delete_card_from_list(*cards, choosen);
            return choosen;
        case PH_BUILDER:
            while(trav != NULL){
                if((trav->cost + self->cost_off) <= (self->totalHand - 1) && !check_card_on_ground(self->ground, trav)){
                    if(trav->cost > maxCost){
                        maxCost = trav->cost;
                        choosen = trav;
                    }
                }
                trav = trav->next;
            }
            if(choosen == NULL) return NULL;
            *cards = delete_card_from_list(*cards, choosen);
            cost = choosen->cost - ((has_Smithy(self->ground) && trav->buildingType == FACTORY) ? 1: 0) - ((has_Quarry(self->ground) && trav->buildingType == SPECIAL) ? 1: 0);
            return choosen;
        case PH_COUNCILLOR:
            while(trav != NULL) {
                if(trav->cost > maxCost) {
                    maxCost = trav->cost;
                    choosen = trav;
                }
                trav = trav->next;
            }
            if(choosen == NULL) return NULL;
            *cards = delete_card_from_list(*cards, choosen);
            return choosen;
        case PH_PROSPECTOR:
            while(trav != NULL) {
                if(trav->cost > maxCost){
                    maxCost = trav->cost;
                    choosen   = trav;
                }
                trav = trav->next;
            }
            if(choosen == NULL) return NULL;
            *cards = delete_card_from_list(*cards, choosen);
            return choosen;
        case PH_ROUND:
            trav = *cards;
            maxCost = 1000;
            while(trav != NULL) {
                if(trav->cost < maxCost ) {
                    maxCost = trav->cost;
                    choosen = trav;
                }
                trav = trav->next;
            }
            if(choosen == NULL) return NULL;
            *cards = delete_card_from_list(*cards, choosen);
            return choosen;
        case PH_TRADER:
            while (trav != NULL) {
                if (trav->buildingType == FACTORY && trav->tokens != NULL) {
                    if(trav->cost > maxCost){
                        maxCost = trav->cost;
                        choosen = trav;
                    }
                }
                trav = trav->next;

            }
            if(choosen == NULL) return NULL;
            return choosen;
        case PH_CHOOSECARD:
            while (trav != NULL) {
                if(trav->cost > maxCost){
                    maxCost = trav->cost;
                    choosen = trav;
                }
                trav = trav->next;
            }
            *cards = delete_card_from_list(*cards, choosen);
            return choosen;

    }
}

void get_Bot_Func(player_t *player, int mode){
    switch(mode){
        case 1:
            player->chooseCareer = bot_level_1_choose_career;
            player->chooseCard = bot_level_1_choose_card;
            break;
        case 2:
            player->chooseCard = bot_level_2_choose_card;
            player->chooseCareer = bot_level_2_choose_career;
            break;
    }
}