// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
// #include "Pack.h"
#include "Card.h"
#include "unit_test_framework.h"


#include <iostream>

using namespace std;
Card nine_spades = Card(NINE, SPADES);
Card ten_spades = Card(TEN, SPADES);
Card jack_spades = Card(JACK, SPADES);
Card queen_spades = Card(QUEEN, SPADES);
Card king_spades = Card(KING, SPADES);
Card ace_spades = Card(ACE, SPADES);

Card nine_club = Card(NINE, CLUBS);
Card ten_club = Card(TEN, CLUBS);
Card jack_club = Card(JACK, CLUBS);
Card queen_club = Card(QUEEN, CLUBS);
Card king_club = Card(KING, CLUBS);
Card ace_club = Card(ACE, CLUBS);

Card nine_heart = Card(NINE, HEARTS);
Card ten_heart = Card(TEN, HEARTS);
Card jack_heart = Card(JACK, HEARTS);
Card queen_heart = Card(QUEEN, HEARTS);
Card king_heart = Card(KING, HEARTS);
Card ace_heart = Card(ACE, HEARTS);

Card nine_diamond = Card(NINE, DIAMONDS);
Card ten_diamonds = Card(TEN, DIAMONDS);
Card jack_diamond = Card(JACK, DIAMONDS);
Card queen_diamond = Card(QUEEN, DIAMONDS);
Card king_diamond = Card(KING, DIAMONDS);
Card ace_diamond = Card(ACE, DIAMONDS);



TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_player_name_human) {
    Player * alex = Player_factory("Alex", "Human");
    ASSERT_EQUAL("Alex", alex->get_name());

    delete alex;
}

TEST(trump) {
    
    Player * Jake = Player_factory("Jake", "Simple");

    Jake->add_card(queen_spades);
    Jake->add_card(jack_spades);
    Jake->add_card(jack_club);
    Jake->add_card(ten_club);
    Jake->add_card(ace_heart);

/*
    Card trump1(KING, SPADES);
    Suit trump = undefined;
    //ASSERT_TRUE(Jake ->make_trump(nine_spades, true 1, trump1))
    Suit s = trump1.get_suit();
    bool orderup = Jake->make_trump(trump1, true, 1, s);
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, "undefined");
  */

    Card trump2(KING, DIAMONDS);
    Suit v = trump2.get_suit();
    bool orderup1 = Jake->make_trump(trump2, true, 1, v);
    ASSERT_FALSE(orderup1);
    // ASSERT_EQUAL(trump, "undefined");

    Card trump3(KING, DIAMONDS);

    Suit r = trump3.get_suit();
    bool orderup3 = Jake->make_trump(trump3, true, 1, r);
    ASSERT_FALSE(orderup3);
   // ASSERT_EQUAL(trump, "undefined");

    delete Jake;

}

//TEST(test_simple_add_discard) {
//    Player * Mike = Player_factory("Mike", "Simple");
//    
//    Mike->add_card(nine_club);
//    Mike->add_card(nine_club);
//    Mike->add_card(nine_club);
//    Mike->add_card(nine_club);
//    Mike->add_card(nine_club);
//    Mike->add_and_discard(queen_club);
//    Card test = Mike->lead_card(CLUBS);
//    ASSERT_EQUAL(test, queen_club);
//    
//    delete Mike;
//    
//}
// Add more tests here



TEST(test_name_of_multiple_players){ //Testing the grabbing of multiple names
  Player * James = Player_factory("James", "Simple");
  Player * Hannah = Player_factory("Hannah", "Simple");
  Player * Brennen = Player_factory("Brennen", "Human");
  Player * Amanda = Player_factory("Amanda", "Human");

  ASSERT_EQUAL(James->get_name(), "James");
  ASSERT_EQUAL(Hannah->get_name(), "Hannah");
  ASSERT_EQUAL(Brennen->get_name(), "Brennen");
  ASSERT_EQUAL(Amanda->get_name(), "Amanda");

  ostringstream os1;
  os1 << *James;
  ASSERT_EQUAL(os1.str(), "James");
  
  ostringstream os2;
  os2 << *Hannah;
  ASSERT_EQUAL(os2.str(), "Hannah");

  ostringstream os3;
  os3 << *Brennen;
  ASSERT_EQUAL(os3.str(), "Brennen");

  ostringstream os4;
  os4 << *Amanda;
  ASSERT_EQUAL(os4.str(), "Amanda");

  delete James;
  delete Hannah;
  delete Brennen;
  delete Amanda;
}

