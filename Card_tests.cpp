// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>


using namespace std;


TEST(test_card_rank_suit) {
    Card c(JACK, DIAMONDS);
    ASSERT_EQUAL(JACK, c.get_rank());
    ASSERT_EQUAL(DIAMONDS, c.get_suit());
    
    //(D > C > H > S)
    
    
}
TEST(test_card_operator) {
    Card c(ACE, HEARTS);
    Card d(KING, CLUBS);
    // ACE is not less than KING
    //assert c < d is false
    ASSERT_FALSE(operator<(c,d));
   // ASSERT_TRUE(c.operator<);
    
}
TEST(test_card_operator_1) {
    Card c(JACK, HEARTS);
    Card d(KING, CLUBS);
    //assert c < d is true
    ASSERT_TRUE(operator<(c,d));
   // ASSERT_TRUE(c.operator<);
    
}
TEST(test_card_operator_2) {
    Card c(JACK, HEARTS);
    Card d(KING, CLUBS);
    //assert d < c is false
    ASSERT_FALSE(operator<(d,c));
   // ASSERT_TRUE(c.operator<);
    
}
TEST(test_card_operator_3) {
    Card c(JACK, HEARTS);
    Card d(KING, HEARTS);
    //assert d < c is false
 //   ASSERT_TRUE(operator<(c,d));
   // ASSERT_TRUE(c.operator<);
    
}

TEST(test_card_operator_less_equal) {
    Card c(JACK, HEARTS);
    Card d(KING, HEARTS);
    //assert c < d is true
    ASSERT_TRUE(operator<=(c,d));
   // ASSERT_TRUE(c.operator<);
    
}

TEST(test_card_operator_less_equal1) {
    Card c(JACK, HEARTS);
    Card d(JACK, HEARTS);
    
    // assert c <= d is true
    ASSERT_TRUE(operator<=(c,d));
    
}

TEST(test_card_opearator_less_equal2){
    Card c(JACK, DIAMONDS);
    Card d(JACK, HEARTS);
    
    
   // ASSERT_TRUE(operator<=(d,c));
    
}

TEST(test_card_operator_greater){
    Card c(JACK, DIAMONDS);
    Card d(JACK, HEARTS);
    
    ASSERT_TRUE(operator>(c,d));
    
    
}

TEST(test_card_operator_greater_ranks){
    
// card wher lhs_suit < rhs_suit but lhs_rank>rhs_rank
    Card c(JACK, SPADES);
    Card d(NINE, DIAMONDS);
    
    // jack is > than 9 Spades < Diamonds Assert true
    ASSERT_TRUE(operator>(c,d));
}

TEST(test_card_operator_greater_same){
    Card c (JACK, DIAMONDS);
    Card d (JACK, DIAMONDS);
    
    ASSERT_FALSE(operator>(c,d));
}

TEST(test_card_operator_greater_equal){
    
    Card c (KING, DIAMONDS);
    Card d (JACK, HEARTS);
    
    ASSERT_TRUE(operator>=(c,d));
    
}

TEST(test_card_operator_equal){
    Card c(KING, DIAMONDS);
    Card d(KING, DIAMONDS);
    
    ASSERT_TRUE(operator>=(c,d));
    
}

TEST(test_card_operator_doubleequal){
    Card c(KING, DIAMONDS);
    Card d(KING, DIAMONDS);
    
    ASSERT_TRUE(operator==(c,d));
}

TEST(test_card_operator_doubleequal_false){
    Card c(KING, DIAMONDS);
    Card d(ACE, DIAMONDS);
    
    ASSERT_FALSE(operator==(c,d));
    
}

TEST(test_card_operator_doubleequal_almost){
    Card c(KING,DIAMONDS);
    Card d(KING, HEARTS);
    
  //  ASSERT_FALSE(operator==(c,d)); 
}

TEST(test_card_operator_not_equal){
    Card c(KING, DIAMONDS);
    Card d(KING, HEARTS);
    
    ASSERT_TRUE(operator!=(c,d));
}
//(D > C > H > S)


// Add more test cases here

TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

// Add more test cases here

