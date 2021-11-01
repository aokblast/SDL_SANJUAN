//
// Created by blast on 2021/6/2.
//
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "Sanjuandata.h"
#include "GameMain.h"
#include "Window.h"
#include "Button.h"

SDL_Texture *cardBack;
SDL_Texture *trading_1;
SDL_Texture *trading_2;
SDL_Texture *trading_3;
SDL_Texture *trading_4;
SDL_Texture *trading_5;

void draw_trading_status();
void draw_presentCareer();
void draw_confirm_button();
bool in_ConfirmButton(SDL_Point point);
extern prices_t presentPrice;

extern char PH_TRADER_TEXT[40];
extern char PH_BUILDER_TEXT[40];
extern char PH_PROSPECTOR_TEXT[40];
extern char PH_COUNCILLOR_TEXT[40];
extern char PH_ROUND_TEXT[40];
extern char PH_DISCARD_TEXT[40];
extern char PH_PRODUCER_TEXT[40];
extern char PH_CHOOSE_CAREER_TEXT[40];
extern char PH_GAME_END_TEXT[40];
extern char PH_CHOOSECARD_TEXT[40];
extern char BUTTON_CONFIRM_TEXT[10];
extern char BUTTON_YES_TEXT[10];
extern char BUTTON_NO_TEXT[10];
extern char MSG_BUILDER_TEXT[40];
extern char MSG_TRADER_TEXT[40];
extern char MSG_PRODUCER_TEXT[40];
extern char MSG_COUNCILLOR_TEXT[40];
extern char MSG_CHOOSECAREER_TEXT[40];
extern char MSG_DISCARD_TEXT[40];
extern char MSG_PROSPECTOR_TEXT[40];
extern char MSG_GAMEEND_TEXT[40];
extern char MSG_GOVERNER_TEXT[40];
extern char MSG_CHOOSECARD_TEXT[40];


static buttonItem confirmButton = {BUTTON_CONFIRM_TEXT, {0, 0}};
static buttonItem YesNoButton[] = {
        {BUTTON_YES_TEXT, {0, 0}},
        {BUTTON_NO_TEXT, {0, 0}},
        {"", {0, 0}}
};

