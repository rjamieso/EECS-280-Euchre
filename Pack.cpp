//  Pack.cpp
//  p3-euchre
//
//  Created by Ronald Luke Jamieson on 2/18/23.

// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Pack.h"
#include "Card.h"
#include <array>
#include <string>
#include <cassert>

Pack::Pack() {
    next = 0; // Start of pack
    for(int suitnum = 0; suitnum < 4; ++suitnum){
        for(int ranknum = 7; ranknum < 13; ++ranknum){
            Rank rank = static_cast<Rank> (ranknum);
            Suit suit = static_cast<Suit> (suitnum);

            Card c = Card(rank,suit);
            cards[next] = c;
            
            ++next;
        }
    }
    next = 0; //Reset
}


Pack::Pack(std::istream& pack_input) {
    Rank card_rank;
    std::string junk;
    Suit card_suit;
    
    for(int next = 0; next < PACK_SIZE; ++next){
        pack_input >> card_rank >> junk >> card_suit;
        Card c = Card(card_rank,card_suit);
        cards[next] = c;
    }
    next = 0; // Reset
}


Card Pack::deal_one() {
    Card c;
    c = cards[next];
    ++next;
    return c;
}


void Pack::reset() {
    next = 0;
}


void Pack::shuffle() {
    std::array<Card,PACK_SIZE> copyarray = cards;
    
    int firsthalfend = (PACK_SIZE / 2); //Doesn't count 12
    int secondhalfend = PACK_SIZE; //Counts 12 but not 24 due to indexing
    int difffirsthalf = 1;
    int diffsecondhalf = 0;
    int shuffleamount = 7;

    for(int shufflecount = 0; shufflecount < shuffleamount; ++shufflecount){
        difffirsthalf = 1;
        diffsecondhalf = 0;
        for(int i = 0; i < PACK_SIZE; ++i){
            if((i < firsthalfend) && (i != firsthalfend)){
                Card c1; //Default card
                c1 = copyarray[i]; //Specifies card
                cards[difffirsthalf] = c1;
                difffirsthalf = difffirsthalf + 2; 
            }
            if((i >= firsthalfend) && (i < secondhalfend)){
                Card c2;
                c2 = copyarray[i];
                cards[diffsecondhalf] = c2;
                diffsecondhalf = diffsecondhalf + 2;
            }
        }
        copyarray = cards;
    }
}

bool Pack::empty() const {
    return next >= PACK_SIZE;
}

