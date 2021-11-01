//
// Created by blast on 2021/5/29.
//

#include <SDL2/SDL_mixer.h>

Mix_Music *backgroundMusic = NULL;
Mix_Chunk *drawCardSound = NULL;


void play_DrawCard_sound(){
    Mix_PlayChannel(1, drawCardSound,14);
}