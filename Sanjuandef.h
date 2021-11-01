//
// Created by blast on 2021/5/24.
//

#ifndef COMPUTER_PROGRAMMING_FINAL_PROJECT_SANJUANDEF_H
#define COMPUTER_PROGRAMMING_FINAL_PROJECT_SANJUANDEF_H


typedef enum {
    GM_EXIT,
    GM_SINGLE,
    GM_MULTI,
} gameMode_t;

typedef enum {
    CR_BUILDER = 0,
    CR_COUNCILLOR = 1,
    CR_PRODUCER = 2,
    CR_PROSEPCTOR = 3,
    CR_TRADER = 4,
} career_t;

typedef enum {
    FACTORY,
    SPECIAL,
} building_t;

#endif //COMPUTER_PROGRAMMING_FINAL_PROJECT_SANJUANDEF_H