//End of testing name

//Testing make_trump
TEST(round1_make_trump){ //Testing round 1, not dealer, no jacks, 3 of same suit
  Player * Jordan = Player_factory("Jordan","Simple");

  Card upcard(ACE, CLUBS);
  Suit trump;

  Jordan->add_card(Card(ACE,CLUBS));
  Jordan->add_card(Card(KING,CLUBS));
  Jordan->add_card(Card(QUEEN,CLUBS));
  Jordan->add_card(Card(TEN,DIAMONDS));
  Jordan->add_card(Card(NINE,DIAMONDS));

  bool orderup = Jordan->make_trump(upcard,false,1,trump);

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump,CLUBS);

  delete Jordan;
}

TEST(round1_make_trump_advance){ //Testing round 1, not dealer, no jacks, 2 of same suit
  Player * Jordan = Player_factory("Jordan","Simple");

  Card upcard(ACE, CLUBS);
  Suit trump;

  Jordan->add_card(Card(ACE,CLUBS));
  Jordan->add_card(Card(KING,CLUBS));
  Jordan->add_card(Card(TEN,HEARTS));
  Jordan->add_card(Card(TEN,DIAMONDS));
  Jordan->add_card(Card(NINE,DIAMONDS));

  bool orderup = Jordan->make_trump(upcard,false,1,trump);

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump,CLUBS);

  delete Jordan;
}

TEST(round1_make_trump_advance_isdealer_false){ //Testing round 1, not dealer, no jacks, 2 of same suit
  Player * Jordan = Player_factory("Jordan","Simple");

  Card upcard(ACE, CLUBS);
  Suit trump;

  Jordan->add_card(Card(ACE,CLUBS));
  Jordan->add_card(Card(NINE,CLUBS));
  Jordan->add_card(Card(TEN,HEARTS));
  Jordan->add_card(Card(TEN,DIAMONDS));
  Jordan->add_card(Card(NINE,DIAMONDS));

  bool orderup = Jordan->make_trump(upcard,true,1,trump);

  ASSERT_FALSE(orderup);

  delete Jordan;
}

TEST(round1_make_trump_advance_isdealer_true){
  Player * Jordan = Player_factory("Jordan","Simple");

  Card upcard(ACE, CLUBS);
  Suit trump;

  Jordan->add_card(Card(ACE,CLUBS));
  Jordan->add_card(Card(KING,CLUBS));
  Jordan->add_card(Card(TEN,HEARTS));
  Jordan->add_card(Card(TEN,DIAMONDS));
  Jordan->add_card(Card(NINE,DIAMONDS));

  bool orderup = Jordan->make_trump(upcard,true,1,trump);

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump,CLUBS);

  delete Jordan;
}

TEST(round1_make_trump_advancer){ //Testing round 1, no jacks, not dealer, only 1 facecard
  Player * Jordan = Player_factory("Jordan","Simple");

  Card upcard(ACE, CLUBS);
  Suit trump;

  Jordan->add_card(Card(ACE,CLUBS));
  Jordan->add_card(Card(TEN,CLUBS));
  Jordan->add_card(Card(KING,HEARTS));
  Jordan->add_card(Card(TEN,DIAMONDS));
  Jordan->add_card(Card(NINE,DIAMONDS));

  bool orderup = Jordan->make_trump(upcard,false,1,trump);

  ASSERT_FALSE(orderup);

  delete Jordan;
}