TEST(get_suit_with_trump){
    Card leftbowc(JACK, DIAMONDS);
    Card randomc(ACE, CLUBS);

    Suit trump = HEARTS;

    ASSERT_EQUAL(HEARTS, leftbowc.get_suit(trump));
    ASSERT_EQUAL(CLUBS, randomc.get_suit(trump));
}

TEST(test_face_or_ace) {
    Card trueace(ACE, HEARTS);
    Card truejack(JACK, HEARTS);
    Card trueking(KING, HEARTS);
    Card truequeen(QUEEN, HEARTS);
    Card falsec(TEN, HEARTS);

    ASSERT_EQUAL(true,trueace.is_face_or_ace());
    ASSERT_EQUAL(true,truejack.is_face_or_ace());
    ASSERT_EQUAL(true,trueking.is_face_or_ace());
    ASSERT_EQUAL(true,truequeen.is_face_or_ace());
    ASSERT_EQUAL(false,falsec.is_face_or_ace());
}

TEST(is_right_bower_test){
    Card rightbow(JACK, HEARTS);
    Card notrightbow(JACK, DIAMONDS);

    Suit trump = HEARTS;
    ASSERT_EQUAL(true,rightbow.is_right_bower(trump));
    ASSERT_EQUAL(false,notrightbow.is_right_bower(trump));
}

TEST(is_left_bower_test){
    Card leftbow(JACK, HEARTS);
    Card notleftbow(JACK, DIAMONDS);

    Suit trump = DIAMONDS;

    ASSERT_EQUAL(true,leftbow.is_left_bower(trump));
    ASSERT_EQUAL(false,notleftbow.is_left_bower(trump));

}

TEST(is_trump_card){
    Card truec(ACE, DIAMONDS);
    Card leftbowc(JACK, HEARTS);
    Card falsec(ACE, CLUBS);
    
    Suit trump = DIAMONDS;

    ASSERT_EQUAL(true,truec.is_trump(trump));
    ASSERT_EQUAL(true,leftbowc.is_trump(trump));
    ASSERT_EQUAL(false,falsec.is_trump(trump));
}

TEST(less_than_operator){
    Card greaterc1(ACE, CLUBS);
    Card lesserc2(JACK, CLUBS);
    Card greaterc3(ACE, DIAMONDS);
    Card lesserc4(ACE, CLUBS);

    ASSERT_EQUAL(true,operator<(lesserc2,greaterc1));
    ASSERT_EQUAL(true,operator<(lesserc4,greaterc3));
}

TEST(less_than_or_equal_to_operator){
    Card greaterc1(ACE, CLUBS);
    Card lesserc1(JACK, CLUBS);
    ASSERT_EQUAL(true,operator<=(lesserc1,greaterc1)); //Test basic less than

    Card greaterc2(KING, DIAMONDS);
    Card lesserc2(KING, HEARTS);
    ASSERT_EQUAL(true,operator<=(lesserc2,greaterc2)); //Test breaking ties if not same

    Card equalc1(QUEEN,HEARTS);
    Card equalc2(QUEEN, HEARTS);
    ASSERT_EQUAL(true,operator<=(equalc1,equalc2)); //Test if same/equal

}

TEST(greater_than_operator){
    Card greaterc1(ACE, CLUBS);
    Card lesserc2(JACK, CLUBS);
    Card greaterc3(ACE, DIAMONDS);
    Card lesserc4(ACE, CLUBS);

    ASSERT_EQUAL(true,operator>(greaterc1,lesserc2));
    ASSERT_EQUAL(false,operator>(lesserc4,greaterc3));
}

TEST(greater_than_or_equal_to_operator){
    Card greaterc1(ACE, CLUBS);
    Card lesserc1(JACK, CLUBS);
    ASSERT_EQUAL(true,operator>=(greaterc1,lesserc1)); //Test basic less than
    ASSERT_EQUAL(false,operator>=(lesserc1,greaterc1));

    Card greaterc2(KING, DIAMONDS);
    Card lesserc2(KING, HEARTS);
    ASSERT_EQUAL(true,operator>=(greaterc2,lesserc2)); //Test breaking ties if not same
    ASSERT_EQUAL(false,operator>=(lesserc2,greaterc2));

    Card equalc1(QUEEN,HEARTS);
    Card equalc2(QUEEN,HEARTS);
    ASSERT_EQUAL(true,operator>=(equalc1,equalc2)); //Test if same/equal
}

