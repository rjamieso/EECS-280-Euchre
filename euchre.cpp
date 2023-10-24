// Project UID 1d9f47bfc76643019cfbf037641defe1

//  main.cpp
//  p3-euchre
//
//  Created by Ronald Luke Jamieson on 2/11/23.
//
#include "Card.h"
#include "Pack.h"
#include "Player.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <array>

using namespace std;

// Look for any extra cin

class Game {
    private:
    //Read in variables
    Pack packused; //The pack we will use in our game
    bool shuffle; //Whether the pack will shuffle after each round
    int winningscore; //What the winning score will be
    std::vector<Player*> players; //Players in the game

    //Variables in the game
    std::vector<bool> isdealer; //Keeps track of the dealer
    Suit trumpsuit; //Keeps track of what the trump suit is
    int leader; //Leader of start of hand and for subsequent tricks
    bool team1m;
    bool team2m;
    int spot0, spot1, spot2, spot3;
    int dormindic;
    int handc1; //Keeps track of team 1 score in hand
    int handc2; //Keeps track of team 2 score in hand
    int team1s; //Keeps track of team 1 score overall
    int team2s; //Keeps track of team 2 score overall

    //Functions play will utilize

    //Shuffles the deck
    void shuffledeck(){
        if(shuffle == true){
            packused.shuffle();
        } 
    }

    //Deal the cards in the pack to the players
    void deal(){        
        //Creates used variables   
        packused.reset();
        int dealernum;
        //Gets the dealer number
        for(int i = 0; i < 4; ++i){
            if(isdealer[i] == true){
                cout << players[i]->get_name() << " deals" << endl;
                dealernum = i;
            }
        }
        //Determines order of distribution
        if(dealernum == 0){
            spot0 = dealernum; spot1 = 1; spot2 = 2; spot3 = 3;
        } else if(dealernum == 1){
            spot0 = dealernum; spot1 = 2; spot2 = 3; spot3 = 0;
        } else if(dealernum == 2){
            spot0 = dealernum; spot1 = 3; spot2 = 0; spot3 = 1;
        } else if(dealernum == 3){
            spot0 = dealernum; spot1 = 0; spot2 = 1; spot3 = 2;
        }
        //Distribute cards based on the dealer
        perform_deal();
    }

    //Sends out cards
    void perform_deal(){
        players[spot1]->add_card(packused.deal_one());
        players[spot1]->add_card(packused.deal_one());
        players[spot1]->add_card(packused.deal_one());
        //Batch 2
        players[spot2]->add_card(packused.deal_one());
        players[spot2]->add_card(packused.deal_one());
        //Batch 3
        players[spot3]->add_card(packused.deal_one());
        players[spot3]->add_card(packused.deal_one());
        players[spot3]->add_card(packused.deal_one());
        //Batch 4
        players[spot0]->add_card(packused.deal_one());
        players[spot0]->add_card(packused.deal_one());
        //Batch 5
        players[spot1]->add_card(packused.deal_one());
        players[spot1]->add_card(packused.deal_one());
        //Batch 6
        players[spot2]->add_card(packused.deal_one());
        players[spot2]->add_card(packused.deal_one());
        players[spot2]->add_card(packused.deal_one());
        //Batch 7
        players[spot3]->add_card(packused.deal_one());
        players[spot3]->add_card(packused.deal_one());
        //Batch 8
        players[spot0]->add_card(packused.deal_one());
        players[spot0]->add_card(packused.deal_one());
        players[spot0]->add_card(packused.deal_one());
    }