TEST(round1_make_trump_advance_with_leftbower){ //Testing round 1, leftbower jack, not dealer
  Player * Jordan = Player_factory("Jordan","Simple");

  Card upcard(ACE, CLUBS);
  Suit trump;

  Jordan->add_card(Card(ACE,CLUBS));
  Jordan->add_card(Card(JACK,SPADES));
  Jordan->add_card(Card(TEN,HEARTS));
  Jordan->add_card(Card(TEN,DIAMONDS));
  Jordan->add_card(Card(NINE,DIAMONDS));

  bool orderup = Jordan->make_trump(upcard,false,1,trump);

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump,CLUBS);

  delete Jordan;
}

TEST(round1_make_trump_advance_beyond){ //Testing round 1, both Jacks present, not dealer
  Player * Jordan = Player_factory("Jordan","Simple");

  Card upcard(ACE, CLUBS);
  Suit trump;

  Jordan->add_card(Card(JACK,CLUBS));
  Jordan->add_card(Card(JACK,SPADES));
  Jordan->add_card(Card(TEN,HEARTS));
  Jordan->add_card(Card(TEN,DIAMONDS));
  Jordan->add_card(Card(NINE,DIAMONDS));

  bool orderup = Jordan->make_trump(upcard,false,1,trump);

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump,CLUBS);

  delete Jordan;
}

TEST(round2_make_trump){ //Testing round 2, 2 face cards of opposite upcard suit present
  Player * Jordan = Player_factory("Jordan","Simple");

  Card upcard(ACE, CLUBS);
  Suit trump;

  Jordan->add_card(Card(ACE,SPADES));
  Jordan->add_card(Card(KING,SPADES));
  Jordan->add_card(Card(TEN,HEARTS));
  Jordan->add_card(Card(TEN,DIAMONDS));
  Jordan->add_card(Card(NINE,DIAMONDS));

  bool orderup = Jordan->make_trump(upcard,false,2,trump);

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump,SPADES);

  delete Jordan;
}

TEST(round2_make_trump_advance){ //Testing round 2, 1 face card of opposite upcard suite present
  Player * Jordan = Player_factory("Jordan","Simple");

  Card upcard(ACE, CLUBS);
  Suit trump;

  Jordan->add_card(Card(ACE,SPADES));
  Jordan->add_card(Card(KING,HEARTS));
  Jordan->add_card(Card(TEN,HEARTS));
  Jordan->add_card(Card(TEN,DIAMONDS));
  Jordan->add_card(Card(NINE,DIAMONDS));

  bool orderup = Jordan->make_trump(upcard,false,2,trump);

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump,SPADES);

  delete Jordan;
}

TEST(round2_make_trump_false){ //Testing round 2, no cards of opposite suit present
  Player * Jordan = Player_factory("Jordan","Simple");

  Card upcard(ACE, CLUBS);
  Suit trump;

  Jordan->add_card(Card(ACE,HEARTS));
  Jordan->add_card(Card(KING,HEARTS));
  Jordan->add_card(Card(TEN,HEARTS));
  Jordan->add_card(Card(TEN,DIAMONDS));
  Jordan->add_card(Card(NINE,DIAMONDS));

  bool orderup = Jordan->make_trump(upcard,false,2,trump);

  ASSERT_FALSE(orderup);

  delete Jordan;
}

TEST(round2_make_trump_false2){ //Testing round 2, no cards of opposite suit but 2 face cards of upcard suit present
  Player * Jordan = Player_factory("Jordan","Simple");

  Card upcard(ACE, CLUBS);
  Suit trump;

  Jordan->add_card(Card(ACE,CLUBS));
  Jordan->add_card(Card(KING,CLUBS));
  Jordan->add_card(Card(TEN,HEARTS));
  Jordan->add_card(Card(TEN,DIAMONDS));
  Jordan->add_card(Card(NINE,DIAMONDS));

  bool orderup = Jordan->make_trump(upcard,false,2,trump);

  ASSERT_FALSE(orderup);

  delete Jordan;
}

TEST(round2_make_trump_false3){ //Testing round 2, no cards of opposite suit, EXTREMELY BASIC FUNCTION WHY IS THIS HERE
  Player * Jordan = Player_factory("Jordan","Simple");

  Card upcard(ACE, CLUBS);
  Suit trump;

  Jordan->add_card(Card(ACE,HEARTS));
  Jordan->add_card(Card(KING,HEARTS));
  Jordan->add_card(Card(TEN,HEARTS));
  Jordan->add_card(Card(TEN,DIAMONDS));
  Jordan->add_card(Card(NINE,DIAMONDS));

  bool orderup = Jordan->make_trump(upcard,false,2,trump);

  ASSERT_FALSE(orderup);

  delete Jordan;
}

