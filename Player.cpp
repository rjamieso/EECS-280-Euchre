// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Player.h"
// #include "Pack.h"
#include "Card.h"
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>

// should class go before all this? probably


// specific kind of player derived from player class
// use drawcard from pack to get card and point to it
// create an array of pointers



class SimplePlayer : public Player {
    
    
private:
    // variable for player name
    std::string name;
    // vector of Card for hands
    std::vector<Card> hand;
    //hand.erase(hand.begin() + i);
    
public:
    SimplePlayer(const std::string &name) : name(name){}
    
    virtual const std::string & get_name() const{
    return this->name;
     /*
    // return name of player
    virtual const std::string & get_name() const override {
        return name;
    }
    */
  }
   

    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    // add card c to players hand
    // hand.Card c ?
    virtual void add_card(const Card &c){

    this->hand.push_back(c);
    /*virtual void add_card(const Card &c) override {
        // adding card to hand vector
        hand.push_back(c);
    } */

    }

    
    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    
    virtual bool make_trump(const Card &upcard, bool is_dealer,
                            int round, Suit &order_up_suit) const{

    int truthnum = 0;
    Suit upcardsuit = upcard.get_suit();
    Suit oppsuit = Suit_next(upcardsuit);

    if(round == 1){ //Round 1 parameters
      truthnum = 0;
      for(int cardnum = 0; cardnum < MAX_HAND_SIZE; ++cardnum){
        Card c = this->hand[cardnum];
        if((c.is_face_or_ace() == true) && (c.is_trump(upcardsuit) == true)){
          ++truthnum;
        }
      }
      if(truthnum >= 2){
        order_up_suit = upcardsuit;
        return true;
      } else{
        return false;
      }
    }else if((round == 2) &&( is_dealer == false)){ //Round 2 paramenters (Is not dealer)
      truthnum = 0;
      for(int cardnum = 0; cardnum < MAX_HAND_SIZE; ++cardnum){
        Card c = this->hand[cardnum];
        if((c.is_face_or_ace() == true) && (c.get_suit(oppsuit) == oppsuit)){
          ++truthnum;
        }
      }
        if(truthnum >= 1){
          order_up_suit = oppsuit;
          return true;
        } else{
          return false;
        }
    } else if((round == 2) && (is_dealer == true)){ //Round 2 parameters (Is the dealer)
      order_up_suit = oppsuit;
      return true;
    }
    return 0; //Only way for it to run, NEED TO FIX

    }
    

    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    virtual void add_and_discard(const Card &upcard){
      std::vector<Card> copy_hand = hand;
    // Card minbegin = upcard;
    Card truemin = upcard;
    int minum = 0;
    int discardupindicator = 0;
    Suit trump = upcard.get_suit();
    //Iterates through each card starting at 1 and determines the minimum
    for(int cardnum = 0; cardnum < MAX_HAND_SIZE; ++cardnum){ 
      if(Card_less(copy_hand[cardnum],truemin,trump) == true){ 
        truemin = copy_hand[cardnum];
        minum = cardnum;
        ++discardupindicator;
      }
    }
    if(discardupindicator > 0){
      this->hand[minum] = upcard; //Replaces minimum card with upcard
    }
    }
    

    virtual Card lead_card(Suit trump){
    int trumpcount = 0;
    Card chosencard;
    Card hightrump;
    Card nonhightrump;
    std::vector<Card> nonhightrumpset;
    std::vector<int> nonhightrumpsetognumspots;
    int currenthandsize = this->hand.size();

  //Iterates through hand and finds the # of trump cards and non-trump cards
    for(int cardnum = 0; cardnum < currenthandsize; ++cardnum){ 
      Card c = this->hand[cardnum];
      if(c.get_suit(trump) == trump){
        ++trumpcount;
      }
      if(c.get_suit(trump) != trump){
        nonhightrumpset.push_back(c);
        nonhightrumpsetognumspots.push_back(cardnum);
      }
    }

    int nhtsize = nonhightrumpset.size();
    int highnontrumpnum = 0;
    //If the hand is not all trump cards, they will iterate through 
    // and find the highest non-trump card
    if(nhtsize > 0){ 
      nonhightrump = nonhightrumpset[0];
      highnontrumpnum = nonhightrumpsetognumspots[0];
      for(int nhts = 0; nhts < nhtsize; ++nhts){
        if(Card_less(nonhightrump,nonhightrumpset[nhts],trump)){
          nonhightrump = nonhightrumpset[nhts];
          highnontrumpnum = nonhightrumpsetognumspots[nhts]; 
        }
     }
    }

    int hightrumpnum = 0;
    //If the hand is all trump cards, they will find and play the highest trump card
    if(trumpcount == currenthandsize){ 
      hightrump = this->hand[0];
      for(int cardnum = 0; cardnum < currenthandsize; ++cardnum){
        Card c = this->hand[cardnum];
        if(Card_less(hightrump,c,trump)){
          hightrump = c;
          hightrumpnum = cardnum; //Should be fine since all are in original vector
        }
      }
      chosencard = hightrump; //Playing the highest trump card
      this->hand.erase(this->hand.begin() + hightrumpnum); 
    }else{
      chosencard = nonhightrump; //Playing the highest non-trump card
      this->hand.erase(this->hand.begin() + highnontrumpnum); 
    }

    return chosencard; //Playing the chosen card from above
  
    }
    