    //Makes the card trump
    void make_trump(){
        //Initialize starter player and get the upcard
        int sp,roundholder;
        Suit trump;
        Card upcard = get_upcard();
        operator<<(cout,upcard) << " turned up" << endl;
        //Determine the starterplayer
        if(isdealer[0] == true){
                sp = 1;
            } else if(isdealer[1] == true){
                sp = 2;
            } else if(isdealer[2] == true){
                sp = 3;
            } else if(isdealer[3] == true){
                sp = 0;
            }
            leader = sp;
        //Goes through each round and determine which players want to make trump
        for(int round = 1; round < 3; ++round){
            //Goes through each player
            for(int i = 0; i < 4; ++i){
                if(players[sp]->make_trump(upcard,isdealer[sp],round,trump) == true){
                    trumpsuit = trump;
                    roundholder = round;
                    cout << players[sp]->get_name();
                    cout << " orders up " << trumpsuit << endl << endl;
                    //Used to end finding out trump
                    i = 4; round = 3; dormindic = sp;
                //If they don't make trump
                } else{
                    cout << players[sp]->get_name() << " passes" << endl;
                }
                //Used to reset starterplayer
                ++sp;
                if(sp > 3){
                    sp = 0;
                }
            }
        }
        //Determines which teams are the makers and defenders
        def_or_mak();

        //Checks each player to determine if dealer; if dealer and its round 1
        //Have them pick up the upcard and discard a card
        for(int i = 0; i < 4; ++i){
            if((roundholder == 1) && (isdealer[i] == true)){
                players[i]->add_and_discard(upcard);
            }
        }
    }

    void def_or_mak(){
       if((dormindic == 0) || (dormindic == 2)){
            team1m = true; team2m = false;
        } else if((dormindic == 1) || (dormindic == 3)){
            team1m = false; team2m = true;
        } 
    }

    //Play the hand, basically repeat this until a team wins
    void play_hand(){ 
        handc1 = 0; handc2 = 0;
        //Play through each of the tricks
        for(int hand = 0; hand < 5; ++hand){ 
            play_trick(); }
        //Determine winners and update overall score
        declare_hand_winner();
    }

    void declare_hand_winner(){
        if(((handc1 == 3) || (handc1 == 4)) && (team1m == true)){ team1s=team1s+1;
            //Team 1 were makers and won the trick
            cout << players[0]->get_name() << " and " << players[2]->get_name();
            cout << " win the hand" << endl;
        } else if((handc1 == 5) && (team1m == true)){ team1s = team1s + 2;
            //Team 1 were makers and performed a march
            cout << players[0]->get_name() << " and " << players[2]->get_name();
            cout << " win the hand" << endl; cout << "march!" << endl;
        } else if(((handc1 == 0) || (handc1 == 1) || (handc1 == 2)) && (team1m == true)){
            //Team 1 were makers but failed the trick
            team2s = team2s + 2;
            cout << players[1]->get_name() << " and " << players[3]->get_name();
            cout << " win the hand" << endl; cout << "euchred!" << endl;
        } else if(((handc2 == 3) || (handc2 == 4)) && (team2m == true)){ team2s=team2s+1;
            //Team 2 were makers and won the trick
            cout << players[1]->get_name() << " and " << players[3]->get_name();
            cout << " win the hand" << endl;
        } else if((handc2 == 5) && (team2m == true)){ team2s = team2s + 2;
            //Team 2 were makers and performed a march
            cout << players[1]->get_name() << " and " << players[3]->get_name();
            cout << " win the hand" << endl; cout << "march!" << endl;
        } else if(((handc2 == 0) || (handc2 == 1) || (handc2 == 2)) && (team2m == true)){
            //Team 2 were makers but failed the trick
            team1s = team1s + 2;
            cout << players[0]->get_name() << " and " << players[2]->get_name();
            cout << " win the hand" << endl; cout << "euchred!" << endl;
        }
        cout << players[0]->get_name() << " and " << players[2]->get_name();
        cout << " have " << team1s << " points" << endl;
        cout << players[1]->get_name() << " and " << players[3]->get_name();
        cout << " have "<< team2s << " points" << endl; cout << endl;
    }

    //Plays the individual trick in the hanad
    void play_trick(){
        //Initiates the leadcard and creates a copy of it
        Card leadcard = players[leader]->lead_card(trumpsuit);Card lch = leadcard;
        //Displays who led the trick and pushes back needed values to respective vectors
        operator<<(cout,leadcard)<<" led by "<<players[leader]->get_name();
        cout << endl;
        std::vector<int> playernum; std::vector<Card> playedcards;
        playedcards.push_back(leadcard); playernum.push_back(leader); ++leader;
        //Goes through the remaining three players and obtains their played card
        for(int i = 0; i < 3; ++i){
            reset_leader();
            Card c = players[leader]->play_card(leadcard,trumpsuit);
            operator<<(cout,c)<<" played by "<<players[leader]->get_name();
            cout << endl;
            playedcards.push_back(c); playernum.push_back(leader); ++leader;
        }
        //Begins the processing of comparing to find the highest card
        int playerwinum = playernum[0];
        for(int selcard = 1; selcard < 4; ++selcard){
            Card temp = playedcards[selcard];
            if(Card_less(leadcard,temp,lch,trumpsuit) == true){
                leadcard = temp; playerwinum = playernum[selcard];
            }
        }
        //Once highest card is found, find the player and print out they won the trick
        for(int i = 0; i < 4; ++i){
            if(playerwinum == i){
                cout << players[i]->get_name() << " takes the trick" << endl;
                cout << endl;
                leader = i;
                if((playerwinum == 0) || (playerwinum == 2)){
                    ++handc1;
                } else if((playerwinum == 1) || (playerwinum == 3)){
                    ++handc2;
                }
            }
        }
    }

