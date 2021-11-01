//
// Created by blast on 2021/5/24.
//

#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include "Draw.h"
#include "Argv.h"
#include "Sanjuandef.h"
#include "Button.h"
#include "GameMain.h"
#include "Setting.h"
#include "Window.h"
#include "Sound.h"
#include "Language.h"
#include "Card.h"
#include "Player.h"
#include "Career.h"
#include "Deck.h"
#include "Bot.h"

extern char MAIN_SINGLE[20];
extern char MAIN_MULTI[20];
extern char MAIN_SETTING[10];
extern char MAIN_EXIT[10];
extern char LOOP_4_PLAYERS[20];
extern char LOOP_3_PLAYERS[20];
extern char LOOP_2_PLAYERS[20];
extern char SETTING_BACK[20];
extern char MAIN_DIFFICULTY[20];

static gameMode_t startGameMode = GM_EXIT;
static int botDifficulty = 0;
player_t **players;
card_t *careers;
career_t presentCareer;
phase_t presentPhase;
int8_t totalPlayer = 0;


SDL_Texture *backgroundImg = NULL;


static buttonItem menuButtons[] = {
        {MAIN_SINGLE, {0, 0}},
        {MAIN_MULTI,  {0, 0}},
        {MAIN_SETTING, {0, 0}},
        {MAIN_EXIT, {0, 0}},
        {"", {0, 0}}
};

static buttonItem playerButtons[] = {
        {LOOP_4_PLAYERS, {0, 0}},
        {LOOP_3_PLAYERS, {0, 0}},
        {LOOP_2_PLAYERS, {0, 0}},
        {SETTING_BACK, {0, 0}},
        {"", {0, 0}}
};

static buttonItem DifficultyButtons[] = {
        {MAIN_DIFFICULTY, {0, 0}},
        {"1", {0, 0}},
        {"2", {0 ,0}},
        {SETTING_BACK, {0, 0}},
        {"", {0, 0}}
};

static buttonItem MultiButtons[] = {
        {"Not yet implemented", {0, 0}},
        {SETTING_BACK, {0, 0}},
        {"", {0, 0}}
};

void SANJUAN_Loop();
int SANJUAN_Menu();
int Init_Graphic_Lib();
int load_start_Resource();
int load_in_game_resource();


void printPlayerInfo(int j){ // for debug
    printf("Player:%d\n", (j % 4 )+ 1);
    printf("Ground:\n");
    for(card_t *trav = players[j % 4]->ground; trav != NULL; trav = trav->next){
        printf("%s\n", trav->cardName);
    }
    printf("Hand:\n");
    for(card_t *trav = players[j % 4]->hand; trav != NULL; trav = trav->next){
        printf("%s\n", trav->cardName);
    }
}

int SANJUAN_Main() {
    SDL_Color  gray = {0, 0, 0};
    //Parse Argument
    int arg_loc = 0;
    char *errptr = NULL;

    set_language("English");

    if(( arg_loc = check_Param("--Width")) || ( arg_loc = check_Param("-W"))) {
        ScreenWidth = strtol(myargv[arg_loc + 1], &errptr, 10);
        if(*errptr != '\0') ScreenWidth = 1600;
    }
    if( (arg_loc = check_Param("--Height")) || (arg_loc = check_Param("-H"))) {
        ScreenHeight = strtol(myargv[arg_loc + 1], &errptr, 10);
        if(*errptr != '\0') ScreenHeight = 900;
    }
    if((arg_loc = check_Param("--Font")) || (arg_loc = check_Param("-F"))) {
        button_Font = TTF_OpenFont(myargv[arg_loc + 1], 50 * (ScreenHeight / 760.0));
        if(!button_Font) printf("Wrong initialize font with %s(Use default setting)! TTF_Error: %s\n", myargv[arg_loc + 1], TTF_GetError());
        else strcpy(fontPath, myargv[arg_loc + 1]);
    }
    if((arg_loc = check_Param("--GameMode")) || (arg_loc = check_Param("-G"))){
        if(strcmp(myargv[arg_loc + 1], "Single") == 0){
            startGameMode = GM_SINGLE;
        }else if(strcmp(myargv[arg_loc + 1], "Multi") == 0){
            startGameMode = GM_MULTI;
        }else{
            printf("Wrong parameter: %s\n", myargv[arg_loc + 1]);
        }
    }
    if((arg_loc = check_Param("--Lang")) || (arg_loc = check_Param("-L"))){
        if(strcmp(myargv[arg_loc + 1], "English") == 0){
            set_language(myargv[arg_loc + 1]);
        }else if(strcmp(myargv[arg_loc + 1], "Chinese") == 0){
            set_language(myargv[arg_loc + 1]);
        }else{
            printf("Wrong parameter: %s\n", myargv[arg_loc + 1]);
        }
    }

    //Initialze Graphic library

    if(!Init_Graphic_Lib()){
        return 0;
    }

    if(!load_start_Resource()){
        return 0;
    }

    //Goto Menu
    Menu:
    SANJUAN_Menu();


    //Goto StartGame Loop
    if(startGameMode == GM_SINGLE){
        SANJUAN_Loop();
    };

    quit_Game();
    return 1;

}

