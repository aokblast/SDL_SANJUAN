//
// Created by blast on 2021/5/26.
//

#include "Deck.h"
#include "Card.h"
#include "GameMain.h"
#include "Window.h"
#include "Draw.h"
#include "Button.h"
#include "Sound.h"
#include <SDL2/SDL_image.h>


static card_t builder;
static card_t councillor;
static card_t producer;
static card_t prospector;
static card_t trader;

extern char CAREER_COUNCILOR[20];
extern char CAREER_PRUDUCER[20];
extern char CAREER_PROSPECTOR[20];
extern char CAREER_TRADER[20];
extern char CAREER_BUILDER[20];

int cost = 0;


void trader_action(player_t *player){
    check_effect(player);
    presentPhase = PH_TRADER;
    int totalSell = 0;
    for(int i = 0; i < player->totalPerSell; ++i) {
        card_t *choosen = player->chooseCard(player, &player->ground);
        if (choosen == NULL) {
            break;
        }
        int drawTotal = sell(choosen) + (has_MarketHall(player->ground) ?  1 : 0);
        while (drawTotal--) {
            player->hand = add_card(player->hand, draw());
            ++player->totalHand;
        }
        play_DrawCard_sound();
        disard_card(*choosen->tokens);
        choosen->tokens = NULL;
        if(player->playerNum != 1) draw_bot_choose_msg_and_wait_for_confirm(player->playerNum, choosen->cardName);
        ++totalSell;
    }
    if(has_marketStand(player->ground) && totalSell >= 2) {
        player->hand = add_card(player->hand, draw());
        ++player->totalHand;
    }
    player->totalPerSell = 1;
}

void prospector_action(player_t *player){
    check_effect(player);
}
void producer_action(player_t *player){
    check_effect(player);
    presentPhase = PH_PRODUCER;
    int totalProduce = 0;
    for(int i = 0; i < player->totalPerProduce; ++i) {
        card_t *choosen = player->chooseCard(player, &player->ground);
        if (choosen == NULL) break;
        choosen->tokens = add_card(choosen->tokens, draw());
        if(player->playerNum != 1) draw_bot_choose_msg_and_wait_for_confirm(player->playerNum, choosen->cardName);
        ++totalProduce;
    }
    if(has_Well(player->ground) && totalProduce >=2) {
        player->hand = add_card(player->hand, draw());
        ++player->totalHand;
    }
    player->totalPerProduce = 1;
}

void councillor_action(player_t *player){
    check_effect(player);
    presentPhase = PH_COUNCILLOR;
    if(has_Archive(player->ground)){
        for(int i = 0; i < 3; ++i) player->hand = add_card(player->hand, draw()), ++player->totalHand;
        play_DrawCard_sound();
        card_t *tmp = NULL;
        presentPhase = PH_DISCARD;
        int totalDiscard = 0;
        for(int i = 0; i < 2 - (has_preFecture(player->ground) ? 1 : 0); ++i){
            ++totalDiscard;
            --player->totalHand;
            card_t *choosen = player->chooseCard(player, &player->hand);
            tmp = add_card(tmp, *choosen);
            free(choosen);
        }
        discard_all_card(tmp);
        if (player->playerNum != 1) draw_bot_choose_msg_and_wait_for_confirm(player->playerNum, &totalDiscard);
        presentPhase = PH_COUNCILLOR;
    }else {
        card_t *tmp = NULL;
        for (int i = 0; i < 2; ++i) tmp = add_card(tmp, draw());
        card_t *choosen = player->chooseCard(player, &tmp);
        player->hand = add_card(player->hand, *choosen);
        ++player->totalHand;
        play_DrawCard_sound();
        if (player->playerNum != 1) draw_bot_choose_msg_and_wait_for_confirm(player->playerNum, NULL);
        if (has_preFecture(player->ground)) {
            card_t *choosen = player->chooseCard(player, &tmp);
            player->hand = add_card(player->hand, *choosen);
            ++player->totalHand;
            play_DrawCard_sound();
            if (player->playerNum != 1) draw_bot_choose_msg_and_wait_for_confirm(player->playerNum, NULL);
        }
        free(choosen);
        discard_all_card(tmp);
    }
}

