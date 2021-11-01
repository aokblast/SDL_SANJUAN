//
// Created by blast on 2021/5/29.
//

#include "Deck.h"

card_t deck[128];
card_t discard[128];

int deckTop = 0;
int discardTop = 0;

void shuffle(){
    for(int i = 0; i < deckTop; ++i) {
        int toChange = rand() % (deckTop);
        card_t tmp = deck[i];
        deck[i] = deck[toChange];
        deck[toChange] = tmp;
    }
}

card_t draw(){
    if(deckTop == 0) {
        for(int i = 0; i < discardTop; ++i) {
            deck[i] = discard[i];
            ++deckTop;
        }
        shuffle();
        discardTop = 0;
    }
    return deck[--deckTop];
}

void disard_card(card_t card) {
    card.pos.h = card.pos.y = card.pos.x = card.pos.w = 0;
    card.next = NULL;
    card.tokens = NULL;
    discard[discardTop++] = card;
}
