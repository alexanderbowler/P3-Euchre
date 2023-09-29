// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor_BASIC) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
    ASSERT_EQUAL(HEARTS, c.get_suit(DIAMONDS));
    ASSERT_TRUE(c.is_face_or_ace());
    ASSERT_FALSE(c.is_left_bower(SPADES));
    ASSERT_FALSE(c.is_right_bower(CLUBS));
    ASSERT_TRUE(c.is_trump(HEARTS))
    ostringstream expected;
    expected<<"Ace of Hearts";
    ostringstream actual;
    actual<<c;
    ASSERT_EQUAL(expected.str(),actual.str());
    istringstream input("Jack of Spades");
    input>>c;
    Card a(JACK, SPADES);
    ASSERT_EQUAL(a,c);
    Card b(ACE, HEARTS);
    ASSERT_TRUE(b>a);
    ASSERT_EQUAL(Suit_next(HEARTS),DIAMONDS);
    
}

TEST(default_ctor){
    Card c;
    ASSERT_EQUAL(TWO,c.get_rank());
    ASSERT_EQUAL(SPADES,c.get_suit());
}

TEST(get_suit_left_bower){
    Card c(JACK,SPADES);
    ASSERT_EQUAL(CLUBS,c.get_suit(CLUBS));
}

TEST(is_face_or_ace){
    Card c1(SEVEN,SPADES);
    Card c2(QUEEN,HEARTS);
    ASSERT_TRUE(!c1.is_face_or_ace());
    ASSERT_TRUE(c2.is_face_or_ace());
}

TEST(rightBower){
    Card c1(JACK,HEARTS);
    Card c2(JACK,SPADES);
    ASSERT_TRUE(c1.is_right_bower(HEARTS));
    ASSERT_TRUE(!c2.is_right_bower(HEARTS));
}

TEST(leftBower){
    Card c1(JACK,HEARTS);
    Card c2(JACK,SPADES);
    ASSERT_TRUE(!c1.is_left_bower(HEARTS));
    ASSERT_TRUE(c2.is_left_bower(CLUBS));
}

TEST(isTrump){
    Card c1(JACK,HEARTS);
    Card c2(JACK,SPADES);
    ASSERT_TRUE(c1.is_trump(HEARTS));
    ASSERT_TRUE(c2.is_trump(CLUBS));
    ASSERT_FALSE(c1.is_trump(SPADES));
}

TEST(output_input){
    Card c2(JACK,SPADES);
    ostringstream expected;
    expected<<"Jack of Spades";
    ostringstream actual;
    actual<<c2;
    ASSERT_EQUAL(expected.str(),actual.str());
    istringstream input("Jack of Spades");
    input>>c2;
    Card a(JACK, SPADES);
    ASSERT_TRUE(a==c2);
}

TEST(Comparisons){
    Card c1(JACK,HEARTS);
    Card c2(JACK,SPADES);
    Card c3(ACE, HEARTS);
    ASSERT_TRUE(c3>c1);
    ASSERT_TRUE(c3>c2);
    ASSERT_TRUE(c1>c2);
}

TEST(NextSuit){
    ASSERT_EQUAL(SPADES, Suit_next(CLUBS));
    ASSERT_EQUAL(CLUBS,Suit_next(SPADES));
    ASSERT_EQUAL(HEARTS,Suit_next(DIAMONDS));
    ASSERT_EQUAL(DIAMONDS,Suit_next(HEARTS));
}

TEST(CardLessTrump){
    Card c1(JACK,HEARTS);
    Card c2(JACK,SPADES);
    Card c3(ACE, HEARTS);
    Card c4(ACE,DIAMONDS);
    Card c5(JACK,DIAMONDS);
    ASSERT_TRUE(Card_less(c1,c2,SPADES));
    ASSERT_TRUE(Card_less(c1,c3,SPADES));
    ASSERT_TRUE(Card_less(c3,c2,SPADES));
    ASSERT_TRUE(Card_less(c3,c1,DIAMONDS));
    ASSERT_TRUE(Card_less(c4,c1,DIAMONDS));
    ASSERT_TRUE(Card_less(c1,c5,DIAMONDS));
    ASSERT_FALSE(Card_less(c1,c4,DIAMONDS));
}


TEST(CardLessTrumpLed){
    Card c1(JACK,HEARTS);
    Card c2(JACK,SPADES);
    Card c3(ACE, HEARTS);
    Card c4(ACE,DIAMONDS);
    Card c5(JACK,DIAMONDS);
    Card c6(JACK,CLUBS);
    ASSERT_TRUE(Card_less(c3,c5,c4,SPADES));
    ASSERT_TRUE(Card_less(c4,c2,c4,SPADES));
    ASSERT_TRUE(Card_less(c4,c6,c4,SPADES));
    ASSERT_TRUE(Card_less(c6,c4,c4,HEARTS));
}

TEST(getSuit){
    Card c1(JACK,HEARTS);
    Card c2(JACK,SPADES);
    ASSERT_EQUAL(HEARTS,c1.get_suit(SPADES));
    ASSERT_EQUAL(HEARTS,c1.get_suit(HEARTS));
    ASSERT_EQUAL(DIAMONDS,c1.get_suit(DIAMONDS));
    ASSERT_EQUAL(SPADES,c2.get_suit(HEARTS));


}


// Add more test cases here

TEST_MAIN()