void builder_action(player_t *player){
    check_effect(player);
    presentPhase = PH_BUILDER;
    if(has_BlackMarket(player->ground)){
        card_t *chooseList = NULL;
        for(card_t *trav = player->ground; trav != NULL; trav = trav->next) if(trav->buildingType == FACTORY && trav->tokens != NULL) chooseList = add_card(chooseList, *trav);
        presentPhase = PH_CHOOSECARD;
        for(int i = 0; i < 2; ++i) {
            if(chooseList  == NULL) break;
            card_t *choosen = player->chooseCard(player, &chooseList);
            if(choosen == NULL) break;
            card_t *trav;
            for(trav = player->ground; !same_card(trav, choosen); trav = trav->next);
            discard_all_card(trav->tokens);
            trav->tokens = NULL;
            free(choosen);
            --player->cost_off;
        }
        presentPhase = PH_BUILDER;

    }

    card_t *choosen = player->chooseCard(player, &player->hand);
    if (choosen == NULL) return;

    --player->totalHand;
    player->ground = add_card(player->ground, *choosen);
    if (player->playerNum != 1) draw_bot_choose_msg_and_wait_for_confirm(player->playerNum, choosen->cardName);
    free(choosen);
    choosen = NULL;
    presentPhase = PH_DISCARD;
    int totalDiscard = 0;
    for (int i = 0; (i < (cost + player->cost_off)) && (i < player->maxCost); ++i) {
        card_t *tmp = player->chooseCard(player, &player->hand);
        choosen = add_card(choosen, *tmp);
        --player->totalHand;
        ++totalDiscard;
        free(tmp);
    }
    if(player->playerNum != 1) draw_bot_choose_msg_and_wait_for_confirm(player->playerNum, &totalDiscard);
    discard_all_card(choosen);
    presentPhase = PH_BUILDER;
    ++player->totalBuilding;
    if(player->totalBuilding == 12) return;
    player->cost_off = 0;
    player->maxCost = 100;
    if(player->totalHand <= 1 && has_poorHouse(player->ground)) {
        player->hand = add_card(player->hand, draw());
        ++player->totalHand;
    }
}

void trader_previ(player_t *player){
    get_Price();
    if(has_library(player->ground)) player->privillageTimes = 2;
    for(int i = 0; i < player->privillageTimes; ++i) {
        ++player->totalPerSell;
    }
    player->privillageTimes = 1;
    trader_action(player);
}
void prospector_previ(player_t *player){
    check_effect(player);
    presentPhase = PH_PROSPECTOR;
    if(has_library(player->ground)) player->privillageTimes = 2;
    for(int i = 0; i < player->privillageTimes; ++i) {
        player->hand = add_card(player->hand, draw());
        if (player->playerNum != 1) draw_bot_choose_msg_and_wait_for_confirm(player->playerNum, NULL);
        ++player->totalHand;
    }
    play_DrawCard_sound();
    player->privillageTimes = 1;
}
void producer_previ(player_t *player){
    if(has_library(player->ground)) player->privillageTimes = 2;
    for(int i = 0; i < player->privillageTimes; ++i) {
        ++player->totalPerProduce;
    }
    player->privillageTimes = 1;
    producer_action(player);
}
void councillor_previ(player_t *player){
    check_effect(player);
    presentPhase = PH_COUNCILLOR;
    if(has_library(player->ground)) player->privillageTimes = 2;
    for(int i = 0; i < player->privillageTimes; ++i) {
        if(has_Archive(player->ground)){
            for(int i = 0; i < 5; ++i) player->hand = add_card(player->hand, draw()), ++player->totalHand;
            card_t *tmp = NULL;
            presentPhase = PH_DISCARD;
            int totalDiscard = 0;
            for(int i = 0; i < 4 - (has_preFecture(player->ground) ? 1 : 0); ++i){
                ++totalDiscard;
                --player->totalHand;
                card_t *choosen = player->chooseCard(player, &player->hand);
                tmp = add_card(tmp, *choosen);
                free(choosen);
            }
            discard_all_card(tmp);
            if (player->playerNum != 1) draw_bot_choose_msg_and_wait_for_confirm(player->playerNum, &totalDiscard);
            presentPhase = PH_COUNCILLOR;
        }else {
            card_t *tmp = NULL;
            for (int i = 0; i < 5; ++i) tmp = add_card(tmp, draw());
            card_t *choosen = player->chooseCard(player, &tmp);
            player->hand = add_card(player->hand, *choosen);
            if (player->playerNum != 1) draw_bot_choose_msg_and_wait_for_confirm(player->playerNum, NULL);
            ++player->totalHand;
            if (has_preFecture(player->ground)) {
                card_t *choosen = player->chooseCard(player, &tmp);
                player->hand = add_card(player->hand, *choosen);
                ++player->totalHand;
                if (player->playerNum != 1) draw_bot_choose_msg_and_wait_for_confirm(player->playerNum, NULL);
            }
            free(choosen);
            discard_all_card(tmp);
        }
    }
    player->privillageTimes = 1;
}
void builder_previ(player_t *player){
    if(has_library(player->ground)) player->privillageTimes = 2;
    for(int i = 0; i < player->privillageTimes; ++i) {
        player->cost_off -= 1;
    }
    player->privillageTimes = 1;
    builder_action(player);
}