void draw_ground(){
    SDL_RenderClear(main_window_renderer);
    SDL_RenderCopy(main_window_renderer, backgroundImg, NULL, NULL);

    if(totalPlayer >= 1) {
        int32_t period = (ScreenWidth / 16.0 * 10.0 )/ players[0]->totalHand;
        SDL_Rect cardRect = {.h = ScreenHeight / 6.0, .w = ScreenWidth / 18.0, .x = ScreenWidth / 6.0, .y =
        ScreenHeight / 6.0 * 5};
        SDL_Rect tokenRec = cardRect;
        tokenRec.h *= 0.8;
        tokenRec.w *= 0.8;
        card_t *trav = players[0]->hand;
        //printf("Hand:\n");
        while (trav != NULL) {
            //printf("%s\n", trav->cardName);
            trav->pos = cardRect;
            SDL_RenderCopyEx(main_window_renderer, trav->texture, NULL, &trav->pos, 0, NULL, SDL_FLIP_NONE);
            trav = trav->next;
            cardRect.x += period;

        }
        cardRect.y = ScreenHeight / 8.0 * 5;
        cardRect.x = ScreenWidth / 6.0;
        trav = players[0]->ground;
        period = (ScreenWidth / 16.0 * 10.0 )/ 12.0;
        //printf("Ground:\n");
        while (trav != NULL) {
            //printf("%s\n", trav->cardName);
            trav->pos = cardRect;

            SDL_RenderCopyEx(main_window_renderer, trav->texture, NULL, &trav->pos, 0, NULL, SDL_FLIP_NONE);
            if(trav->tokens != NULL){
                tokenRec.x = cardRect.x + cardRect.w / 10.0;
                tokenRec.y = cardRect.y + cardRect.h / 10.0;
                SDL_RenderCopyEx(main_window_renderer, cardBack, NULL, &tokenRec, 0, NULL, SDL_FLIP_NONE);
            }
            trav = trav->next;
            cardRect.x += period;

        }

    }

    if(totalPlayer >= 2) {
        int32_t period = ScreenHeight / 3.0 * 2.0 / 12.0;
        SDL_Rect cardRect = {.h = ScreenHeight / 6.0 , .w = ScreenWidth / 18.0, .x = ScreenWidth / 64.0, .y =  ScreenHeight / 8.0};
        card_t *trav = players[1]->ground;
        SDL_Rect tokenRec = cardRect;
        tokenRec.h *= 0.8;
        tokenRec.w *= 0.8;
        while(trav != NULL) {
            trav->pos = cardRect;
            SDL_RenderCopyEx(main_window_renderer, trav->texture, NULL, &trav->pos, 90, NULL, SDL_FLIP_NONE);
            if(trav->tokens != NULL){
                tokenRec.x = cardRect.x + cardRect.w / 10.0;
                tokenRec.y = cardRect.y + cardRect.h / 10.0;
                SDL_RenderCopyEx(main_window_renderer, cardBack, NULL, &tokenRec, 90, NULL, SDL_FLIP_NONE);
            }
            trav = trav->next;
            cardRect.y += period;
        }


    }

    if(totalPlayer >= 3) {
        int32_t period = ScreenWidth / 16.0 * 10.0 / 12.0;
        SDL_Rect cardRect = {.h = ScreenHeight / 6.0 , .w = ScreenWidth / 18.0, .x = ScreenWidth / 6.0, .y =  0};
        card_t *trav = players[2]->ground;
        SDL_Rect tokenRec = cardRect;
        tokenRec.h *= 0.8;
        tokenRec.w *= 0.8;
        while(trav != NULL) {
            trav->pos = cardRect;
            SDL_RenderCopyEx(main_window_renderer, trav->texture, NULL, &trav->pos, 180, NULL, SDL_FLIP_NONE);
            if(trav->tokens != NULL){
                tokenRec.x = cardRect.x + cardRect.w / 10.0;
                tokenRec.y = cardRect.y + cardRect.h / 10.0;
                SDL_RenderCopyEx(main_window_renderer, cardBack, NULL, &tokenRec, 180, NULL, SDL_FLIP_NONE);
            }
            trav = trav->next;
            cardRect.x += period;
        }

    }

    if(totalPlayer >= 4) {
        int32_t period = ScreenHeight / 3.0 * 2.0 / 12.0;
        SDL_Rect cardRect = {.h = ScreenHeight / 6.0 , .w = ScreenWidth / 18.0, .x = ScreenWidth / 6.0 * 5.5, .y =  ScreenHeight / 8.0};
        card_t *trav = players[3]->ground;
        SDL_Rect tokenRec = cardRect;
        tokenRec.h *= 0.8;
        tokenRec.w *= 0.8;
        while(trav != NULL) {
            trav->pos = cardRect;
            SDL_RenderCopyEx(main_window_renderer, trav->texture, NULL, &trav->pos, 270, NULL, SDL_FLIP_NONE);
            if(trav->tokens != NULL){
                tokenRec.x = cardRect.x + cardRect.w / 10.0;
                tokenRec.y = cardRect.y + cardRect.h / 10.0;
                SDL_RenderCopyEx(main_window_renderer, cardBack, NULL, &tokenRec, 270, NULL, SDL_FLIP_NONE);
            }
            trav = trav->next;

            cardRect.y += period;
        }
    }
    draw_presentCareer();
    if(presentPhase == PH_TRADER) draw_trading_status();
}