//BE WARY OF THIS, DOESN'T MAKE SENSE
TEST(round2_make_trump_leftbower){ //Testing round 2, no cards of opposite suit but left bower of potential suit
  Player * Jordan = Player_factory("Jordan","Simple");

  Card upcard(ACE, CLUBS);
  Suit trump;

  Jordan->add_card(Card(ACE,HEARTS));
  Jordan->add_card(Card(JACK,SPADES));
  Jordan->add_card(Card(TEN,HEARTS));
  Jordan->add_card(Card(TEN,DIAMONDS));
  Jordan->add_card(Card(NINE,DIAMONDS));

  bool orderup = Jordan->make_trump(upcard,false,2,trump);

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump,SPADES); //Sus

  delete Jordan;
}

//BE WARY OF THIS, ALMOST DEFINITELY DOESN'T MAKE SENSE
TEST(round2_make_trump_rightbower){ //Testing round 2, no cards of opposite suit but right bower of potential suit
  Player * Jordan = Player_factory("Jordan","Simple");

  Card upcard(ACE, SPADES);
  Suit trump;

  Jordan->add_card(Card(ACE,HEARTS));
  Jordan->add_card(Card(JACK,SPADES));
  Jordan->add_card(Card(TEN,HEARTS));
  Jordan->add_card(Card(TEN,DIAMONDS));
  Jordan->add_card(Card(NINE,DIAMONDS));

  bool orderup = Jordan->make_trump(upcard,false,2,trump);

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump,CLUBS);

  delete Jordan;
}

TEST(round2_make_trump_dealermust){ //Testing round 2, lands on dealer, must pick up regardless
  Player * Jordan = Player_factory("Jordan","Simple");

  Card upcard(ACE, CLUBS);
  Suit trump;

  Jordan->add_card(Card(ACE,HEARTS));
  Jordan->add_card(Card(JACK,HEARTS));
  Jordan->add_card(Card(TEN,HEARTS));
  Jordan->add_card(Card(TEN,DIAMONDS));
  Jordan->add_card(Card(NINE,DIAMONDS));

  bool orderup = Jordan->make_trump(upcard,true,2,trump);

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump,SPADES);

  delete Jordan;
}

TEST(round2_make_trump_dealermust_test2){ //Testing round 2, lands on dealer, must pick up regardless
  Player * Jordan = Player_factory("Jordan","Simple");

  Card upcard(ACE, CLUBS);
  Suit trump;

  Jordan->add_card(Card(QUEEN,CLUBS));
  Jordan->add_card(Card(JACK,HEARTS));
  Jordan->add_card(Card(TEN,HEARTS));
  Jordan->add_card(Card(KING,CLUBS));
  Jordan->add_card(Card(QUEEN,CLUBS));

  bool orderup = Jordan->make_trump(upcard,true,2,trump);

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump,SPADES);

  delete Jordan;
}

TEST(round2_make_trump_dealermust_test3){ //Testing round 2, lands on dealer, must pick up regardless
  Player * Jordan = Player_factory("Jordan","Simple");

  Card upcard(NINE,CLUBS);
  Suit trump;

  Jordan->add_card(Card(QUEEN,CLUBS));
  Jordan->add_card(Card(JACK,HEARTS));
  Jordan->add_card(Card(TEN,HEARTS));
  Jordan->add_card(Card(KING,CLUBS));
  Jordan->add_card(Card(QUEEN,SPADES));

  bool orderup = Jordan->make_trump(upcard,true,2,trump);

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump,SPADES);

  delete Jordan;
}

//End of make_trump

