// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Pack.h"
#include <cassert>

  // EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
  next = 0;
}


  // EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on.
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
  Pack::Pack(){
    reset();
    for(int i=0;i<4;i++)
        for(int j=0;j<6;j++)
            cards[6*i+j] = Card(static_cast<Rank>(7+j),static_cast<Suit>(i));
    
  }

  // REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
 Pack::Pack(std::istream& pack_input){
  reset();
    std::string suit, rank;
    for(int i=0;i<24;i++)
    {
        pack_input>>rank;
        pack_input>>suit;
        pack_input>>suit;
        cards[i]=Card(string_to_rank(rank),string_to_suit(suit));
    }
 }

  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
  Card Pack::deal_one()
  {
    assert(next<PACK_SIZE);
    return cards[next++];
  }



  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
  void Pack::shuffle(){
    for(int j=0;j<7;j++)
    {
        Card newCards[24];
      for(int i=0;i<24;i+=2){
  			newCards[i] = cards[12+i/2];
        newCards[i+1] = cards[i/2];
      }
    for(int i=0;i<24;i++)
        cards[i] = newCards[i];
    }
  }


  // EFFECTS: returns true if there are no more cards left in the pack
  bool Pack::empty() const{
    return !(next<PACK_SIZE);
  }


