cmake_minimum_required(VERSION 3.15)
project(SanJuan-SDL C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)


add_executable(SanJuan-SDL Main.c)
add_library(argv STATIC Argv.c)
add_library(game_main STATIC GameMain.c)
add_library(card STATIC Card.c)
add_library(button STATIC Button.c)
add_library(setting STATIC Setting.c)
add_library(window STATIC Window.c)
add_library(sound STATIC Sound.c)
add_library(language STATIC Language.c)
add_library(player STATIC Player.c)
add_library(deck STATIC Deck.c)
add_library(career STATIC Career.c)
add_library(draw STATIC Draw.c)
add_library(bot STATIC Bot.c)


target_link_libraries(game_main INTERFACE -lSDL2)
target_link_libraries(game_main INTERFACE -lSDL2_image)
target_link_libraries(game_main INTERFACE -lSDL2_ttf)
target_link_libraries(game_main INTERFACE -lSDL2_mixer)


target_link_libraries(SanJuan-SDL PUBLIC argv)
target_link_libraries(SanJuan-SDL PUBLIC game_main)
target_link_libraries(SanJuan-SDL PUBLIC button)
target_link_libraries(SanJuan-SDL PUBLIC card)
target_link_libraries(SanJuan-SDL PUBLIC setting)
target_link_libraries(SanJuan-SDL PUBLIC window)
target_link_libraries(SanJuan-SDL PUBLIC sound)
target_link_libraries(SanJuan-SDL PUBLIC language)
target_link_libraries(SanJuan-SDL PUBLIC player)
target_link_libraries(SanJuan-SDL PUBLIC deck)
target_link_libraries(SanJuan-SDL PUBLIC career)
target_link_libraries(SanJuan-SDL PUBLIC draw)
target_link_libraries(SanJuan-SDL PUBLIC bot)


target_compile_options(SanJuan-SDL PUBLIC -D ENGLISH)