//Testing Lead Card
TEST(add_and_discard_test){ //Testing partial trump, partial not
  Player * Jordan = Player_factory("Jordan","Simple");

  Card upcard(QUEEN, HEARTS);

  Jordan->add_card(Card(ACE,HEARTS));
  Jordan->add_card(Card(JACK,HEARTS));
  Jordan->add_card(Card(TEN,HEARTS));
  Jordan->add_card(Card(ACE,DIAMONDS));
  Jordan->add_card(Card(NINE,DIAMONDS));

  Jordan->add_and_discard(upcard);

  Card card_led = Jordan->lead_card(HEARTS);

  Card ace_diamond(ACE, DIAMONDS);
  ASSERT_EQUAL(card_led,ace_diamond);

  delete Jordan;
}

TEST(add_and_discard_test_withties){ //Testing lead card with ties present
  Player * Jordan = Player_factory("Jordan","Simple");

  Jordan->add_card(Card(NINE,HEARTS));
  Jordan->add_card(Card(NINE,SPADES));
  Jordan->add_card(Card(NINE,CLUBS));
  Jordan->add_card(Card(NINE,DIAMONDS));
  Jordan->add_card(Card(TEN,HEARTS));

  Card card_led = Jordan->lead_card(HEARTS);

  Card ace_diamond(NINE, DIAMONDS);
  ASSERT_EQUAL(card_led,ace_diamond);

  delete Jordan;
}

TEST(add_and_discard_test_notrumps){ //Testing lead card if no trumps are available
  Player * Jordan = Player_factory("Jordan","Simple");

  Jordan->add_card(Card(ACE,SPADES));
  Jordan->add_card(Card(JACK,CLUBS));
  Jordan->add_card(Card(TEN,CLUBS));
  Jordan->add_card(Card(KING,SPADES));
  Jordan->add_card(Card(NINE,SPADES));

  Card card_led = Jordan->lead_card(HEARTS);

  Card ace_spades(ACE, SPADES);
  ASSERT_EQUAL(card_led,ace_spades);

  delete Jordan;
}

TEST(add_and_discard_test_alltrumps){ //Testing lead card if all cards are trump
  Player * Jordan = Player_factory("Jordan","Simple");

  Jordan->add_card(Card(ACE,DIAMONDS));
  Jordan->add_card(Card(JACK,DIAMONDS));
  Jordan->add_card(Card(TEN,DIAMONDS));
  Jordan->add_card(Card(KING,DIAMONDS));
  Jordan->add_card(Card(NINE,DIAMONDS));

  Card card_led = Jordan->lead_card(DIAMONDS);

  Card jack_diamonds(JACK, DIAMONDS);
  ASSERT_EQUAL(card_led,jack_diamonds);

  delete Jordan;
}

TEST(add_and_discard_test_alltrumps_leftbower){ //Testing lead card if left bower is present / all cards are trump
  Player * Jordan = Player_factory("Jordan","Simple");

  Jordan->add_card(Card(ACE,DIAMONDS));
  Jordan->add_card(Card(JACK,HEARTS));
  Jordan->add_card(Card(TEN,DIAMONDS));
  Jordan->add_card(Card(KING,DIAMONDS));
  Jordan->add_card(Card(NINE,DIAMONDS));

  Card card_led = Jordan->lead_card(DIAMONDS);

  Card jack_hearts(JACK, HEARTS);
  ASSERT_EQUAL(card_led,jack_hearts);

  delete Jordan;
}

TEST(add_and_discard_test_notrumps_butleftbower){ //Testing lead card no trump but left bower
  Player * Jordan = Player_factory("Jordan","Simple");

  Jordan->add_card(Card(ACE,SPADES));
  Jordan->add_card(Card(JACK,DIAMONDS));
  Jordan->add_card(Card(TEN,CLUBS));
  Jordan->add_card(Card(KING,SPADES));
  Jordan->add_card(Card(NINE,SPADES));

  Card card_led = Jordan->lead_card(HEARTS);

  Card ace_spades(ACE, SPADES);
  ASSERT_EQUAL(card_led,ace_spades);

  delete Jordan;
}