    //Assigns who is the dealer
    void make_dealer(){
        if(isdealer[0] == true){
            isdealer[0] = false;
            isdealer[1] = true;
            isdealer[2] = false;
            isdealer[3] = false;
        } else if(isdealer[1] == true){
            isdealer[0] = false;
            isdealer[1] = false;
            isdealer[2] = true;
            isdealer[3] = false;
        } else if(isdealer[2] == true){
            isdealer[0] = false;
            isdealer[1] = false;
            isdealer[2] = false;
            isdealer[3] = true;
        } else if(isdealer[3] == true){
            isdealer[0] = true;
            isdealer[1] = false;
            isdealer[2] = false;
            isdealer[3] = false;
        }
    }

    //Gets the upcard
    Card get_upcard(){
        Card upcard = packused.deal_one();
        packused.reset();
        return upcard;
    }

    void reset_leader(){
        if(leader > 3){
            leader = 0;
        }
    }

    public:
    //Constructor of Game
    Game(Pack inpack,bool shuforno,int pointstowin,std::vector<Player*> readinplayers){
        packused = inpack;
        shuffle = shuforno;
        winningscore = pointstowin;
        players = readinplayers;
    }
    
    //Plays the game
    void play(){
        int hand = 0;
        isdealer = {true,false,false,false}; //Initial dealer
        team1s = 0;
        team2s = 0;
        while((team1s < winningscore) && (team2s < winningscore)){
            cout << "Hand " << hand << endl;
            shuffledeck();
            deal();
            make_trump();
            play_hand();
            make_dealer();
            ++hand;
        }
        if(team1s >= winningscore){
            cout << players[0]->get_name() << " and " << players[2]->get_name();
            cout << " win!" << endl;
        } else if(team2s >= winningscore){
            cout << players[1]->get_name() << " and " << players[3]->get_name();
            cout << " win!" << endl;
        }
    }
};

int main(int argc, char **argv){
    for(int i = 0; i < 12; ++i){
        cout << argv[i] << " ";
    }
    cout << endl;
    if(argc != 12){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
        return 1;
    }
    //Reads in pack used
    std::string inputpackname = argv[1];
    std::ifstream fin(inputpackname);
    Pack packin(fin);
    if(!fin.is_open()){
        cout << "Error opening " << inputpackname << endl;
        return 1;
    }
    //Reads in whether to shuffle or not
    bool shuffledeck;
    std::string shuffledecision = argv[2];
    if(!((shuffledecision == "shuffle") || (shuffledecision == "noshuffle"))){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
        return 1;
    }
    if(shuffledecision == "shuffle"){
        shuffledeck = true;
    }else if(shuffledecision == "noshuffle"){
        shuffledeck = false;
    }
    //Read in points needed
    int pointsneeded = atoi(argv[3]);
    if((pointsneeded < 0) || (pointsneeded > 100)){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
        return 1;
    }
    //Reads in players
    int indexer = 4;
    std::vector<Player*> playersingame;
    for(int i = 0; i < 4; ++i){
        std::string type = argv[indexer + 1];
        if(!((type == "Simple") || (type == "Human"))){
            cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
            return 1;
        }
        playersingame.push_back(Player_factory(argv[indexer],argv[indexer + 1]));
        indexer = indexer + 2;
    }
    //Initiates the game
    //This will read in the specifications of the game
    Game game(packin,shuffledeck,pointsneeded,playersingame);
    //Will play the game out with the given conditions and player types
    game.play();
    //After the game is over, will delete the players
    for(int j = 0; j < 4; ++j){
        delete playersingame[j];
    }
}
