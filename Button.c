//
// Created by blast on 2021/5/24.
//

#include "Button.h"
#include "Window.h"
#include <SDL2/SDL.h>

SDL_Texture  *buttonImg = NULL;


void Show_Buttons(SDL_Texture *buttonImg, buttonItem *buttons, SDL_Color color) {
    size_t size = get_Button_Size(buttons);
    int i = 0;
    while(i < size) {
        SDL_Surface *textTmp = TTF_RenderUTF8_Blended(button_Font, buttons[i].msg, color);
        SDL_Texture *text = SDL_CreateTextureFromSurface(main_window_renderer, textTmp);
        int mid_y = ScreenHeight / (size + 2) * (i + 1) + textTmp->h / 2;
        buttons[i].rect.w = ScreenWidth / 2;
        buttons[i].rect.h = textTmp->h * 1.5;
        buttons[i].rect.x = ScreenWidth / 3.95;
        buttons[i].rect.y = mid_y - textTmp->h / 1.5;
        SDL_Rect textRect = {.w = textTmp->w, .h = textTmp->h, .x = ScreenWidth / 2.0 - textTmp->w / 2.0, .y = ScreenHeight / (size + 2) * (i + 1)};
        SDL_RenderCopy(main_window_renderer, buttonImg, NULL, &buttons[i].rect);
        SDL_RenderCopy(main_window_renderer, text, NULL, &textRect);

        SDL_FreeSurface(textTmp);
        SDL_DestroyTexture(text);
        ++i;
    }
}

int Get_Button_ID(int x, int y, buttonItem *buttons) {
    size_t buttonSize = get_Button_Size(buttons);
    SDL_Point point = {x, y};
    for(int i = 0; i < buttonSize; ++i){
        if(SDL_PointInRect(&point, &buttons[i].rect)){
            return i + 1;
        }
    }
    return -1;
}

size_t get_Button_Size(buttonItem *buttons){
    size_t size = 0;
    for(; buttons[size].msg[0] != '\0'; ++size );
    return size;
}

