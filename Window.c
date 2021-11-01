//
// Created by blast on 2021/5/29.
//

#include "Window.h"
#include "Sanjuandata.h"
#include "Draw.h"
#include "Card.h"
#include "Career.h"



SDL_Window* main_window = NULL;
SDL_Renderer* main_window_renderer = NULL;
TTF_Font* button_Font = NULL;

int ScreenWidth = 480;
int ScreenHeight = 320;

char fontPath[120] = "./Asset/Fonts/mc.ttf";

void update_window_res(){
    SDL_SetWindowSize(main_window, ScreenWidth, ScreenHeight);
    TTF_CloseFont(button_Font);
    button_Font = TTF_OpenFont(fontPath, 50 * (ScreenHeight / 760.0) );
    if(button_Font == NULL){
        printf( "Font could not be loaded, Use default! TTF_Error: %s\n", TTF_GetError());
        button_Font = TTF_OpenFont("./Asset/Fonts/mc.ttf", 50 * (ScreenHeight / 760.0) );
    }
}

void quit_Game(){
    SDL_DestroyTexture(backgroundImg);
    SDL_DestroyTexture(buttonImg);
    SDL_DestroyTexture(cardBack);
    SDL_DestroyTexture(trading_1);
    SDL_DestroyTexture(trading_2);
    SDL_DestroyTexture(trading_3);
    SDL_DestroyTexture(trading_4);
    SDL_DestroyTexture(trading_5);
    SDL_DestroyRenderer(main_window_renderer);
    SDL_DestroyWindow(main_window);

    destroy_card_texture();
    free_career_texture();
    //Mix_CloseAudio();
    exit(0);
}