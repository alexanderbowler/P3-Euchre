// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(add_card)
{
    Player * bob = Player_factory("Bob","Simple");
    Card c1(JACK,HEARTS);
    Card c2(JACK,SPADES);
    Card c3(ACE, HEARTS);
    Card c4(ACE,DIAMONDS);
    Card c5(JACK,DIAMONDS);
    bob->add_card(c1);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);

    delete bob;
}

TEST(make_trump1){
    Player * bob = Player_factory("Bob","Simple");
    Card c1(JACK,HEARTS);
    Card c2(JACK,SPADES);
    Card c3(ACE, HEARTS);
    Card c4(ACE,DIAMONDS);
    Card c5(NINE,DIAMONDS);
    Card up(NINE,HEARTS);
    bob->add_card(c1);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);
    Suit trump;
    bool tru = bob->make_trump(up,false,1,trump);
    ASSERT_EQUAL(trump,HEARTS);
    ASSERT_EQUAL(tru,true);

    delete bob;
}

TEST(make_trump2){
    Player * bob = Player_factory("Bob","Simple");
    Card c1(JACK,HEARTS);
    Card c2(JACK,SPADES);
    Card c3(TEN, HEARTS);
    Card c4(TEN,DIAMONDS);
    Card c5(NINE,DIAMONDS);
    Card up(NINE,HEARTS);
    bob->add_card(c1);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);
    Suit trump;
    bool fal = bob->make_trump(up,true,1,trump);
    ASSERT_EQUAL(fal,false);

    delete bob;
}

TEST(make_trump3){
    Player * bob = Player_factory("Bob","Simple");
    Card c1(JACK,HEARTS);
    Card c2(JACK,SPADES);
    Card c3(TEN, HEARTS);
    Card c4(TEN,DIAMONDS);
    Card c5(NINE,DIAMONDS);
    Card up(NINE,HEARTS);
    bob->add_card(c1);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);
    Suit trump;
    bool trufal = bob->make_trump(up,false,2,trump); //asserts tru bc left bower
    ASSERT_EQUAL(trufal,true);
    ASSERT_EQUAL(trump,DIAMONDS);

    delete bob;
}

TEST(make_trump4){
    Player * bob = Player_factory("Bob","Simple");
    Card c1(TEN,HEARTS);
    Card c2(JACK,SPADES);
    Card c3(TEN, HEARTS);
    Card c4(TEN,DIAMONDS);
    Card c5(NINE,DIAMONDS);
    Card up(NINE,HEARTS);
    bob->add_card(c1);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);
    Suit trump;
    bool trufal = bob->make_trump(up,true,2,trump); //asserts tru bc screwdealer
    ASSERT_EQUAL(trufal,true);
    ASSERT_EQUAL(trump,DIAMONDS);

    delete bob;
}

TEST(make_trump5){
    Player * bob = Player_factory("Bob","Simple");
    Card c1(TEN,HEARTS);
    Card c2(JACK,SPADES);
    Card c3(TEN, HEARTS);
    Card c4(TEN,DIAMONDS);
    Card c5(NINE,DIAMONDS);
    Card up(JACK,DIAMONDS);
    bob->add_card(c1);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);
    Suit trump;
    bool trufal = bob->make_trump(up,false,2,trump); //asserts tru bc screwdealer
    ASSERT_EQUAL(trufal,false);

    delete bob;
}


TEST(addDiscard){
    Player * bob = Player_factory("Bob","Simple");
    Card c1(TEN,HEARTS);
    Card c2(JACK,SPADES);
    Card c3(QUEEN, HEARTS);
    Card c4(TEN,DIAMONDS);
    Card c5(NINE,DIAMONDS);
    Card up(JACK,DIAMONDS);
    bob->add_card(c1);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);
    bob->add_and_discard(up);

    delete bob;
}