TEST(add_and_discard_test_fourtrumps_andonenontrump){ //Testing four trumps and one non-trump
  Player * Jordan = Player_factory("Jordan","Simple");

  Jordan->add_card(Card(ACE,HEARTS));
  Jordan->add_card(Card(KING,DIAMONDS));
  Jordan->add_card(Card(TEN,HEARTS));
  Jordan->add_card(Card(KING,HEARTS));
  Jordan->add_card(Card(NINE,HEARTS));

  Card card_led = Jordan->lead_card(HEARTS);

  Card ace_spades(KING, DIAMONDS);
  ASSERT_EQUAL(card_led,ace_spades);

  delete Jordan;
}

TEST(add_and_discard_test_alltrumps_withleftandrightbower){ //Testing lead card if all cards are trump
  Player * Jordan = Player_factory("Jordan","Simple");

  Jordan->add_card(Card(ACE,DIAMONDS));
  Jordan->add_card(Card(JACK,DIAMONDS));
  Jordan->add_card(Card(TEN,DIAMONDS));
  Jordan->add_card(Card(KING,DIAMONDS));
  Jordan->add_card(Card(JACK,HEARTS));

  Card card_led = Jordan->lead_card(DIAMONDS);

  Card jack_diamonds(JACK, DIAMONDS);
  ASSERT_EQUAL(card_led,jack_diamonds);

  delete Jordan;
}

//End of testing lead card

//Testing play card

TEST(test_play_card_simple){
  Player * Jordan = Player_factory("Jordan","Simple");

  Card led_card(ACE, DIAMONDS);
  Suit trump = SPADES;

  Jordan->add_card(Card(ACE,HEARTS));
  Jordan->add_card(Card(JACK,HEARTS));
  Jordan->add_card(Card(TEN,HEARTS));
  Jordan->add_card(Card(KING,DIAMONDS));
  Jordan->add_card(Card(NINE,DIAMONDS));

  Card card_played = Jordan->play_card(led_card,trump);

  ASSERT_EQUAL(card_played, Card(KING, DIAMONDS));

  delete Jordan;
}

TEST(test_play_card_simple_lowest_noledsuit){
  Player * Jordan = Player_factory("Jordan","Simple");

  Card led_card(ACE, DIAMONDS);
  Suit trump = SPADES;

  Jordan->add_card(Card(ACE,HEARTS));
  Jordan->add_card(Card(JACK,HEARTS));
  Jordan->add_card(Card(TEN,HEARTS));
  Jordan->add_card(Card(KING,CLUBS));
  Jordan->add_card(Card(NINE,SPADES));

  Card card_played = Jordan->play_card(led_card,trump);

  ASSERT_EQUAL(card_played, Card(TEN, HEARTS));

  delete Jordan;
}

TEST(test_play_card_simple_highest_alltrump){
  Player * Jordan = Player_factory("Jordan","Simple");

  Card led_card(QUEEN, DIAMONDS);
  Suit trump = SPADES;

  Jordan->add_card(Card(ACE,DIAMONDS));
  Jordan->add_card(Card(JACK,DIAMONDS));
  Jordan->add_card(Card(TEN,DIAMONDS));
  Jordan->add_card(Card(KING,DIAMONDS));
  Jordan->add_card(Card(NINE,DIAMONDS));

  Card card_played = Jordan->play_card(led_card,trump);

  ASSERT_EQUAL(card_played, Card(ACE, DIAMONDS));

  delete Jordan;
}

TEST(test_play_card_simple_withjack){
  Player * Jordan = Player_factory("Jordan","Simple");

  Card led_card(ACE, DIAMONDS);
  Suit trump = DIAMONDS;

  Jordan->add_card(Card(ACE,HEARTS));
  Jordan->add_card(Card(JACK,HEARTS));
  Jordan->add_card(Card(TEN,HEARTS));
  Jordan->add_card(Card(KING,CLUBS));
  Jordan->add_card(Card(NINE,CLUBS));

  Card card_played = Jordan->play_card(led_card,trump);

  ASSERT_EQUAL(card_played, Card(JACK, HEARTS));

  delete Jordan;
}

