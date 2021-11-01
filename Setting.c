//
// Created by blast on 2021/5/26.
//

#include "Setting.h"
#include "Button.h"
#include "Sanjuandata.h"
#include "stdbool.h"
#include "SDL2/SDL.h"
#include "Window.h"
#include "Language.h"

extern char SETTING_SOUND[10];
extern char SETTING_LANGUAGE[10];
extern char SETTING_WINDOW[20];
extern char SETTING_BACK[10];
extern char SETTING_LANG_ENGLISH[10];
extern char SETTING_LANG_CHINESE[10];

static buttonItem settingButtons[] = {
        {SETTING_SOUND, {0, 0} },
        {SETTING_LANGUAGE,  {0, 0} },
        {SETTING_WINDOW, {0, 0} },
        {SETTING_BACK, {0, 0} },
        {"", {0, 0} }
};

static buttonItem resolutionsButtons[] = {
        {"800 * 450", {0, 0} },
        {"1280 * 760", {0, 0} },
        {"1366 * 768", {0, 0} },
        {"1440 * 810", {0, 0} },
        {"1600 * 900", {0, 0} },
        {"", {0, 0} }
};

static buttonItem soundButtons[] = {
        {"0%", {0, 0} },
        {"25%", {0, 0} },
        {"50%", {0, 0} },
        {"75%", {0, 0} },
        {"100%", {0, 0} },
        {"", {0, 0} }
};

static buttonItem langButtons[] = {
        {SETTING_LANG_ENGLISH, {0, 0} },
        {SETTING_LANG_CHINESE, {0, 0} },
        {"", {0, 0} }
};


typedef enum {
    ST_,
    ST_SOUND,
    ST_LANGUAGE,
    ST_GRAPHIC,
    ST_BACK,
} setting_t;

void setting() {
    SDL_Color gray = {0, 0, 0};
    bool quitSetting = false;
    bool change = false;
    SDL_Event event;
    buttonItem *presentButton = settingButtons;
    setting_t setting = ST_;

    while(!quitSetting){
        SDL_RenderClear(main_window_renderer);
        SDL_RenderCopy(main_window_renderer, backgroundImg, NULL, NULL);
        Show_Buttons(buttonImg, presentButton, gray);
        SDL_RenderPresent(main_window_renderer);
        SDL_WaitEvent(&event);

        switch(event.type){
            case SDL_QUIT:
                quit_Game();
                break;
            case SDL_MOUSEBUTTONDOWN: {
                int pos_x = 0, pos_y = 0;
                SDL_GetMouseState(&pos_x, &pos_y);
                int choose = Get_Button_ID(pos_x, pos_y, presentButton);
                if(setting == ST_LANGUAGE){
                    switch (choose) {
                        case 1:
                            change = true;
                            set_language("English");
                            break;
                        case 2:
                            change = true;
                            set_language("Chinese");
                            break;
                    }
                    if(change){
                        change = false;
                        setting = ST_;
                        presentButton = settingButtons;
                        load_language();
                    }

                }else if(setting == ST_SOUND){
                    switch (choose) {
                        case 1:
                            change = true;
                            Mix_VolumeMusic(0);
                            break;
                        case 2:
                            change = true;
                            Mix_VolumeMusic(32);
                            break;
                        case 3:
                            change = true;
                            Mix_VolumeMusic(64);
                            break;
                        case 4:
                            change = true;
                            Mix_VolumeMusic(96);
                            break;
                        case 5:
                            change = true;
                            Mix_VolumeMusic(128);
                            break;
                    }

                    if(change) {
                        change = false;
                        setting = ST_;
                        presentButton = settingButtons;
                    }
                }else if(setting == ST_GRAPHIC){
                    switch (choose) {
                        case 1:
                            ScreenWidth = 800;
                            ScreenHeight = 450;
                            change = true;
                            break;
                        case 2:
                            ScreenWidth = 1280;
                            ScreenHeight = 760;
                            change = true;
                            break;
                        case 3:
                            ScreenWidth = 1366;
                            ScreenHeight = 768;
                            change = true;
                            break;
                        case 4:
                            ScreenWidth = 1440;
                            ScreenHeight = 810;
                            change = true;
                            break;
                        case 5:
                            ScreenWidth = 1600;
                            ScreenHeight = 900;
                            change = true;
                            break;
                    }
                    if(change){
                        setting = ST_;
                        presentButton = settingButtons;
                        update_window_res();
                        change = false;
                    }


                }
                else {
                    switch (choose) {
                        case 1:
                            presentButton = soundButtons;
                            setting = ST_SOUND;
                            break;
                        case 2:
                            presentButton = langButtons;
                            setting = ST_LANGUAGE;
                            break;
                        case 3:
                            presentButton = resolutionsButtons;
                            setting = ST_GRAPHIC;
                            break;
                        case 4:
                            setting = ST_BACK;
                            quitSetting = true;
                            break;
                    }
                }
                break;
            }
        }
    }
}



