//
// Created by blast on 2021/5/24.
//

#ifndef COMPUTER_PROGRAMMING_FINAL_PROJECT_SANJUANDATA_H
#define COMPUTER_PROGRAMMING_FINAL_PROJECT_SANJUANDATA_H
#include "Sanjuandef.h"
#include <SDL2/SDL.h>

typedef struct _player_t player_t;

typedef enum _phase_t{
    PH_ALL = 1,
    PH_PROSPECTOR = 2,
    PH_ROUND = 4,
    PH_GAMEEND = 8,
    PH_TRADER = 16,
    PH_COUNCILLOR = 32,
    PH_BUILDER = 64,
    PH_PRODUCER = 128,
    PH_NOEFFECT = 256,
    PH_DISCARD = 512,
    PH_CHOOSECAREER = 1024,
    PH_CHOOSECARD = 2048,
} phase_t;


typedef struct _card_t{
    SDL_Texture *texture;
    phase_t phase;
    struct _card_t *tokens;
    int victoryPoint;
    int cost;
    building_t buildingType;
    void (*effect)(player_t *player);
    struct _card_t *next;
    char *cardName;
    SDL_Rect pos;
} card_t;

struct _player_t {
    card_t *hand;
    card_t *ground;
    int victoryPoint;
    int8_t totalBuilding;
    int8_t privillageTimes;
    int8_t totalPerSell;
    int8_t totalPerProduce;
    int8_t cost_off;
    int8_t maxCost;
    int8_t totalHand;
    int8_t maxHand;
    int8_t playerNum;
    career_t (*chooseCareer)(player_t *player);
    card_t* (*chooseCard)(player_t *player, card_t **cards);
};

typedef struct _prices{
    int8_t indigo;
    int8_t sugar;
    int8_t tobacco;
    int8_t coffee;
    int8_t silver;
} prices_t;


extern SDL_Texture *backgroundImg;



#endif //COMPUTER_PROGRAMMING_FINAL_PROJECT_SANJUANDATA_H
