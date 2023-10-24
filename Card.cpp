// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <array>
#include "Card.h"

using namespace std;

/////////////// Rank operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const RANK_NAMES[] = {
  "Two",   // TWO
  "Three", // THREE
  "Four",  // FOUR
  "Five",  // FIVE
  "Six",   // SIX
  "Seven", // SEVEN
  "Eight", // EIGHT
  "Nine",  // NINE
  "Ten",   // TEN
  "Jack",  // JACK
  "Queen", // QUEEN
  "King",  // KING
  "Ace"    // ACE
};

//REQUIRES str represents a valid rank ("Two", "Three", ..., "Ace")
Rank string_to_rank(const std::string &str) {
  for(int r = TWO; r <= ACE; ++r) {
    if (str == RANK_NAMES[r]) {
      return static_cast<Rank>(r);
    }
  }
  assert(false); // Input string didn't match any rank
}

//EFFECTS Prints Rank to stream, for example "Two"
std::ostream & operator<<(std::ostream &os, Rank rank) {
  os << RANK_NAMES[rank];
  return os;
}

//REQUIRES If any input is read, it must be a valid rank
//EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream & operator>>(std::istream &is, Rank &rank) {
  string str;
  if(is >> str) {
    rank = string_to_rank(str);
  }
  return is;
}


/////////////// Suit operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const SUIT_NAMES[] = {
  "Spades",   // SPADES
  "Hearts",   // HEARTS
  "Clubs",    // CLUBS
  "Diamonds", // DIAMONDS
};

//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
Suit string_to_suit(const std::string &str) {
  for(int s = 0; s <= 3; ++s) {
    if (str == SUIT_NAMES[s]) {
      return static_cast<Suit>(s);
    }
  }
  assert(false); // Input string didn't match any suit
  
}

//EFFECTS Prints Suit to stream, for example "Spades"
std::ostream & operator<<(std::ostream &os, Suit suit) {
  os << SUIT_NAMES[suit];
  return os;
}

//REQUIRES If any input is read, it must be a valid suit
//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream & operator>>(std::istream &is, Suit &suit) {
  string str;
  if (is >> str) {
    suit = string_to_suit(str);
  }
  return is;
}


/////////////// Write your implementation for Card below ///////////////

Card::Card() {
    rank = TWO;
    suit = SPADES;
    //rank represents the value
    //Suit represents the suit of card
}
Card::Card(Rank rank_in, Suit suit_in) {
    rank = rank_in;
    suit = suit_in;
}
Rank Card::get_rank() const{
    return(rank);
}


bool Card::is_face_or_ace() const{

    int J = JACK;
    int Q = QUEEN;
    int K = KING;
    int A = ACE;
    if (rank == J || rank == Q || rank == K ||  rank == A){return true;}
    else {return false;}
}


Suit Card::get_suit() const{
    return(suit); 
}


Suit Card::get_suit(Suit trump) const{
    // don't include trump card?
    
    // use is_left_bower(trump) to check if there is trump card
    // all other times return the suit of the card
    if (is_left_bower(trump)){
        return trump;
    }
    else {
        return suit; 
    }
}

bool Card::is_right_bower(Suit trump) const{
    // JACK - find where this is defined
    // JACK has enum value of 9
    // Returns true if the card is JACK of trump suit
    // Check this condition - that TRUMP == JACK
    return (rank == JACK && suit == trump);
}

bool Card::is_left_bower(Suit trump) const{
    // for each case where trump is a different suit
    // the rank is JACK and suit is the next suit then return true
    // follow order of suits in spec: Spades, Clubs, Hearts, Diamonds?
    if (trump == SPADES && rank == JACK && suit == CLUBS){
        return true;
    }
    else if (trump == CLUBS && rank == JACK && suit == SPADES) {
        return true;
    }
    else if (trump == HEARTS && rank == JACK && suit == DIAMONDS){
        return true;
        
    }
    else if (trump == DIAMONDS && rank == JACK && suit == HEARTS) {
        return true;
    }
    else {
        return false;
    }
}

bool Card::is_trump(Suit trump) const{
    // call get_suit to check trump is trump
    if (trump == get_suit(trump)){
        return true;
    }
    // left_bower is also trump card:
    else if(is_left_bower(trump) == true){
        return true;
    }
    else {
        return false;
    }
}

