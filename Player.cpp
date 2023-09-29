// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Player.h"
#include <vector>
#include <cassert>
#include <algorithm>


std::ostream & operator<<(std::ostream &os, const Player &p) {
  os<<p.get_name();
  return os;
}

bool isAllTrump(std::vector<Card> hand, Suit trump){
    for(int i=0;i<hand.size();i++)
        if(!hand[i].is_trump(trump))
            return false;
    return true;
}

bool hasLedSuit(std::vector<Card> hand, Suit led, Suit trump){
    for(int i=0;i<hand.size();i++)
        if(hand[i].get_suit(trump)==led)
            return true;
    return false;
}

class SimplePlayer : public Player {

private:
    std::string name;
    std::vector<Card> hand;

 public:

    SimplePlayer(std::string n){
        name = n;
    }

     const std::string & get_name() const override {
        return name;
    }

    void add_card(const Card &c) override {
        assert(hand.size()<MAX_HAND_SIZE);
        hand.push_back(c);
    }

    bool make_trump(const Card &upcard, bool is_dealer, int round, Suit &order_up_suit)
    const override {
        assert(round==1||round==2);
        Suit proposedSuit = upcard.get_suit();
        if(round==2)
            proposedSuit = Suit_next(proposedSuit);
        int countSameSuit=0;
        for(int i=0;i<MAX_HAND_SIZE;i++)
            if(hand[i].is_face_or_ace()&&hand[i].is_trump(proposedSuit))
                countSameSuit++;            
        if(round==1&&countSameSuit>=2){
            order_up_suit = proposedSuit;
            return true;
            }
        if(round==2&&is_dealer) //screw the dealaer rules
        {
            order_up_suit = proposedSuit;
            return true;
        }
        if(round==2&&countSameSuit>=1){
           order_up_suit = proposedSuit;
           return true; 
        }
        return false;
    }

    void add_and_discard(const Card &upcard) override{
        Card min = upcard;
        int minIndex = -1;
        Suit trump = upcard.get_suit();
        for(int i=0;i<hand.size();i++){
            if(Card_less(hand[i],min,trump)){
                min = hand[i];
                minIndex=i;
            }
        }
        if(minIndex==-1)
            return;
        else
            hand[minIndex]=upcard;


    }

    Card lead_card(Suit trump) override{
        bool hasBeenPicked = false;
        Card max;
        int maxIndex =-1;
        bool maxIsTrump = isAllTrump(hand,trump);
        if(maxIsTrump)
        {
         for(int i=0;i<hand.size();i++)
         {
            if(!hasBeenPicked){
                max = hand[i];
                maxIndex=i;
                hasBeenPicked = true;
            }
            else if(hasBeenPicked&&Card_less(max,hand[i],trump)){
                max = hand[i];
                maxIndex=i;
             }
         }
        }
        else{
         for(int i=0;i<hand.size();i++)
         {
            if(!hasBeenPicked&&!hand[i].is_trump(trump)){
                max = hand[i];
                maxIndex=i;
                hasBeenPicked = true;
            }
            else if(hasBeenPicked&&Card_less(max,hand[i],trump)
                    &&!hand[i].is_trump(trump)){
                max = hand[i];
                maxIndex=i;
             }
         }
        }
        if(maxIndex==-1)
            assert(false);
        hand.erase(hand.begin()+maxIndex);
        return max;
    }

    Card play_card(const Card &led_card, Suit trump) override{
        Suit ledSuit = led_card.get_suit(trump);
        if(hasLedSuit(hand,ledSuit,trump)){
             Card max;
             bool hasBeenPicked = false;
             int maxIndex =-1;
             for(int i=0;i<hand.size();i++)
            {
                if(!hasBeenPicked&&hand[i].get_suit(trump)==ledSuit){
                    maxIndex = i;
                    max = hand[i];
                    hasBeenPicked = true;
                }
                if(hasBeenPicked&&
                Card_less(max,hand[i],trump)&&hand[i].get_suit(trump)==ledSuit){
                  max = hand[i];
                  maxIndex=i;
                 }
            }
            if(maxIndex==-1)
                assert(false);
            hand.erase(hand.begin()+maxIndex);
            return max;
        }
        else{
            Card min = hand[0];
            int minIndex = 0;
            for(int i=1;i<hand.size();i++)
            {
                if(Card_less(hand[i],min,trump))
                {
                    min = hand[i];
                    minIndex = i;
                }
            }
            hand.erase(hand.begin()+minIndex);
            return min;
        }
    }
};



class HumanPlayer : public Player {

private:
    std::string name;
    std::vector<Card> hand;

    void printHand() const {
    for(int i=0;i<hand.size();i++)
        std::cout<<"Human player "<<name<<"'s hand: ["<<i<<"] "<<hand[i]<<std::endl;
    }

 public:    

    HumanPlayer(std::string n){
        name = n;
    }

     const std::string & get_name() const override {
        return name;
    }

    void add_card(const Card &c) override {
        assert(hand.size()<MAX_HAND_SIZE);
        hand.push_back(c);
        std::sort(hand.begin(), hand.end());
    }

    bool make_trump(const Card &upcard, bool is_dealer, int round, Suit &order_up_suit)
    const override {
        std::string choice;
        printHand();
        std::cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
        std::cin>>choice;
        if (choice != "pass"){ 
            Suit ordered_up = string_to_suit(choice);
            order_up_suit = ordered_up;
            return true;
        }
        return false;
    }

    void add_and_discard(const Card &upcard) override{
        int discardIndex;
        printHand();
        std::cout << "Discard upcard: [-1]\n";
        std::cout << "Human player " << name << ", please select a card to discard:\n";
        std::cin>>discardIndex;
        hand.erase(hand.begin()+discardIndex);
        add_card(upcard);
    }

    Card lead_card(Suit trump) override{
        printHand();
        std::cout << "Human player " << name << ", please select a card:\n";
        int cardToPlay;
        std::cin>>cardToPlay;
        Card play = hand[cardToPlay];
        hand.erase(hand.begin()+cardToPlay);
        return play;
    }

    Card play_card(const Card &led_card, Suit trump) override{
        return lead_card(trump);
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
  if (strategy == "Human"){
    return new HumanPlayer(name);
  }
  
  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}