int SANJUAN_Menu(){

    SDL_Event event;
    SDL_Color  gray = {0, 0, 0};

    bool quitMenu = false;
    buttonItem *presentButtons;
    if(startGameMode == GM_EXIT){
        presentButtons = menuButtons;
    }else if(startGameMode == GM_SINGLE){
        presentButtons = playerButtons;
    }else if(startGameMode == GM_MULTI){
        presentButtons = MultiButtons;
    }


    while(!quitMenu) {
        SDL_RenderClear(main_window_renderer);
        SDL_RenderCopy(main_window_renderer, backgroundImg, NULL, NULL);
        Show_Buttons(buttonImg, presentButtons, gray);
        SDL_RenderPresent(main_window_renderer);

        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                quit_Game();
                break;
            case SDL_MOUSEBUTTONDOWN: {
                int pos_x = 0, pos_y = 0;
                SDL_GetMouseState(&pos_x, &pos_y);
                int choose = Get_Button_ID(pos_x, pos_y, presentButtons);

                if(totalPlayer != 0){
                    switch(choose){
                        case 2:
                            botDifficulty = 1;
                            quitMenu = true;
                            break;
                        case 3:
                            botDifficulty = 2;
                            quitMenu = true;
                            break;
                        case 4:
                            totalPlayer = 0;
                            presentButtons = playerButtons;
                            break;
                    }
                }else if(startGameMode == GM_SINGLE){
                    switch (choose) {
                        case 1:
                            totalPlayer = 4;
                            presentButtons = DifficultyButtons;
                            break;
                        case 2:
                            totalPlayer = 3;
                            presentButtons = DifficultyButtons;
                            break;
                        case 3:
                            totalPlayer = 2;
                            presentButtons = DifficultyButtons;
                            break;
                        case 4:
                            startGameMode = GM_EXIT;
                            presentButtons = menuButtons;
                            break;
                    }
                }else if(startGameMode == GM_MULTI) {
                    switch(choose){
                        case 1:
                            break;
                        case 2:
                            presentButtons = menuButtons;
                            startGameMode = GM_EXIT;
                            break;
                    }
                }else{
                    switch (choose) {
                        case 1:
                            startGameMode = GM_SINGLE;
                            presentButtons = playerButtons;
                            break;
                        case 2:
                            startGameMode = GM_MULTI;
                            presentButtons = MultiButtons;
                            break;
                        case 3:
                            setting();
                            break;
                        case 4:
                            quitMenu = true;
                            startGameMode = GM_EXIT;
                            break;
                    }
                }

                break;
            }
        }

    }

    SDL_RenderClear(main_window_renderer);
    SDL_RenderPresent(main_window_renderer);
}

