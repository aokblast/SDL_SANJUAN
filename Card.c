//
// Created by blast on 2021/5/26.
//
#include "Sanjuandata.h"
#include "Deck.h"
#include "GameMain.h"
#include "Window.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "Draw.h"
#include "Card.h"
#include "Sound.h"

extern int deckTop;

extern char CARD_AQUEDUCT[20];
extern char CARD_ARCHIVE[20];
extern char CARD_BLACKMARKET[20];
extern char CARD_CARPENTER[20];
extern char CARD_CHAPEL[20];
extern char CARD_COFFEESOASTER[20];
extern char CARD_CRANE[20];
extern char CARD_CITYHALL[20];
extern char CARD_GUILDHALL[20];
extern char CARD_GOLDMINE[20];
extern char CARD_HERO[20];
extern char CARD_INDIGOPLANT[20];
extern char CARD_LIBRARY[20];
extern char CARD_MARKETSTAND[20];
extern char CARD_MARKETHALL[20];
extern char CARD_PREFECTURE[20];
extern char CARD_POORHOUSE[20];
extern char CARD_PALACE[20];
extern char CARD_QUARRY[20];
extern char CARD_SILVER_SMELTER[20];
extern char CARD_SUGARMILL[20];
extern char CARD_STATUS[20];
extern char CARD_SMITHY[20];
extern char CARD_TOBACCOSTORAGE[20];
extern char CARD_TRADINGPOST[20];
extern char CARD_TRIUMPHALARCH[20];
extern char CARD_TOWER[20];
extern char CARD_VICTORYCOLUMN[20];
extern char CARD_WELL[20];

static prices_t priceTable[5] = {{1, 1, 2, 2, 3},
                                 {1, 2, 2, 2, 3},
                                 {1, 2, 2, 3, 3},
                                 {1, 1, 1, 2, 2},
                                 {1, 1, 2, 2, 2}};

prices_t presentPrice;


void silverSmelter_effect(player_t *player){
}

void library_effect(player_t *player){
}
void palace_effect(player_t *player){
}
void marketStand_effect(player_t *player){
}
void blackMarket_effect(player_t *player){
}
void tobaccoStorage_effect(player_t *player){
}
void marketHall_effect(player_t *player){
}
void carpenter_effect(player_t *player){
    for(card_t *trav = player->ground; trav != NULL; trav = trav->next){
        if(trav->buildingType == SPECIAL) {
            player->hand = add_card(player->hand, draw());
            ++player->totalHand;
            break;
        }
    }
}
void coffeeRoaster_effect(player_t *player){
}
void well_effect(player_t *player){
}
void sugarMill_effect(player_t *player){
}
void smithy_effect(player_t *player){
}
void archive_effect(player_t *player){
}

void tradingPost_effect(player_t *player){
    ++player->totalPerSell;
}
void guildHall_effect(player_t *player){
    card_t *guildHall;
    for(guildHall = player->ground; guildHall != NULL; guildHall = guildHall->next)
    for(card_t *trav = player->ground; trav != NULL; trav = trav->next){
        if(trav->buildingType == FACTORY) guildHall->victoryPoint += 2;
    }
}

void quarry_effect(player_t *player){
}

void crane_effect(player_t *player){
}