void execute_prev(player_t *player) {
    switch(presentCareer){
        case CR_BUILDER:
            builder_previ(player);
            break;
        case CR_COUNCILLOR:
            councillor_previ(player);
            break;
        case CR_PRODUCER:
            producer_previ(player);
            break;
        case CR_PROSEPCTOR:
            prospector_previ(player);
            break;
        case CR_TRADER:
            trader_previ(player);
            break;
    }
}
void execute_norm(player_t *player) {
    switch(presentCareer){
        case CR_BUILDER:
            builder_action(player);
            break;
        case CR_COUNCILLOR:
            councillor_action(player);
            break;
        case CR_PRODUCER:
            producer_action(player);
            break;
        case CR_PROSEPCTOR:
            prospector_action(player);
            break;
        case CR_TRADER:
            trader_action(player);
            break;
    }
}


int load_career_texture(){
    builder.texture = IMG_LoadTexture(main_window_renderer, "./Asset/builder.gif");
    if(builder.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    builder.cardName = CAREER_BUILDER;

    councillor.texture = IMG_LoadTexture(main_window_renderer, "./Asset/councillor.gif");
    if(councillor.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    councillor.cardName = CAREER_COUNCILOR;
    producer.texture = IMG_LoadTexture(main_window_renderer, "./Asset/producer.gif");
    if(producer.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    producer.cardName = CAREER_PRUDUCER;
    prospector.texture = IMG_LoadTexture(main_window_renderer, "./Asset/prospector.gif");
    if(prospector.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    prospector.cardName = CAREER_PROSPECTOR;
    trader.texture = IMG_LoadTexture(main_window_renderer, "./Asset/trader.gif");
    if(trader.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    trader.cardName = CAREER_TRADER;
}

card_t *init_career_list(){
    card_t *first = calloc(1, sizeof(card_t));
    *first = builder;
    first->next = calloc(1, sizeof(card_t));
    *(first->next) = councillor;
    first->next->next = calloc(1, sizeof(card_t));
    *(first->next->next) = producer;
    first->next->next->next = calloc(1, sizeof(card_t));
    *(first->next->next->next) = prospector;
    first->next->next->next->next = calloc(1, sizeof(card_t));
    *(first->next->next->next->next) = trader;
    first->next->next->next->next->next = NULL;
    return first;
}

void destroy_career_list(card_t *cards){
    if(cards != NULL){
        destroy_career_list(cards->next);
        free(cards);
    }
}

void free_career_texture(){
    SDL_DestroyTexture(builder.texture);
    SDL_DestroyTexture(councillor.texture);
    SDL_DestroyTexture(prospector.texture);
    SDL_DestroyTexture(producer.texture);
    SDL_DestroyTexture(trader.texture);
}

career_t get_career(card_t *career) {
    if (career->texture == builder.texture) return CR_BUILDER;
    else if (career->texture == councillor.texture) return CR_COUNCILLOR;
    else if (career->texture == producer.texture) return CR_PRODUCER;
    else if (career->texture == prospector.texture) return CR_PROSEPCTOR;
    else if (career->texture == trader.texture) return CR_TRADER;
}