//
// Created by blast on 2021/5/24.
//

#ifndef COMPUTER_PROGRAMMING_FINAL_PROJECT_BUTTON_H
#define COMPUTER_PROGRAMMING_FINAL_PROJECT_BUTTON_H
#include <SDL2/SDL.h>

typedef struct _ButtonItem{
    char *msg;
    SDL_Rect rect;
} buttonItem;


void Show_Buttons(SDL_Texture *buttonImg, buttonItem *buttons, SDL_Color color);
size_t get_Button_Size(buttonItem *buttons);
int Get_Button_ID(int x, int y, buttonItem *buttons);

#endif //COMPUTER_PROGRAMMING_FINAL_PROJECT_BUTTON_H