void SANJUAN_Loop() {
    bool endGame = false;
    int turn = rand() % totalPlayer;
    presentPhase = PH_ROUND;

    if(!load_in_game_resource()){
        return ;
    }

    init_deck();
    shuffle();
    players = calloc(totalPlayer, sizeof(player_t *));

    for(int i = 0; i < totalPlayer; ++i){
        players[(i + turn) % totalPlayer] = init_player((i + turn) % totalPlayer + 1, 5 + i);
    }
    players[0]->chooseCard = player_choose_Card;
    players[0]->chooseCareer = player_choose_career;

    for(int i = 1; i < totalPlayer; ++i){
        get_Bot_Func(players[i], botDifficulty);
    }

    for(int i = 0; i < totalPlayer; ++i){
        int totalDisacrd = 0;
        while(players[i]->totalHand > 4){
            presentPhase = PH_DISCARD;
            card_t *card = players[i]->chooseCard(players[i], &players[i]->hand);
            disard_card(*card);
            free(card);
            --players[i]->totalHand;
            ++totalDisacrd;
        }
        if(i != 0) draw_bot_choose_msg_and_wait_for_confirm(i + 1, &totalDisacrd);
    }


    while(!endGame){
        careers = init_career_list();
        SDL_RenderClear(main_window_renderer);
        draw_ground();
        SDL_RenderPresent(main_window_renderer);
        presentPhase = PH_ROUND;
        draw_bot_choose_msg_and_wait_for_confirm( (turn % totalPlayer) + 1, NULL);
        for(int i = 0; i < totalPlayer; ++i){
            check_effect(players[i]);
            presentPhase = PH_DISCARD;
            int disCardHand = 0;
            while(players[i]->totalHand > players[i]->maxHand){
                card_t *card = players[i]->chooseCard(players[i], &players[i]->hand);
                disard_card(*card);
                free(card);
                --players[i]->totalHand;
                ++disCardHand;
            }
            if(i != 0 && disCardHand != 0) draw_bot_choose_msg_and_wait_for_confirm(i + 1, &disCardHand);
            players[i]->maxHand = 7;
            presentPhase = PH_ROUND;

        }

        for(int i = turn; i < turn + totalPlayer; ++i) {
            presentPhase = PH_CHOOSECAREER;
            presentCareer = players[i % totalPlayer]->chooseCareer(players[i % totalPlayer]);

            //printf("PresentCareer:%d\n", presentCareer);
            //printf("Remain Cards:\n");
            //for(card_t *trav = players[0]->hand; trav != NULL; trav = trav->next){
            //    printf("%s ", trav->cardName);
            //}
            //printf("\n");

            switch (presentCareer) {
                case CR_TRADER:
                    presentPhase = PH_TRADER;
                    break;
                case CR_PROSEPCTOR:
                    presentPhase = PH_PROSPECTOR;
                    break;
                case CR_PRODUCER:
                    presentPhase = PH_PRODUCER;
                    break;
                case CR_COUNCILLOR:
                    presentPhase = PH_COUNCILLOR;
                    break;
                case CR_BUILDER:
                    presentPhase = PH_BUILDER;
                    break;
            }


            execute_prev(players[i % totalPlayer]);
            //printf("%d\n", players[0]->totalHand);
            if(players[i % totalPlayer]->totalBuilding >= 12) {

                endGame = true;
                break;
            }


            for (int j = i + 1; j < i + totalPlayer; ++j) {

                //printf("Before:\n");
                //printPlayerInfo(j);
                execute_norm(players[j % totalPlayer]);
                //printf("%d\n", players[0]->totalHand);
                if(players[j % totalPlayer]->totalBuilding >= 12) {
                    endGame = true;
                    break;
                }

                //printf("After:\n");
                //printPlayerInfo(j);
            }
            //printf("\n");
            if(endGame == true) break;

        }


        ++turn;
        destroy_career_list(careers);



    }
    presentPhase = PH_GAMEEND;
    int winID = 0;
    for(int i = 0; i < totalPlayer; ++i){
        check_effect(players[i]);
        for(card_t *trav = players[i]->ground; trav != NULL; trav = trav->next) players[i]->victoryPoint += trav->victoryPoint;
        if(has_palace(players[i]->ground)) players[i]->victoryPoint += players[i]->victoryPoint / 4;
        if(players[i]->victoryPoint > players[winID]->victoryPoint) winID = i;
    }
    presentPhase = PH_GAMEEND;
    draw_bot_choose_msg_and_wait_for_confirm(winID + 1, NULL);



    for(int i = 0; i < totalPlayer; ++i){
        clear_player(players[i]);
    }
    free(players);

}