void triumphalArch_effect(player_t *player){
    int totalMomen = 0;
    for(card_t *trav = player->ground; trav != NULL; trav = trav->next) totalMomen += (trav->effect == NULL ? 1 : 0);
    card_t *triumphArch;
    for(triumphArch = player->ground; triumphArch->cardName != CARD_TRIUMPHALARCH; triumphArch = triumphArch->next);
    triumphArch->victoryPoint += (totalMomen == 3 ? 8 : totalMomen == 2 ? 6 : totalMomen == 1 ? 4 : 0);
}
void chapel_effect(player_t *player){
    //CANT DISCARD
    //printf("%d\n", presentPhase);
    if(presentPhase & PH_ROUND) {
        card_t *card = player->chooseCard(player, &player->hand);
        if (card != NULL) {
            play_DrawCard_sound();
            --player->totalHand;
            card_t *trav;
            for (trav = player->ground; trav->cardName != CARD_CHAPEL; trav = trav->next);
            trav->tokens = add_card(trav->tokens, *card);
            ++player->victoryPoint;
            free(card);
        }
        presentPhase = PH_ROUND;
    }

}
void status_effect(player_t *player){
}
void goldMine_effect(player_t *player){
    card_t *choosen = NULL;
    bool hasCost[10] = {false};
    bool needDraw = true;
    for(int i = 0; i < 4; ++i) {
        card_t drawCard = draw();
        choosen = add_card(choosen, drawCard);
        if(hasCost[drawCard.cost]) needDraw = false;
        else{
            hasCost[drawCard.cost] = true;
        }
    }
    if(needDraw){
        presentPhase = PH_CHOOSECARD;
        card_t *draw = player->chooseCard(player, &choosen);
        play_DrawCard_sound();
        player->hand = add_card(player->hand, *draw);
        discard_all_card(choosen);
        ++player->totalHand;
        return;
    }
    discard_all_card(choosen);
    presentPhase = PH_PROSPECTOR;
}
void tower_effect(player_t *player){
    player->maxHand = 12;
}
void aqueduct_effect(player_t *player){
    ++player->totalPerProduce;
}

void prefecture_effect(player_t *player){
}
void poorHouse_effect(player_t *player){
}

void indigoPlant_effect(player_t *player) {
}

void cityHall_effect(player_t *player) {
    card_t *cityHall;
    for(cityHall = player->ground; cityHall->cardName != CARD_CITYHALL; cityHall = cityHall->next);
    for(card_t *trav = player->ground; trav != NULL; trav = trav->next){
        if(trav->buildingType == SPECIAL) {
            ++cityHall->victoryPoint;
        }
    }
}