TEST(test_play_card_simple_withjackbothleftandrightbow){
  Player * Jordan = Player_factory("Jordan","Simple");

  Card led_card(ACE, DIAMONDS);
  Suit trump = DIAMONDS;

  Jordan->add_card(Card(ACE,HEARTS));
  Jordan->add_card(Card(JACK,HEARTS));
  Jordan->add_card(Card(JACK,DIAMONDS));
  Jordan->add_card(Card(KING,CLUBS));
  Jordan->add_card(Card(NINE,CLUBS));

  Card card_played = Jordan->play_card(led_card,trump);

  ASSERT_EQUAL(card_played, Card(JACK, DIAMONDS));

  delete Jordan;
}

TEST(test_play_card_simple_withjackduo){
  Player * Jordan = Player_factory("Jordan","Simple");

  Card led_card(ACE, HEARTS);
  Suit trump = DIAMONDS;

  Jordan->add_card(Card(ACE,CLUBS));
  Jordan->add_card(Card(JACK,DIAMONDS)); //Right Bower
  Jordan->add_card(Card(TEN,HEARTS));
  Jordan->add_card(Card(JACK,HEARTS)); //Left Bower, wouldn't this count also as a jack of diamonds?
  Jordan->add_card(Card(NINE,CLUBS));

  Card card_played = Jordan->play_card(led_card,trump);

  ASSERT_EQUAL(card_played, Card(TEN, HEARTS));

  delete Jordan;
}

TEST(test_play_card_simple_withjackproblem){
  Player * Jordan = Player_factory("Jordan","Simple");

  Card led_card(ACE, HEARTS);
  Suit trump = HEARTS;

  Jordan->add_card(Card(ACE,CLUBS));
  Jordan->add_card(Card(JACK,DIAMONDS)); //Left Bower
  Jordan->add_card(Card(TEN,HEARTS));
  Jordan->add_card(Card(ACE,HEARTS)); 
  Jordan->add_card(Card(NINE,CLUBS));

  Card card_played = Jordan->play_card(led_card,trump);

  ASSERT_EQUAL(card_played, Card(JACK, DIAMONDS));

  delete Jordan;
}

//End of testing play card

//Beginning of stuff from public test

TEST(test_simple_player_play_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob plays a card
  Card nine_diamonds(NINE, DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    HEARTS        // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(NINE, SPADES));
  delete bob;
}

TEST(test_simple_player_lead_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(NINE, HEARTS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(HEARTS);

  // Verify the card Bob selected to lead
  Card ace_spades(ACE, SPADES);
  ASSERT_EQUAL(card_led, ace_spades); //check led card

  delete bob;
}

TEST(test_simple_player_make_trump) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob makes tump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, SPADES);

  delete bob;
}

TEST(test_player_insertion) {
  // Create a Human player
  Player * human = Player_factory("NotRobot", "Human");

  // Print the player using the stream insertion operator
  ostringstream oss1;
  oss1 << * human;

  // Verify that the output is the player's name
  ASSERT_EQUAL(oss1.str(), "NotRobot");

  // Create a Simple player
  Player * alice = Player_factory("Alice", "Simple");

  // Print the player using the stream insertion operator
  ostringstream oss2;
  oss2 << *alice;
  ASSERT_EQUAL(oss2.str(), "Alice");

  // Clean up players that were created using Player_factory()
  delete human;
  delete alice;
}

//End of stuff from public tests

//Testing add card
TEST(test_add_card){ //Testing 1 card and making sure that it is the lead card
  Player * Jordan = Player_factory("Jordan", "Simple");
  Jordan->add_card(Card(ACE,HEARTS));
  Suit trump = SPADES;

  ASSERT_EQUAL(Jordan->lead_card(trump),Card(ACE,HEARTS));

  delete Jordan;
}

TEST(test_add_card_multiple_added){
  Player * Jordan = Player_factory("Jordan","Simple");
  Jordan->add_card(Card(QUEEN,DIAMONDS));
  Jordan->add_card(Card(JACK,HEARTS));

  Suit trump = DIAMONDS;
  Card ledcard(JACK,HEARTS);

  ASSERT_EQUAL(Jordan->lead_card(trump),Card(JACK,HEARTS));
  ASSERT_EQUAL(Jordan->play_card(ledcard,trump),Card(QUEEN,DIAMONDS));

  delete Jordan;
}