TEST(equal_to_operator){
    Card equalc1(NINE, SPADES);
    Card equalc2(NINE, SPADES);
    ASSERT_EQUAL(true,operator==(equalc1,equalc2));

    Card notequalc1(ACE, CLUBS);
    Card notequalc2(KING, CLUBS);
    ASSERT_EQUAL(false,operator==(notequalc1,notequalc2));

    Card notequalc3(ACE, DIAMONDS);
    Card notequalc4(ACE, CLUBS);
    ASSERT_EQUAL(false,operator==(notequalc3,notequalc4));

    Card notequalc5(ACE, DIAMONDS);
    Card notequalc6(JACK, CLUBS);
    ASSERT_EQUAL(false,operator==(notequalc5,notequalc6));
}

TEST(not_equal_to_operator){
    Card equalc1(NINE, SPADES);
    Card equalc2(NINE, SPADES);
    ASSERT_EQUAL(false,operator!=(equalc1,equalc2));

    Card notequalc1(ACE, CLUBS);
    Card notequalc2(KING, CLUBS);
    ASSERT_EQUAL(true,operator!=(notequalc1,notequalc2));

    Card notequalc3(ACE, DIAMONDS);
    Card notequalc4(ACE, CLUBS);
    ASSERT_EQUAL(true,operator!=(notequalc3,notequalc4));

    Card notequalc5(ACE, DIAMONDS);
    Card notequalc6(JACK, CLUBS);
    ASSERT_EQUAL(true,operator!=(notequalc5,notequalc6));
}

TEST(test_suit_next){
    Card c1(ACE, HEARTS);
    Card c2(ACE, CLUBS);
    Card c3(ACE, DIAMONDS);
    Card c4(ACE, SPADES);

    ASSERT_EQUAL(DIAMONDS, Suit_next(c1.get_suit()));
    ASSERT_EQUAL(SPADES, Suit_next(c2.get_suit()));
    ASSERT_EQUAL(HEARTS, Suit_next(c3.get_suit()));
    ASSERT_EQUAL(CLUBS, Suit_next(c4.get_suit()));

}

// break

TEST(operator_out){
    Card ace_hearts = Card(ACE, HEARTS);
    ostringstream oss;
    oss << ace_hearts;
    ASSERT_EQUAL(oss.str(), "Ace of Hearts");
}

TEST(card_less_no_led){
    Card equal1(ACE, DIAMONDS); //Both cards are same
    Card equal2(ACE, DIAMONDS);
    Suit trump1 = CLUBS;
    ASSERT_EQUAL(false,Card_less(equal1,equal2,trump1));

    Card less1(NINE, DIAMONDS); //Trump suit with one greater
    Card greater1(ACE, DIAMONDS);
    Suit trump2 = DIAMONDS;
    ASSERT_EQUAL(true,(Card_less(less1,greater1,trump2)));

    Card less2(ACE, DIAMONDS); //Both trump suit with right bower
    Card greater2(JACK, DIAMONDS);
    Suit trump3 = DIAMONDS;
    ASSERT_EQUAL(true,(Card_less(less2,greater2,trump3)));

    Card less3(QUEEN, CLUBS); //1 Trump, 1 not trump
    Card greater3(JACK, DIAMONDS);
    Suit trump4 = DIAMONDS;
    ASSERT_EQUAL(true,Card_less(less3,greater3,trump4));

    Card greater4(JACK, DIAMONDS); //Left bower and highest non-jack trump
    Card lesser4(ACE, HEARTS);
    Suit trump5 = HEARTS;
    ASSERT_EQUAL(true,Card_less(lesser4,greater4,trump5));

    Card greater5(JACK, DIAMONDS); //Compare left and right bower
    Card lesser5(JACK, SPADES);
    Suit trump6 = DIAMONDS;
    ASSERT_EQUAL(true,Card_less(lesser5,greater5,trump6));

}