int Init_Graphic_Lib() {
    if(SDL_Init(SDL_INIT_EVERYTHING)  < 0) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return 0;
    }
    if(!IMG_Init(IMG_INIT_JPG) ) {
        printf( "Image could not initialize! IMG_Error: %s\n", IMG_GetError() );
        return 0;
    }

    if(!IMG_Init(IMG_INIT_PNG)) {
        printf( "Image could not initialize! IMG_Error: %s\n", IMG_GetError() );
        return 0;
    }
    if(TTF_Init() < 0) {
        printf("TTF could not be initialize! TTF_Error: %s\n", TTF_GetError());
        return 0;
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        return 0;
    }
    return 1;
}

int load_start_Resource(){

    if(!button_Font) button_Font = TTF_OpenFont(fontPath, 50 * (ScreenHeight / 760.0) );
    if(button_Font == NULL) {
        printf( "Font could not be loaded! TTF_Error: %s\n", TTF_GetError() );
    }
    srand(time(NULL));

    main_window = SDL_CreateWindow("SANJUAN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ScreenWidth, ScreenHeight,SDL_WINDOW_SHOWN);
    if(main_window == NULL) {
        printf( "Menu could not be created! SDL_Error: %s\n", SDL_GetError() );
        return 0;
    }

    backgroundMusic = Mix_LoadMUS("./Asset/Sound/backGround_sound.mp3");
    if(backgroundMusic == NULL) {
        printf( "Music could not be loaded! Mix:Error: %s\n", Mix_GetError());
        return 0;
    }

    main_window_renderer = SDL_CreateRenderer(main_window, -1, 0);
    if(main_window_renderer == NULL) {
        printf("Renderer could not be created! SDL:Error: %s\n", SDL_GetError());
    }

    backgroundImg = IMG_LoadTexture(main_window_renderer, "./Asset/Menu_Background.jpg");
    if(backgroundImg == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }

    buttonImg = IMG_LoadTexture(main_window_renderer, "./Asset/buttons.png");
    if(buttonImg == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }

    Mix_PlayMusic(backgroundMusic, -1);
    load_language();

    return 1;
}

int load_in_game_resource(){
    if(!load_card_texture()){
        return 0;
    }
    if(!load_career_texture()){
        return 0;
    }
    SDL_DestroyTexture(backgroundImg);
    backgroundImg = IMG_LoadTexture(main_window_renderer, "./Asset/In_game_background.png");
    if(backgroundImg == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    cardBack = IMG_LoadTexture(main_window_renderer, "./Asset/large_card_back.gif");
    if(backgroundImg == NULL) {
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    trading_1 = IMG_LoadTexture(main_window_renderer, "./Asset/trade_1.gif");
    if(trading_1 == NULL){
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    trading_2 = IMG_LoadTexture(main_window_renderer, "./Asset/trade_2.gif");
    if(trading_2 == NULL){
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    trading_3 = IMG_LoadTexture(main_window_renderer, "./Asset/trade_3.gif");
    if(trading_3 == NULL){
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    trading_4 = IMG_LoadTexture(main_window_renderer, "./Asset/trade_4.gif");
    if(trading_4 == NULL){
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    trading_5 = IMG_LoadTexture(main_window_renderer, "./Asset/trade_5.gif");
    if(trading_5 == NULL){
        printf( "Image could not be loaded! IMG:Error: %s\n", IMG_GetError());
        return 0;
    }
    drawCardSound = Mix_LoadWAV("./Asset/Sound/drawCard.mp3");
    if(drawCardSound == NULL) {
        printf( "Music could not be loaded! Mix:Error: %s\n", Mix_GetError());
        return 0;
    }

    return 1;
}