//End of testing add card

//Testing add and discard

TEST(test_add_and_discard_testerer){
  Player * Jordan = Player_factory("Jordan","Simple");
  Jordan->add_card(Card(NINE,CLUBS));
  Jordan->add_card(Card(TEN,CLUBS));
  Jordan->add_card(Card(QUEEN,DIAMONDS));
  Jordan->add_card(Card(QUEEN,HEARTS));
  Jordan->add_card(Card(NINE,SPADES));

  Card upcard(ACE,CLUBS);
  Card trueleadcard(QUEEN,DIAMONDS);

  Suit trump = CLUBS;
  Jordan->add_and_discard(upcard); //Should remove nine of spades and replace with ace of clubs

  ASSERT_EQUAL(Jordan->lead_card(CLUBS),trueleadcard); //Lead with Queen of diamonds, our largest non-trump suit
  ASSERT_EQUAL(Jordan->play_card(trueleadcard,trump),Card(QUEEN,HEARTS)); //Since the nine, ten, and ace are of the trump suit ,clubs, queen of hearts is the lowest
  ASSERT_EQUAL(Jordan->play_card(trueleadcard,trump),Card(NINE,CLUBS)); //Play the lowest of the trump suit
  ASSERT_EQUAL(Jordan->play_card(trueleadcard,trump),Card(TEN,CLUBS)); //Play the next lowest
  ASSERT_EQUAL(Jordan->play_card(trueleadcard,trump),Card(ACE,CLUBS)); //Play the remaining card, AKA the card we picked up

  delete Jordan;
}

TEST(test_add_and_discard_withleftbower){
  Player * Jordan = Player_factory("Jordan","Simple");
  Jordan->add_card(Card(JACK,DIAMONDS));
  Jordan->add_card(Card(ACE,DIAMONDS));
  Jordan->add_card(Card(KING,DIAMONDS));
  Jordan->add_card(Card(QUEEN,DIAMONDS));
  Jordan->add_card(Card(JACK,HEARTS));

  Card upcard(NINE,DIAMONDS);
  Card trueleadcard(JACK,DIAMONDS);
  Suit trump = DIAMONDS;

  Jordan->add_and_discard(upcard);

  ASSERT_EQUAL(Jordan->lead_card(DIAMONDS),trueleadcard);
  ASSERT_EQUAL(Jordan->play_card(trueleadcard,trump),Card(JACK,HEARTS));
  ASSERT_EQUAL(Jordan->play_card(trueleadcard,trump),Card(ACE,DIAMONDS));
  ASSERT_EQUAL(Jordan->play_card(trueleadcard,trump),Card(KING,DIAMONDS));
  ASSERT_EQUAL(Jordan->play_card(trueleadcard,trump),Card(QUEEN,DIAMONDS));


  delete Jordan;
}

TEST(test_add_and_discard_difficultdeck){
  Player * Jordan = Player_factory("Jordan","Simple");

  Jordan->add_card(Card(JACK,DIAMONDS));
  Jordan->add_card(Card(KING,CLUBS));
  Jordan->add_card(Card(TEN,SPADES)); //Should be lowest
  Jordan->add_card(Card(QUEEN,SPADES));
  Jordan->add_card(Card(JACK,HEARTS)); //keep

  Card upcard(NINE,DIAMONDS);
  Card trueleadcard(KING,CLUBS);
  Suit trump = DIAMONDS;

  Jordan->add_and_discard(upcard);

  ASSERT_EQUAL(Jordan->lead_card(DIAMONDS),trueleadcard);
  ASSERT_EQUAL(Jordan->play_card(trueleadcard,trump),Card(QUEEN,SPADES));
  ASSERT_EQUAL(Jordan->play_card(trueleadcard,trump),Card(NINE,DIAMONDS));
  ASSERT_EQUAL(Jordan->play_card(trueleadcard,trump),Card(JACK,HEARTS));
  ASSERT_EQUAL(Jordan->play_card(trueleadcard,trump),Card(JACK,DIAMONDS));

  delete Jordan;
}


TEST_MAIN()
