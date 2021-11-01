//
// Created by blast on 2021/5/31.
//

#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include "GameMain.h"
#include "Draw.h"
#include "Window.h"
#include "Career.h"

extern char USE_CRANE_TEXT[40];
extern int cost;

player_t *init_player(int playerNum, int initCard){
    player_t *result = calloc(1, sizeof(player_t));
    result->hand = NULL;
    result->totalHand = 0;
    for(int i = 0; i < initCard; ++i){
        result->hand = add_card(result->hand, draw());
        ++result->totalHand;
    }
    result->ground = add_card(NULL, indigoPlant);
    result->victoryPoint = result->totalBuilding = result->cost_off = 0 ;
    result->totalBuilding = 1;
    result->totalPerSell = result->totalPerProduce = 1;
    result->maxCost = 100;
    result->maxHand = 7;
    result->playerNum = playerNum;
    result->privillageTimes = 1;

    return result;
}

void clear_player(player_t *player){
    free_card_list(player->ground);
    free_card_list(player->hand);
    free(player);
}

card_t *player_choose_Card(player_t *self, card_t **cards){
    card_t *chooseList = NULL, *choosen = NULL, *trav = *cards, *card;
    switch(presentPhase){
        case PH_PRODUCER:
            while(trav != NULL){
                if(trav->buildingType == FACTORY && trav->tokens == NULL){
                    chooseList = add_card(chooseList, *trav);
                }
                trav = trav->next;
            }
            if(chooseList == NULL) return NULL;
            draw_ground();
            draw_choose_card(chooseList);
            SDL_RenderPresent(main_window_renderer);
            choosen = choose_card(chooseList);
            if(choosen == NULL) return   NULL;
            trav = *cards;
            while(!same_card(choosen, trav) || trav->tokens != NULL) trav = trav->next;
            return trav;
        case PH_DISCARD:
            if(*cards == NULL) return NULL;
            draw_ground();
            draw_choose_card(*cards);
            SDL_RenderPresent(main_window_renderer);
            choosen = choose_card(*cards);
            *cards = delete_card_from_list(*cards, choosen);
            return choosen;
        case PH_BUILDER:
            if(has_crane(self->ground) && draw_confirm_msg_and_choose_answer(USE_CRANE_TEXT)) {
                int maxCost = 0;
                for(trav = self->ground; trav != NULL; trav = trav->next) maxCost = (trav->cost > maxCost) ? trav->cost : maxCost;
                trav = *cards;
                while(trav != NULL){
                    if((trav->cost + self->cost_off - maxCost  - ((has_Smithy(self->ground) && trav->buildingType == FACTORY) ? 1: 0) - ((has_Quarry(self->ground) && trav->buildingType == SPECIAL) ? 1: 0))<= (self->totalHand - 1 ))  {
                        chooseList = add_card(chooseList, *trav);
                    }
                    trav = trav->next;
                }
                if(chooseList == NULL) return  NULL;
                draw_ground();
                draw_choose_card(chooseList);
                SDL_RenderPresent(main_window_renderer);
                choosen = choose_card(chooseList);
                if(choosen == NULL) return NULL;
                trav = *cards;
                while(!same_card(trav, choosen)) trav = trav->next;
                free_card_list(chooseList);
                self->hand = delete_card_from_list(self->hand, trav);
                chooseList = NULL;
                for(card = self->ground; card != NULL; card = card->next) if(trav->cost + self->cost_off - card->cost - (has_Smithy(self->ground) && trav->buildingType == FACTORY ? 1: 0) - (has_Quarry(self->ground) && trav->buildingType == SPECIAL ? 1: 0)<= self->totalHand - 1 ) chooseList = add_card(chooseList, *card);
                draw_ground();
                draw_choose_card(chooseList);
                SDL_RenderPresent(main_window_renderer);
                presentPhase = PH_DISCARD;
                choosen = choose_card(chooseList);
                if(choosen == NULL) return NULL;
                for(card = self->ground; !same_card(card, choosen); card = card->next);
                self->ground = delete_card_from_list(self->ground, card);
                --self->totalBuilding;
                free_card_list(chooseList);
                discard_all_card(card->tokens);
                disard_card(*card);
                presentPhase = PH_BUILDER;
                cost = trav->cost - card->cost - ((has_Smithy(self->ground) && trav->buildingType == FACTORY) ? 1: 0) - ((has_Quarry(self->ground) && trav->buildingType == SPECIAL) ? 1: 0);
                free(card);
                return trav;
            }else {
                while (trav != NULL) {
                    if ((trav->cost + self->cost_off - ((has_Smithy(self->ground) && trav->buildingType == FACTORY) ? 1: 0) - ((has_Quarry(self->ground) && trav->buildingType == SPECIAL) ? 1: 0)) <= (self->totalHand - 1) &&
                        !check_card_on_ground(self->ground, trav)) {
                        chooseList = add_card(chooseList, *trav);
                    }
                    trav = trav->next;
                }
                if (chooseList == NULL) return NULL;
                draw_ground();
                draw_choose_card(chooseList);
                SDL_RenderPresent(main_window_renderer);
                choosen = choose_card(chooseList);
                if (choosen == NULL) return NULL;
                trav = *cards;
                while (!same_card(choosen, trav)) trav = trav->next;
                *cards = delete_card_from_list(*cards, trav);
                cost = trav->cost - ((has_Smithy(self->ground) && trav->buildingType == FACTORY) ? 1: 0) - ((has_Quarry(self->ground) && trav->buildingType == SPECIAL) ? 1: 0);
                return trav;
            }
        case PH_COUNCILLOR:
            if(*cards == NULL) return NULL;
            draw_ground();
            draw_choose_card(*cards);
            SDL_RenderPresent(main_window_renderer);
            choosen = choose_card(*cards);
            if(choosen == NULL) return  NULL;
            *cards = delete_card_from_list(*cards, choosen);
            return choosen;
        case PH_PROSPECTOR:
            draw_ground();
            draw_choose_card(*cards);
            SDL_RenderPresent(main_window_renderer);
            choosen = choose_card(*cards);
            *cards = delete_card_from_list(*cards, choosen);
            return choosen;
        case PH_ROUND:
            if(*cards == NULL) return NULL;
            draw_ground();
            draw_choose_card(*cards);
            SDL_RenderPresent(main_window_renderer);
            choosen = choose_card(*cards);
            if(choosen == NULL) return  NULL;
            *cards = delete_card_from_list(*cards, choosen);
            return choosen;
        case PH_TRADER:
            trav = *cards;
            while (trav != NULL) {
                if (trav->buildingType == FACTORY && trav->tokens != NULL) {
                    chooseList = add_card(chooseList, *trav);
                }
                trav = trav->next;

            }
            if (chooseList == NULL) {
                return NULL;
            }
            draw_ground();
            draw_choose_card(chooseList);
            SDL_RenderPresent(main_window_renderer);
            choosen = choose_card(chooseList);
            if(choosen == NULL) return NULL;
            trav = *cards;
            while(!same_card(choosen, trav)) trav = trav->next;
            return trav;
        case PH_CHOOSECARD:
            chooseList = *cards;
            draw_ground();
            draw_choose_card(chooseList);
            SDL_RenderPresent(main_window_renderer);
            if(chooseList == NULL) return NULL;
            choosen = choose_card(chooseList);
            if(choosen == NULL) return NULL;
            *cards = delete_card_from_list(*cards, choosen);
            return choosen;

    }
}


career_t player_choose_career(player_t *self){
    SDL_RenderClear(main_window_renderer);
    draw_ground();
    draw_choose_card(careers);
    SDL_RenderPresent(main_window_renderer);
    card_t *career = choose_card(careers);
    careers = delete_card_from_list(careers, career);
    return get_career(career);
}

bool check_card_on_ground(card_t *ground, card_t *card){
    if(card->buildingType == FACTORY) return false;
    while(ground != NULL){
        if(same_card(ground, card)) return true;
        ground = ground->next;
    }
    return false;
}