card_t aqueduct = {NULL, PH_PRODUCER, NULL, 2, 3, SPECIAL, aqueduct_effect, NULL, CARD_AQUEDUCT};
card_t archive = {NULL, PH_COUNCILLOR, NULL, 1, 1, SPECIAL, archive_effect, NULL, CARD_ARCHIVE};
card_t blackMarket = {NULL, PH_BUILDER, NULL, 1, 2, SPECIAL, blackMarket_effect, NULL, CARD_BLACKMARKET};
card_t carpenter = {NULL, PH_BUILDER, NULL, 2, 3, SPECIAL, carpenter_effect, NULL, CARD_CARPENTER};
card_t chapel = {NULL, PH_ROUND, NULL, 2, 3, SPECIAL, chapel_effect, NULL, CARD_CHAPEL};
card_t coffeeRoaster = {NULL, PH_PRODUCER, NULL, 2, 4, FACTORY, coffeeRoaster_effect, NULL, CARD_COFFEESOASTER};
card_t crane = {NULL, PH_BUILDER, NULL, 1, 2, SPECIAL, crane_effect, NULL, CARD_CRANE};
card_t cityHall = {NULL, PH_GAMEEND, NULL,0, 6, SPECIAL, cityHall_effect, NULL, CARD_CITYHALL};
card_t guildHall = {NULL, PH_GAMEEND, NULL, 0, 6, SPECIAL, guildHall_effect, NULL, CARD_GUILDHALL};
card_t goldMine = {NULL, PH_PROSPECTOR, NULL, 1, 1, SPECIAL, goldMine_effect, NULL, CARD_GOLDMINE};
card_t hero = {NULL, PH_NOEFFECT, NULL, 5, 5, SPECIAL, NULL, NULL, CARD_HERO};
card_t indigoPlant = {NULL, PH_PRODUCER, NULL, 1, 1, FACTORY, indigoPlant_effect, NULL, CARD_INDIGOPLANT};
card_t library = {NULL, PH_ALL, NULL,3, 5, SPECIAL, library_effect, NULL, CARD_LIBRARY};
card_t marketStand = {NULL, PH_TRADER, NULL,1, 2, SPECIAL, marketStand_effect, NULL, CARD_MARKETSTAND};
card_t marketHall = {NULL, PH_TRADER, NULL, 2, 4, SPECIAL, marketHall_effect, NULL, CARD_MARKETHALL};
card_t prefecture = {NULL, PH_COUNCILLOR, NULL, 2, 3, SPECIAL, prefecture_effect, NULL, CARD_PREFECTURE};
card_t poorHouse = {NULL, PH_BUILDER, NULL,1, 2, SPECIAL, poorHouse_effect, NULL, CARD_POORHOUSE};
card_t palace = {NULL, PH_GAMEEND, NULL,0, 6, SPECIAL, palace_effect, NULL, CARD_PALACE};
card_t quarry = {NULL, PH_BUILDER, NULL, 2, 4, SPECIAL, quarry_effect, NULL, CARD_QUARRY};
card_t silverSmelter = {NULL, PH_PRODUCER,  NULL, 3,5, FACTORY, silverSmelter_effect, NULL, CARD_SILVER_SMELTER};
card_t sugarMill = {NULL, PH_PRODUCER, NULL,1, 2, FACTORY, sugarMill_effect, NULL, CARD_SUGARMILL};
card_t status = {NULL, PH_NOEFFECT, NULL, 3, 3, SPECIAL, status_effect, NULL, CARD_STATUS};
card_t smithy = {NULL, PH_BUILDER, NULL, 1, 1, SPECIAL, smithy_effect, NULL, CARD_SMITHY};
card_t tobaccoStorage = {NULL, PH_PRODUCER, NULL, 2, 3, FACTORY, tobaccoStorage_effect, NULL, CARD_TOBACCOSTORAGE};
card_t tradingPost = {NULL, PH_TRADER, NULL, 1, 2, SPECIAL, tradingPost_effect, NULL, CARD_TRADINGPOST};
card_t triumphalArch = {NULL, PH_GAMEEND, NULL, 0, 6, SPECIAL, triumphalArch_effect, NULL, CARD_TRIUMPHALARCH};
card_t tower = {NULL, PH_ROUND, NULL, 2, 3, SPECIAL, tower_effect, NULL, CARD_TOWER};
card_t victoryColumn = {NULL, PH_NOEFFECT, NULL, 4, 4, SPECIAL, NULL, NULL, CARD_VICTORYCOLUMN};
card_t well = {NULL, PH_PRODUCER, NULL, 1, 2, SPECIAL, well_effect, NULL, CARD_WELL};


