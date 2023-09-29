// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    Card second = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
    ASSERT_EQUAL(TEN,second.get_rank());
    ASSERT_EQUAL(SPADES, second.get_suit());
}

TEST(test_istream_ctor){
    istringstream in("Nine of Spades\nTen of Spades\nJack of Spades\nQueen of Spades\nKing of Spades\nAce of Spades\nNine of Hearts\nTen of Hearts\nJack of Hearts\nQueen of Hearts\nKing of Hearts\nAce of Hearts\nNine of Clubs\nTen of Clubs\nJack of Clubs\nQueen of Clubs\nKing of Clubs\nAce of Clubs\nNine of Diamonds\nTen of Diamonds\nJack of Diamonds\nQueen of Diamonds\nKing of Diamonds\nAce of Diamonds\n");
    Pack p = Pack(in);
    Card first = p.deal_one();
    Card second = p.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
    ASSERT_EQUAL(TEN,second.get_rank());
    ASSERT_EQUAL(SPADES, second.get_suit());
}

TEST(shuffle){
    Pack pack;
    pack.shuffle();
    Card first = pack.deal_one();
    Card second = pack.deal_one();
    ASSERT_EQUAL(KING, first.get_rank());
    ASSERT_EQUAL(CLUBS, first.get_suit());
    ASSERT_EQUAL(JACK,second.get_rank());
    ASSERT_EQUAL(HEARTS, second.get_suit());
}

/*TEST(empty){
    Pack pack;
    pack.shuffle();
    Card last;
    while(pack.empty()){
        last = pack.deal_one();
    }
    ASSERT_EQUAL(TEN,last.get_rank());
    ASSERT_EQUAL(HEARTS,last.get_suit());
}*/

TEST_MAIN()