bool Card_less(const Card &a, const Card&b, Suit trump){
        if((b.get_suit(trump) == trump) && (a.get_suit(trump) != trump)){
        if((b.is_right_bower(trump) == false) && (a.is_left_bower(trump) == true)){
            return false;
        }else{
            return true;
        }
    } else if((b.get_suit(trump) != trump) && (a.get_suit(trump) == trump)){
        if((b.is_left_bower(trump) == true) && (a.is_right_bower(trump) == false)){
            return true;
        } else{
            return false;
        }
    }else if((b.get_suit(trump) != trump) && (a.get_suit(trump) != trump)){  
        if((b.is_left_bower(trump) == true)){
            return true;
        } else if(a.is_left_bower(trump) == true){
            return false;
        } else{
            return (operator<(a,b));
        }
    }else if((b.get_suit(trump) == trump) && (a.get_suit(trump) == trump)){
        if(b.is_right_bower(trump) == true){
            return true;
        }else if((b.is_left_bower(trump) == true) && (a.is_right_bower(trump) != true)){
            return true;
        }else if(a.is_right_bower(trump) == true){
            return false;
        } else if((a.is_left_bower(trump) == true) && (b.is_right_bower(trump) != true)){
            return false;
        }else{
            return (operator<(a,b));
        }
    } else{
        return false;
    }
}

bool Card_less(const Card &a, const Card &b, const Card &led_card, Suit trump){
    Suit ledsuit = led_card.get_suit();
    if((b.get_suit(trump) != trump) && (a.get_suit(trump) != trump)){
        if((b.get_suit(trump) == ledsuit) && (a.get_suit(trump) != ledsuit)){
            return true;
        } else if((b.get_suit(trump) != ledsuit) && (a.get_suit(trump) == ledsuit)){
            return false;
        } else{
            return operator<(a,b);
        }
    } else{
        return Card_less(a,b,trump);
    }
}


Suit Suit_next(Suit suit){
  
    
    if(suit == 0 ){ // maybe try actual suit name in if condition
        return CLUBS;
        
    }
    else if(suit == 2){
        return SPADES;
        
    }
    else if(suit == 1){
        return DIAMONDS;
        
    }
    else if(suit == 3){
        return HEARTS;
        
    }
      return SPADES;
  }

std::ostream & operator<<(std::ostream &os, const Card &card) {
    // print Card number (rank)  of Card Suit
    os << card.get_rank() << " of " << card.get_suit();
    
    return os;
}

std::istream & operator>>(std::istream &is, Card &card){
//    Rank r = card.get_rank();
//    Suit s = card.get_suit();
    
    string junk;
    Rank r;
    Suit s;
    
    is >> r >> junk >> s;
    
    card.rank = r;
    card.suit = s;
    
    
    //is >> r >> " of " >> card.get_suit();
    
    return is;
     
}

bool operator<(const Card &lhs, const Card &rhs) {
    return (!operator>=(lhs,rhs));
}

bool operator<=(const Card &lhs, const Card &rhs) {
    return (!operator>(lhs, rhs));
}

bool operator>(const Card &lhs, const Card &rhs) {

    int lhs_rank =  lhs.get_rank();
    int lhs_suit = lhs.get_suit();
    int rhs_rank = rhs.get_rank();
    int rhs_suit = rhs.get_suit();
    

    if (lhs_rank > rhs_rank){return true;}
    else if (lhs_rank == rhs_rank){
        if (lhs_suit > rhs_suit){return true;}
        else {return false;}
    }
    else return false;


}


bool operator>=(const Card &lhs, const Card &rhs) {
    return ((operator>(lhs,rhs)) || (operator==(lhs,rhs)));

}


bool operator==(const Card &lhs, const Card &rhs) {
    int lhs_rank =  lhs.get_rank();
    int lhs_suit = lhs.get_suit();
    int rhs_rank = rhs.get_rank();
    int rhs_suit = rhs.get_suit();
    
    if(lhs_rank == rhs_rank){
        if(lhs_suit == rhs_suit){
            return true;
        }
        else{return false;}
    }

   else{return false;}

}

bool operator!=(const Card &lhs, const Card &rhs) {
    int lhs_rank =  lhs.get_rank();
    int lhs_suit = lhs.get_suit();
    int rhs_rank = rhs.get_rank();
    int rhs_suit = rhs.get_suit();
    
    if(lhs_suit != rhs_suit){
        if(lhs_rank != rhs_rank){
            return true;
        }
    }
    // if suits are diffeerent but rank is the same
    else if(lhs_suit != rhs_suit){
        if(lhs_rank == rhs_rank){
            return true;
        }
        
    }
    else if(lhs_suit == rhs_suit){
        if(lhs_rank == rhs_rank){
            return false; 
        }
    }
    return("bruh");
}

// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator>>
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=