    //REQUIRES Player has at least one card
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    
    virtual Card play_card(const Card &led_card, Suit trump){
    Suit ledsuit = led_card.get_suit(trump); 
    Card chosencard;
    Card lowestnonled;
    Card highled;
    int currenthandsize = this->hand.size();
    std::vector<Card> potentled;
    std::vector<int> potentledspot;

    //Checking if there is a led suit card
    for(int cardnum = 0; cardnum < currenthandsize; ++cardnum){
      Card c = this->hand[cardnum];
      if(c.get_suit(trump) == ledsuit){
        potentled.push_back(c);
        potentledspot.push_back(cardnum);
      }
    }

    int potentsize = potentled.size();
    int lowestnumloc = 0;
    if(potentsize == 0){ //If there is no led suit, play the lowest card in hand
      lowestnonled = this->hand[0];
      for(int cardnum = 0; cardnum < currenthandsize; ++cardnum){
        Card c = this->hand[cardnum];
        if(Card_less(c,lowestnonled,trump)){
          lowestnonled = c;
          lowestnumloc = cardnum;
        }
      }
    }

    int highlednum = 0;
    if(potentsize > 0){ //If there is a led suit, play the highest led suit card
      highled = potentled[0];
      highlednum = potentledspot[0];
      for(int cardnum = 0; cardnum < potentsize; ++cardnum){
        Card c = potentled[cardnum];
        if(Card_less(highled,c,trump)){
          highled = c;
          highlednum = potentledspot[cardnum];
        }
      }
      chosencard = highled; //Playing the highest led suit card
      this->hand.erase(this->hand.begin() + highlednum); 
    } else{
      chosencard = lowestnonled; //Playing the lowest non-suit card
      this->hand.erase(this->hand.begin() + lowestnumloc); 
    }

    return chosencard; //Playing the card mentioned above
  }
};





class HumanPlayer : public Player {


private:
    // variable for player name
    std::string name;
    // vector of Card for hands
    std::vector<Card> hand;
    
    std::string decision;
    //hand.erase(hand.begin() + i);
    //        std::string decision;
public:
    HumanPlayer(std::string name_of_player) : name(name_of_player) {}
    
    // EFFECTS returns Player's name:
    virtual const std::string& get_name() const override {
        return name;
    }
    
    void print_hand() const {
      for (int count = 5; count > 0; --count){
        for (size_t i=0; i < count; ++i)
            std::cout << "Human player " << name << "'s hand: "
            << "[" << i << "] " << hand[i] << "\n";
    }
    }
    
    virtual void add_card(const Card &c) override {
        // adding card to hand vector
        hand.push_back(c);
    }

    virtual bool make_trump(const Card &upcard, bool is_dealer,
                            int round, Suit &order_up_suit) const override{
    std::vector<Card> tempvector = this->hand;
    std::sort(tempvector.begin(), tempvector.end());
    int handsize = this->hand.size();
    for(int cardhand = 0; cardhand < handsize; ++cardhand){
      std::cout << "Human player " << this->get_name() << "'s hand: ";
      std::cout << "[" << cardhand << "] " << tempvector[cardhand] << "\n";
    }

    std::cout << "Human player " << this->get_name();
    std::cout << ", please enter a suit, or \"pass\":\n";
    std::string decision;
    
    
    while(std::cin >> decision) {
    if((decision == "Spades") || (decision == "Hearts") 
        || (decision == "Clubs") || (decision == "Diamonds")){
      order_up_suit = string_to_suit(decision);
      return true;
    } else if(decision == "pass"){
      return false;
    }
    }
    return 0;
  }


    virtual void add_and_discard(const Card &upcard) override {
        sort(hand.begin(), hand.end());
        int size = static_cast <int>(hand.size());
        //long line
        Suit us = upcard.get_suit();
        Card u = upcard;
        for (int i = 0; i < hand.size(); i++) {
          bool t = hand[i].is_trump(us);
          std::vector<Card>::const_iterator toe = hand.begin() + i;
            if (t) {
                add_card(u);
                for (int i = 0; i < size; ++i) {
                  hand.erase(toe);
                }
            }
        }
    }
    
    
    virtual Card lead_card(Suit trump) override {
        Card c;
        sort(hand.begin(), hand.end());
        //int size = static_cast <int>(hand.size());
        for (int i = 0; i  < hand.size(); i++) {
            if ( hand[i].get_suit() != trump) {
                 c = hand[i];
                 hand.end();
                 
            }
        }
        return c;
    }


    virtual Card play_card(const Card &led_card, Suit trump) override {
        // if you have same color as led card
        // bool right_bower = is_right_bower(trump);
        //  bool left_bower = is_left_bower(trump);
        Card c;
        for (int i = 0; i < hand.size(); i++){
            Suit ls = led_card.get_suit();
            Suit hs = hand[i].get_suit();
            bool lb = hand[i].is_left_bower(trump);
            bool rb= hand[i].is_right_bower(trump);
            if (ls == hs) {
                c = hand[i];
                hand.end();
            }
            else if (ls != hs) {
                c = hand[i];
                hand[i].is_trump(led_card.get_suit());
            }
            
            else if (led_card.get_suit() == trump) {
                c = hand[i];
                hand[i].is_right_bower(trump);
                
                // left and right bowers
            }
            else if (led_card.get_suit() == trump) {
                c = hand[i];
                hand[i].is_left_bower(trump);
            } // long line
            else if (!lb && !rb) {
                c = hand[i];
                hand.end();
            }
        }
        return c;
    }
    

};

Player * Player_factory(const std::string &name,
                        const std::string &strategy) {
  // We need to check the value of strategy and return
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  }
    if (strategy == "Human") {
        
        return new HumanPlayer(name);
    }
  // Repeat for each other type of Player
  // Invalid strategy if we get here
  return nullptr;
}

std::ostream& operator<<(std::ostream &os, const Player &p) {
    os << p.get_name();
    return os; 
}