TEST(card_less_with_led){
    Card equal1(ACE, DIAMONDS); //Both cards are same
    Card equal2(ACE, DIAMONDS);
    Suit trump1 = CLUBS;
    Card led1(KING, HEARTS);
    ASSERT_EQUAL(false,Card_less(equal1,equal2,led1,trump1));

    Card less1(NINE, DIAMONDS); //Trump suit with one greater
    Card greater1(ACE, DIAMONDS);
    Suit trump2 = DIAMONDS;
    Card led2(KING, HEARTS);
    ASSERT_EQUAL(true,(Card_less(less1,greater1,led2,trump2)));

    Card less2(ACE, DIAMONDS); //Both trump suit with right bower
    Card greater2(JACK, DIAMONDS);
    Suit trump3 = DIAMONDS;
    Card led3(KING, HEARTS);
    ASSERT_EQUAL(true,(Card_less(less2,greater2,led3,trump3)));

    Card less3(QUEEN, CLUBS); //1 Trump, 1 not trump
    Card greater3(JACK, DIAMONDS);
    Suit trump4 = DIAMONDS;
    Card led4(KING, HEARTS);
    ASSERT_EQUAL(true,Card_less(less3,greater3,led4,trump4));

    Card greater4(JACK, DIAMONDS); //Left bower and highest non-jack trump
    Card lesser4(ACE, HEARTS);
    Suit trump5 = HEARTS;
    Card led5(KING, HEARTS);
    ASSERT_EQUAL(true,Card_less(lesser4,greater4,led5,trump5));

    Card greater5(JACK, DIAMONDS); //Compare left and right bower
    Card lesser5(JACK, SPADES);
    Suit trump6 = DIAMONDS;
    Card led6(KING, HEARTS);
    ASSERT_EQUAL(true,Card_less(lesser5,greater5,led6,trump6));

    Card test1(KING, CLUBS);
    Card test2(QUEEN, DIAMONDS);
    Suit trumptest = HEARTS;
    Card ledtest(ACE, DIAMONDS);
    ASSERT_EQUAL(true,Card_less(test1,test2,ledtest,trumptest));

    Card test3(KING, CLUBS);
    Card test4(QUEEN, DIAMONDS);
    Suit trumptester = CLUBS;
    Card ledtest1(ACE, DIAMONDS);
    ASSERT_EQUAL(true,Card_less(test4,test3,ledtest1,trumptester));

    Card leftbow(JACK, DIAMONDS);
    Card notleftbow(ACE, HEARTS);
    Suit bowtrump = HEARTS;
    Card ledhope(NINE, DIAMONDS);
    ASSERT_EQUAL(true,Card_less(notleftbow,leftbow,ledhope,bowtrump));

    Card leftbowerled(JACK, DIAMONDS);
    Card ledsuitself(ACE, DIAMONDS);
    Suit testrump = HEARTS;
    Card ledtester1(KING, DIAMONDS);
    ASSERT_EQUAL(true,Card_less(ledsuitself,leftbowerled,ledtester1,testrump));

    //Prob need more test
}

TEST(card_esdgar){
    Card replacement(NINE, HEARTS);

    Card c1(JACK, SPADES);
    Card c2(TEN, DIAMONDS);
    Suit trump = HEARTS;
    ASSERT_EQUAL(true,Card_less(c1,replacement,trump));
    ASSERT_EQUAL(true,Card_less(c2,replacement,trump));

}

TEST(card_with_2ndsimplecase){
    Card tester1(JACK,DIAMONDS);
    Card tester2(TEN,HEARTS);
    Card ninehearts(NINE,HEARTS);
    Card kingheart(KING,HEARTS);
    Suit trump = HEARTS;
    Card leadcard = tester1;
    ASSERT_EQUAL(false,Card_less(tester1,tester2,leadcard,trump));
    ASSERT_EQUAL(false,Card_less(tester1,ninehearts,leadcard,trump));
    ASSERT_EQUAL(false,Card_less(tester1,kingheart,leadcard,trump));
}


TEST_MAIN()
