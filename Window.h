//
// Created by blast on 2021/5/29.
//

#ifndef COMPUTER_PROGRAMMING_FINAL_PROJECT_WINDOW_H
#define COMPUTER_PROGRAMMING_FINAL_PROJECT_WINDOW_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

extern SDL_Texture  *buttonImg;
extern SDL_Window *main_window;
extern SDL_Renderer* main_window_renderer;
extern TTF_Font* button_Font;


extern int ScreenWidth;
extern int ScreenHeight;
extern char fontPath[120];

void quit_Game();
void update_window_res();

#endif //COMPUTER_PROGRAMMING_FINAL_PROJECT_WINDOW_H