TEST(addDiscard2){
   Player * bob = Player_factory("Bob","Simple");
    Card c1(TEN,DIAMONDS);
    Card c2(JACK,HEARTS);
    Card c3(QUEEN, DIAMONDS);
    Card c4(JACK,DIAMONDS);
    Card c5(ACE,DIAMONDS);
    Card up(NINE,DIAMONDS);
    bob->add_card(c1);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);
    bob->add_and_discard(up);

    delete bob; 
}



TEST(leadCard) {
    Player * bob = Player_factory("Bob","Simple");
    Card c1(TEN,HEARTS);
    Card c2(JACK,SPADES);
    Card c3(QUEEN, HEARTS);
    Card c4(TEN,DIAMONDS);
    Card c5(NINE,DIAMONDS);
    Card up(JACK,DIAMONDS);
    bob->add_card(c1);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);

  bob->add_and_discard(up);

  Card card_led = bob->lead_card(DIAMONDS);

  Card q_h(QUEEN, HEARTS);
  ASSERT_EQUAL(card_led, q_h); 

  delete bob;
}

TEST(leadCard2) {
    Player * bob = Player_factory("Bob","Simple");
    Card c1(KING,CLUBS);
    Card c2(JACK,SPADES);
    Card c3(QUEEN, CLUBS);
    Card c4(TEN,CLUBS);
    Card c5(NINE,CLUBS);
    Card up(ACE,CLUBS);
    bob->add_card(c1);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);

  bob->add_and_discard(up);

  Card card_led = bob->lead_card(CLUBS);

  Card q_h(JACK, SPADES);
  ASSERT_EQUAL(card_led, q_h); 

  delete bob;
}

TEST(leadCard3) {
    Player * bob = Player_factory("Bob","Simple");
    Card c1(TEN,HEARTS);
    Card c2(JACK,SPADES);
    Card c3(JACK, HEARTS);
    Card c4(JACK,DIAMONDS);
    Card c5(ACE,DIAMONDS);
    Card up(JACK,DIAMONDS);
    bob->add_card(c1);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);

  bob->add_and_discard(up);

  Card card_led = bob->lead_card(DIAMONDS);

  Card q_h(JACK, SPADES);
  ASSERT_EQUAL(card_led, q_h); 

  delete bob;
}

TEST(leadCard4) {
    Player * bob = Player_factory("Bob","Simple");
    Card c1(TEN,DIAMONDS);
    Card c2(ACE,SPADES);
    Card c3(JACK, HEARTS);
    Card c4(QUEEN,DIAMONDS);
    Card c5(NINE,DIAMONDS);
    bob->add_card(c1);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);


  Card card_led = bob->lead_card(DIAMONDS);

  Card q_h(ACE, SPADES);
  ASSERT_EQUAL(card_led, q_h); 

  delete bob;
}

TEST(playCard){
    Player * bob = Player_factory("Bob","Simple");
    Card c1(TEN,HEARTS);
    Card c2(JACK,SPADES);
    Card c3(QUEEN, HEARTS);
    Card c4(TEN,DIAMONDS);
    Card c5(NINE,CLUBS);
    Card led(JACK,DIAMONDS);
    bob->add_card(c1);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);

    Card cardPlayed = bob->play_card(led,HEARTS);

    Card q_h(QUEEN, HEARTS);
    ASSERT_EQUAL(cardPlayed, q_h);
    
    delete bob;
}

TEST(playCard2){
   Player * bob = Player_factory("Bob","Simple");
    Card c1(TEN,CLUBS);
    Card c2(JACK,CLUBS);
    Card c3(QUEEN, CLUBS);
    Card c4(TEN,DIAMONDS);
    Card c5(NINE,CLUBS);
    Card led(ACE,DIAMONDS);
    bob->add_card(c1);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);

    Card cardPlayed = bob->play_card(led,HEARTS);

    Card q_h(TEN, DIAMONDS);
    ASSERT_EQUAL(cardPlayed, q_h);
    
    delete bob;
} 