void draw_presentCareer(){
    SDL_Color color = {0, 0, 0};
    SDL_Surface *textSurf;

    switch (presentPhase) {
        case PH_TRADER:
            textSurf = TTF_RenderUTF8_Blended(button_Font, PH_TRADER_TEXT, color);
            break;
        case PH_BUILDER:
            textSurf = TTF_RenderUTF8_Blended(button_Font, PH_BUILDER_TEXT, color);
            break;
        case PH_PROSPECTOR:
            textSurf = TTF_RenderUTF8_Blended(button_Font, PH_PROSPECTOR_TEXT, color);
            break;
        case PH_COUNCILLOR:
            textSurf = TTF_RenderUTF8_Blended(button_Font, PH_COUNCILLOR_TEXT, color);
            break;
        case PH_ROUND:
            textSurf = TTF_RenderUTF8_Blended(button_Font, PH_ROUND_TEXT, color);
            break;
        case PH_DISCARD:
            textSurf = TTF_RenderUTF8_Blended(button_Font, PH_DISCARD_TEXT, color);
            break;
        case PH_PRODUCER:
            textSurf = TTF_RenderUTF8_Blended(button_Font, PH_PRODUCER_TEXT, color);
            break;
        case PH_CHOOSECAREER:
            textSurf = TTF_RenderUTF8_Blended(button_Font, PH_CHOOSE_CAREER_TEXT, color);
            break;
        case PH_GAMEEND:
            textSurf = TTF_RenderUTF8_Blended(button_Font, PH_GAME_END_TEXT, color);
            break;
        case PH_CHOOSECARD:
            textSurf = TTF_RenderUTF8_Blended(button_Font, PH_CHOOSECARD_TEXT, color);
    }
    SDL_Texture *text = SDL_CreateTextureFromSurface(main_window_renderer, textSurf);
    SDL_Rect rect = {.x = ScreenWidth / 2.0 - textSurf->w / 2.0, .y = ScreenHeight / 9.0 * 2.0, .w = textSurf->w, .h = textSurf->h};
    SDL_RenderCopy(main_window_renderer, text, NULL, &rect);
    SDL_FreeSurface(textSurf);
    SDL_DestroyTexture(text);
}

void draw_bot_choose_msg_and_wait_for_confirm(int playerID, void *param){
    SDL_Color color = {0, 0, 0};
    SDL_Event event;
    bool breakLoop = false;
    SDL_RenderClear(main_window_renderer);
    draw_ground();
    char msg[100];
    switch(presentPhase){
        case PH_TRADER: {
            char *cardName = param;
            sprintf(msg, MSG_TRADER_TEXT, playerID, cardName);
        }
            break;
        case PH_BUILDER: {
            char *cardName = param;
            sprintf(msg , MSG_BUILDER_TEXT, playerID, cardName);
        }
            break;
        case PH_PRODUCER:{
            char *cardName = param;
            sprintf(msg, MSG_PRODUCER_TEXT, playerID, cardName);
        }
            break;
        case PH_COUNCILLOR:{
            sprintf(msg , MSG_COUNCILLOR_TEXT, playerID);
        }
            break;
        case PH_ROUND:
            sprintf(msg, MSG_GOVERNER_TEXT, playerID);
            break;
        case PH_CHOOSECAREER:{
            char *careerName = param;
            sprintf(msg, MSG_CHOOSECAREER_TEXT, playerID, careerName);
        }
            break;
        case PH_DISCARD:{
            int *cardNum = param;
            sprintf(msg, MSG_DISCARD_TEXT, playerID, *cardNum);
        }
            break;
        case PH_PROSPECTOR:{
            sprintf(msg, MSG_PROSPECTOR_TEXT, playerID);
        }
            break;
        case PH_GAMEEND:
            sprintf(msg, MSG_GAMEEND_TEXT, playerID);
            break;
        case PH_CHOOSECARD: {
            int *totalCard = param;
            sprintf(msg, MSG_CHOOSECARD_TEXT, playerID, *totalCard);
            break;
        }
    }
    SDL_Surface *textSurf = TTF_RenderUTF8_Blended(button_Font, msg, color);
    SDL_Texture *text = SDL_CreateTextureFromSurface(main_window_renderer, textSurf);
    SDL_Rect rect = {.x = ScreenWidth / 2.0 - textSurf->w / 2.0, .y = ScreenHeight / 9.0 * 4.0, .w = textSurf->w, .h = textSurf->h};
    SDL_RenderCopy(main_window_renderer, text, NULL, &rect);
    SDL_FreeSurface(textSurf);
    SDL_DestroyTexture(text);
    draw_confirm_button();
    SDL_RenderPresent(main_window_renderer);
    while(!breakLoop){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                quit_Game();
                breakLoop = true;
                break;
            case SDL_MOUSEBUTTONDOWN:{
                    SDL_Point point;
                    SDL_GetMouseState(&point.x, &point.y);
                    if(in_ConfirmButton(point)){
                        breakLoop = true;
                    }
                }
                break;


        }
    }

}