int load_card_texture(){
    aqueduct.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_aqueduct.gif");
    if(aqueduct.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    archive.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_archive.gif");
    if(archive.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    blackMarket.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_black_market.gif");
    if(blackMarket.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    carpenter.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_carpenter.gif");
    if(carpenter.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    chapel.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_chapel.gif");
    if(chapel.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    cityHall.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_city_hall.gif");
    if(cityHall.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    coffeeRoaster.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_coffee_roaster.gif");
    if(coffeeRoaster.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    crane.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_crane.gif");
    if(crane.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    goldMine.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_gold_mine.gif");
    if(goldMine.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    guildHall.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_guild_hall.gif");
    if(guildHall.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    hero.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_hero.gif");
    if(hero.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    indigoPlant.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_indigo_plant.gif");
    if(indigoPlant.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    library.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_library.gif");
    if(library.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    marketHall.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_market_hall.gif");
    if(marketHall.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    marketStand.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_market_stand.gif");
    if(marketStand.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    palace.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_palace.gif");
    if(palace.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    poorHouse.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_poor_house.gif");
    if(poorHouse.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    prefecture.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_prefecture.gif");
    if(prefecture.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    quarry.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_quarry.gif");
    if(quarry.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    silverSmelter.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_silver_smelter.gif");
    if(silverSmelter.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    smithy.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_smithy.gif");
    if(smithy.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    status.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_statue.gif");
    if(status.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    sugarMill.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_sugar_mill.gif");
    if(sugarMill.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    tobaccoStorage.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_tobacco_storage.gif");
    if(tobaccoStorage.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    tower.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_tower.gif");
    if(tower.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    tradingPost.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_trading_post.gif");
    if(tradingPost.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    triumphalArch.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_triumphal_arch.gif");
    if(triumphalArch.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    victoryColumn.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_victory_column.gif");
    if(victoryColumn.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    well.texture = IMG_LoadTexture(main_window_renderer, "./Asset/large_well.gif");
    if(well.texture == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    return 1;
}

void destroy_card_texture(){
    SDL_DestroyTexture(aqueduct.texture);
    SDL_DestroyTexture(archive.texture);
    SDL_DestroyTexture(blackMarket.texture);
    SDL_DestroyTexture(carpenter.texture);
    SDL_DestroyTexture(chapel.texture);
    SDL_DestroyTexture(cityHall.texture);
    SDL_DestroyTexture(coffeeRoaster.texture);
    SDL_DestroyTexture(crane.texture);
    SDL_DestroyTexture(goldMine.texture);
    SDL_DestroyTexture(guildHall.texture);
    SDL_DestroyTexture(hero.texture);
    SDL_DestroyTexture(indigoPlant.texture);
    SDL_DestroyTexture(library.texture);
    SDL_DestroyTexture(marketStand.texture);
    SDL_DestroyTexture(marketHall.texture);
    SDL_DestroyTexture(palace.texture);
    SDL_DestroyTexture(poorHouse.texture);
    SDL_DestroyTexture(prefecture.texture);
    SDL_DestroyTexture(quarry.texture);
    SDL_DestroyTexture(silverSmelter.texture);
    SDL_DestroyTexture(smithy.texture);
    SDL_DestroyTexture(status.texture);
    SDL_DestroyTexture(sugarMill.texture);
    SDL_DestroyTexture(tobaccoStorage.texture);
    SDL_DestroyTexture(tower.texture);
    SDL_DestroyTexture(tradingPost.texture);
    SDL_DestroyTexture(triumphalArch.texture);
    SDL_DestroyTexture(victoryColumn.texture);
    SDL_DestroyTexture(well.texture);
}

void init_deck(){
    deck[deckTop++] = palace;
    deck[deckTop++] = palace;
    deck[deckTop++] = marketStand;
    deck[deckTop++] = marketStand;
    deck[deckTop++] = marketStand;
    deck[deckTop++] = cityHall;
    deck[deckTop++] = cityHall;
    deck[deckTop++] = poorHouse;
    deck[deckTop++] = poorHouse;
    deck[deckTop++] = poorHouse;
    deck[deckTop++] = blackMarket;
    deck[deckTop++] = blackMarket;
    deck[deckTop++] = blackMarket;
    deck[deckTop++] = tobaccoStorage;
    deck[deckTop++] = tobaccoStorage;
    deck[deckTop++] = tobaccoStorage;
    deck[deckTop++] = tobaccoStorage;
    deck[deckTop++] = tobaccoStorage;
    deck[deckTop++] = tobaccoStorage;
    deck[deckTop++] = tobaccoStorage;
    deck[deckTop++] = tobaccoStorage;
    deck[deckTop++] = silverSmelter;
    deck[deckTop++] = silverSmelter;
    deck[deckTop++] = silverSmelter;
    deck[deckTop++] = silverSmelter;
    deck[deckTop++] = silverSmelter;
    deck[deckTop++] = silverSmelter;
    deck[deckTop++] = silverSmelter;
    deck[deckTop++] = silverSmelter;
    deck[deckTop++] = marketHall;
    deck[deckTop++] = marketHall;
    deck[deckTop++] = marketHall;
    deck[deckTop++] = carpenter;
    deck[deckTop++] = carpenter;
    deck[deckTop++] = carpenter;
    deck[deckTop++] = coffeeRoaster;
    deck[deckTop++] = coffeeRoaster;
    deck[deckTop++] = coffeeRoaster;
    deck[deckTop++] = coffeeRoaster;
    deck[deckTop++] = coffeeRoaster;
    deck[deckTop++] = coffeeRoaster;
    deck[deckTop++] = coffeeRoaster;
    deck[deckTop++] = coffeeRoaster;
    deck[deckTop++] = well;
    deck[deckTop++] = well;
    deck[deckTop++] = well;
    deck[deckTop++] = sugarMill;
    deck[deckTop++] = sugarMill;
    deck[deckTop++] = sugarMill;
    deck[deckTop++] = sugarMill;
    deck[deckTop++] = sugarMill;
    deck[deckTop++] = sugarMill;
    deck[deckTop++] = sugarMill;
    deck[deckTop++] = sugarMill;
    deck[deckTop++] = smithy;
    deck[deckTop++] = smithy;
    deck[deckTop++] = smithy;
    deck[deckTop++] = victoryColumn;
    deck[deckTop++] = victoryColumn;
    deck[deckTop++] = victoryColumn;
    deck[deckTop++] = archive;
    deck[deckTop++] = archive;
    deck[deckTop++] = archive;
    deck[deckTop++] = tradingPost;
    deck[deckTop++] = tradingPost;
    deck[deckTop++] = tradingPost;
    deck[deckTop++] = quarry;
    deck[deckTop++] = quarry;
    deck[deckTop++] = quarry;
    deck[deckTop++] = crane;
    deck[deckTop++] = crane;
    deck[deckTop++] = crane;
    deck[deckTop++] = triumphalArch;
    deck[deckTop++] = triumphalArch;
    deck[deckTop++] = guildHall;
    deck[deckTop++] = guildHall;
    deck[deckTop++] = hero;
    deck[deckTop++] = hero;
    deck[deckTop++] = hero;
    deck[deckTop++] = chapel;
    deck[deckTop++] = chapel;
    deck[deckTop++] = chapel;
    deck[deckTop++] = status;
    deck[deckTop++] = status;
    deck[deckTop++] = status;
    deck[deckTop++] = goldMine;
    deck[deckTop++] = goldMine;
    deck[deckTop++] = goldMine;
    deck[deckTop++] = tower;
    deck[deckTop++] = tower;
    deck[deckTop++] = tower;
    deck[deckTop++] = aqueduct;
    deck[deckTop++] = aqueduct;
    deck[deckTop++] = aqueduct;
    deck[deckTop++] = library;
    deck[deckTop++] = library;
    deck[deckTop++] = library;
    deck[deckTop++] = prefecture;
    deck[deckTop++] = prefecture;
    deck[deckTop++] = prefecture;
    for(int8_t i  = totalPlayer; i <= 10; ++i){
        deck[deckTop++] = indigoPlant;
    }
}



card_t *add_card(card_t *cards, card_t addCard) {
    card_t *trav = cards;
    card_t *newCard = calloc(1, sizeof(card_t));
    *newCard = addCard;
    newCard->next = NULL;
    if(trav == NULL) {
        return newCard;
    }
    while(trav->next != NULL) trav = trav->next;

    trav->next = newCard;
    return cards;
}


void free_card_list(card_t *cards){
    if(cards != NULL) {
        free_card_list(cards->next);
        free(cards);
    }
}

void check_effect(player_t *player){
    card_t *cards = player->ground;
    while(cards != NULL) {
        if(cards->effect != NULL && ((cards->phase & presentPhase) || (cards->phase & PH_ALL))) {
            cards->effect(player);
        }
        cards = cards->next;
    }
}

void discard_all_card(card_t *cards){
    if(cards != NULL) {
        discard_all_card(cards->next);
        disard_card(*cards);
        free(cards);
    }
}

void get_Price(){
    presentPrice = priceTable[4];
    prices_t tmp = priceTable[0];
    priceTable[0] = priceTable[4];
    for(int i = 1; i < 5; ++i) {
        prices_t tmp2 = priceTable[i];
        priceTable[i] = tmp;
        tmp = tmp2;
    }
}

int sell(card_t *card){
    if(card->texture == silverSmelter.texture){
        return presentPrice.silver;
    }else if(card->texture == coffeeRoaster.texture){
        return presentPrice.coffee;
    }else if(card->texture == indigoPlant.texture){
        return presentPrice.indigo;
    }else if(card->texture == sugarMill.texture){
        return presentPrice.sugar;
    }else if(card->texture == tobaccoStorage.texture){
        return presentPrice.tobacco;
    }
}

card_t *delete_card_from_list(card_t *cardList, card_t *card){
    card_t *trav = cardList;
    if(trav == card) {
        return card->next;
    }
    while(trav->next != NULL && trav->next != card)trav = trav->next;
    if(trav->next == NULL){
        return cardList;
    }
    trav->next = card->next;
    card->next = NULL;
    return cardList;
}

card_t *choose_card(card_t *cards){
    SDL_Event event;
    SDL_Point point;
    card_t *choose = NULL;
    while(choose == NULL){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                quit_Game();
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&point.x, &point.y);
                choose = get_choose(cards, &point);
                if((presentPhase == PH_BUILDER || presentPhase == PH_PRODUCER || presentPhase == PH_TRADER || presentPhase == PH_ROUND) && in_ConfirmButton(point)){
                    return NULL;
                }
                if(choose != NULL) {
                    cards = delete_card_from_list(cards, choose);
                }
                break;
        }

    }
    return choose;
}

bool same_card(card_t *card1, card_t *card2) {
    return (card1->texture == card2->texture) && (card1->phase == card2->phase) && (card1->cost == card2->cost)  && (card1->buildingType == card2->buildingType) && (card1->effect == card2->effect );
}

bool has_crane(card_t *ground){
    for(card_t *trav = ground; trav != NULL; trav = trav->next) if(trav->cardName == CARD_CRANE) return true;
    return false;
}

bool has_library(card_t *ground){
    for(card_t *trav = ground; trav != NULL; trav = trav->next) if(trav->cardName == CARD_LIBRARY) return true;
    return false;
}

bool has_MarketHall(card_t *ground){
    for(card_t *trav = ground; trav != NULL; trav = trav->next) if(trav->cardName == CARD_MARKETHALL) return true;
    return false;
}

bool has_marketStand(card_t *ground){
    for(card_t *trav = ground; trav != NULL; trav = trav->next) if(trav->cardName == CARD_MARKETSTAND) return true;
    return false;
}

bool has_palace(card_t *ground){
    for(card_t *trav = ground; trav != NULL; trav = trav->next) if(trav->cardName == CARD_PALACE) return true;
    return false;
}

bool has_poorHouse(card_t *ground){
    for(card_t *trav = ground; trav != NULL; trav = trav->next) if(trav->cardName == CARD_POORHOUSE) return true;
    return false;
}

bool has_preFecture(card_t *ground){
    for(card_t *trav = ground; trav != NULL; trav = trav->next) if(trav->cardName == CARD_PREFECTURE) return true;
    return false;
}

bool has_Quarry(card_t *ground){
    for(card_t *trav = ground; trav != NULL; trav = trav->next) if(trav->cardName == CARD_QUARRY) return true;
    return false;
}

bool has_Smithy(card_t *ground){
    for(card_t *trav = ground; trav != NULL; trav = trav->next) if(trav->cardName == CARD_SMITHY) return true;
    return false;
}

bool has_Well(card_t *ground){
    for(card_t *trav = ground; trav != NULL; trav = trav->next) if(trav->cardName == CARD_WELL) return true;
    return false;
}

bool has_Archive(card_t *ground){
    for(card_t *trav = ground; trav != NULL; trav = trav->next) if(trav->cardName == CARD_ARCHIVE) return true;
    return false;
}

bool has_BlackMarket(card_t *ground){
    for(card_t *trav = ground; trav != NULL; trav = trav->next) if(trav->cardName == CARD_BLACKMARKET) return true;
    return false;
}