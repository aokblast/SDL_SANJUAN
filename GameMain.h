//
// Created by blast on 2021/5/24.
//

#ifndef COMPUTER_PROGRAMMING_FINAL_PROJECT_GAMEMAIN_H
#define COMPUTER_PROGRAMMING_FINAL_PROJECT_GAMEMAIN_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdint.h>
#include "Sanjuandata.h"

extern career_t presentCareer;
extern card_t *careers;
extern phase_t presentPhase;
extern int8_t totalPlayer;
extern player_t **players;
extern int remainCareerNum;

int SANJUAN_Main();

#endif //COMPUTER_PROGRAMMING_FINAL_PROJECT_GAMEMAIN_H