TEST(playCard3){
   Player * bob = Player_factory("Bob","Simple");
    Card c1(TEN,CLUBS);
    Card c2(JACK,CLUBS);
    Card c3(QUEEN, CLUBS);
    Card c4(TEN,DIAMONDS);
    Card c5(NINE,CLUBS);
    Card led(JACK,DIAMONDS);
    bob->add_card(c1);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);

    Card cardPlayed = bob->play_card(led,HEARTS);

    Card q_h(NINE, CLUBS);
    ASSERT_EQUAL(cardPlayed, q_h);
    
    delete bob;
} 
TEST(playCard4){
   Player * bob = Player_factory("Bob","Simple");
    Card c1(NINE,SPADES);
    Card c2(JACK,CLUBS);
    Card c3(QUEEN, CLUBS);
    Card c4(TEN,HEARTS);
    Card c5(ACE,CLUBS);
    Card led(ACE,DIAMONDS);
    bob->add_card(c1);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);

    Card cardPlayed = bob->play_card(led,SPADES);

    Card q_h(TEN, HEARTS);
    ASSERT_EQUAL(cardPlayed, q_h);
    
    delete bob;
} 

TEST(playAllCard){
   Player * bob = Player_factory("Bob","Simple");
    Card c1(NINE,SPADES);
    Card c2(JACK,DIAMONDS);
    Card c3(QUEEN, CLUBS);
    Card c4(TEN,HEARTS);
    Card c5(ACE,CLUBS);
    Card led(ACE,HEARTS);
    bob->add_card(c1);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);

    Card cardPlayed0 = bob->play_card(led,SPADES);
    Card cardPlayed1 = bob->play_card(led,SPADES);
    Card cardPlayed2 = bob->play_card(led,SPADES);
    Card cardPlayed3 = bob->play_card(led,SPADES);
    Card cardPlayed4 = bob->play_card(led,SPADES);


    Card correct(TEN, HEARTS);
    ASSERT_EQUAL(cardPlayed0, correct);
    Card correct1(JACK, DIAMONDS);
    ASSERT_EQUAL(cardPlayed1, correct1);
    Card correct2(QUEEN, CLUBS);
    ASSERT_EQUAL(cardPlayed2, correct2);
    Card correct3(ACE, CLUBS);
    ASSERT_EQUAL(cardPlayed3, correct3);
    Card correct4(NINE, SPADES);
    ASSERT_EQUAL(cardPlayed4, correct4);
    
    delete bob;
} 

TEST(playAllCard2){
   Player * bob = Player_factory("Bob","Simple");
    Card c1(NINE,SPADES);
    Card c2(JACK,DIAMONDS);
    Card c3(QUEEN, CLUBS);
    Card c4(TEN,HEARTS);
    Card c5(ACE,CLUBS);
    Card led(ACE,HEARTS);
    bob->add_card(c1);
    bob->add_card(c2);
    bob->add_card(c3);
    bob->add_card(c4);
    bob->add_card(c5);

    Card cardPlayed0 = bob->lead_card(SPADES);
    Card cardPlayed1 = bob->play_card(c5,SPADES);
    Card cardPlayed2 = bob->play_card(led,SPADES);
    Card cardPlayed3 = bob->play_card(led,SPADES);
    Card cardPlayed4 = bob->play_card(led,SPADES);


    Card correct(ACE, CLUBS);
    ASSERT_EQUAL(cardPlayed0, correct);
    Card correct1(QUEEN, CLUBS);
    ASSERT_EQUAL(cardPlayed1, correct1);
    Card correct2(TEN, HEARTS);
    ASSERT_EQUAL(cardPlayed2, correct2);
    Card correct3(JACK, DIAMONDS);
    ASSERT_EQUAL(cardPlayed3, correct3);
    Card correct4(NINE, SPADES);
    ASSERT_EQUAL(cardPlayed4, correct4);
    
    delete bob;
} 


TEST_MAIN()