void draw_choose_card(card_t *cards){
    SDL_Rect rect = {.x = ScreenWidth / 16.0 * 3.0, .y = ScreenHeight / 9.0 * 3.0, .w = ScreenWidth / 16, .h = ScreenHeight / 9.0 * 2.0};
    size_t size = 0;
    card_t *trav = cards;
    while(trav != NULL) trav = trav->next, ++size;
    int32_t period = (ScreenWidth / 16.0 );


    SDL_SetRenderDrawColor(main_window_renderer, 255, 255, 255, 252);
    SDL_RenderFillRect(main_window_renderer, &rect);
    while(cards != NULL) {
        SDL_RenderCopy(main_window_renderer, cards->texture, NULL, &rect);
        cards->pos = rect;
        rect.x += period;
        cards = cards->next;
    }
    draw_confirm_button();

}

card_t *get_choose(card_t *cards, SDL_Point *point){
    while(cards != NULL){
        if(SDL_PointInRect(point, &cards->pos)){
            return cards;
        }
        cards = cards->next;
    }
    return NULL;
}

void draw_trading_status(){
    SDL_Rect tradingRect = {.w = ScreenWidth / 16.0 * 2.0, .h = ScreenHeight / 18.0 * 1.0, .x = ScreenWidth /  64.0 * 1.0, .y = ScreenHeight / 9.0 * 8.0};
    if(presentPrice.tobacco == 3){
        SDL_RenderCopy(main_window_renderer, trading_5, NULL, &tradingRect);
    }else if(presentPrice.sugar == 2){
        SDL_RenderCopy(main_window_renderer, trading_4, NULL, &tradingRect);
    }else if(presentPrice.silver == 3){
        SDL_RenderCopy(main_window_renderer, trading_3, NULL, &tradingRect);
    }else if(presentPrice.coffee == 2){
        SDL_RenderCopy(main_window_renderer, trading_2, NULL, &tradingRect);
    }else{
        SDL_RenderCopy(main_window_renderer, trading_1, NULL, &tradingRect);
    }

}

bool in_ConfirmButton(SDL_Point point){
    if(SDL_PointInRect(&point, &confirmButton.rect)) return true;
    return false;
}

void draw_confirm_button(){
    SDL_Rect OKRect = {.w = ScreenWidth / 16.0 * 2.0, .h = ScreenHeight / 18.0 * 1.0, .x = ScreenWidth /  16.0 * 14.0, .y = ScreenHeight / 9.0 * 8.0};
    confirmButton.rect = OKRect;
    SDL_RenderCopy(main_window_renderer, buttonImg, NULL, &OKRect);
    SDL_Color color = {0, 0, 0};
    SDL_Surface *textTmp = TTF_RenderUTF8_Blended(button_Font, confirmButton.msg, color);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(main_window_renderer, textTmp);
    OKRect.x += OKRect.w / 10.0 * 3.0, OKRect.y += OKRect.h / 10.0, OKRect.w *= 0.3, OKRect.h *= 0.8;
    SDL_RenderCopy(main_window_renderer, textTexture, 0, &OKRect);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textTmp);
}

bool draw_confirm_msg_and_choose_answer(char *msg){
    draw_ground();
    SDL_Color color = {0, 0, 0};
    Show_Buttons(buttonImg, YesNoButton, color);
    SDL_Surface *textTmp = TTF_RenderUTF8_Blended(button_Font, msg, color);
    SDL_Texture  *textTexture = SDL_CreateTextureFromSurface(main_window_renderer, textTmp);
    SDL_Rect msgRect = {.w = textTmp->w, .h = textTmp->h, .x = ScreenWidth / 2.0 - textTmp->w / 2.0, .y = ScreenHeight / 18.0 * 7.0};
    SDL_RenderCopy(main_window_renderer, textTexture, NULL, &msgRect);
    SDL_RenderPresent(main_window_renderer);
    SDL_Event event;
    SDL_Point point;
    int id;
    while(1) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                quit_Game();
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&point.x, &point.y);
                id = Get_Button_ID(point.x, point.y, YesNoButton);
                if (id == 1) {
                    SDL_DestroyTexture(textTexture);
                    SDL_FreeSurface(textTmp);
                    return true;
                } else if (id == 2) {
                    SDL_DestroyTexture(textTexture);
                    SDL_FreeSurface(textTmp);
                    return false;
                }
        }
    }
}

