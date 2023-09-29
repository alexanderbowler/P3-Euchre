// Project UID 1d9f47bfc76643019cfbf037641defe1
#include <iostream>
#include <fstream>
#include <cassert>
#include "Player.h"
#include "Pack.h"
#include "Card.h"
#include <cstring>
#include <cmath>
using namespace std;

class Game {
 public:
  Game(string s, int pWin, istream& is, string pInfo[]) 
  : pack(is), pointsToWin(pWin),dealer(0){
            for(int i=0;i<8;i+=2){
                players.push_back(Player_factory(pInfo[i],pInfo[i+1]));
            }
            if(s=="shuffle")
                shuffleBool = true;
            else
                shuffleBool = false;
        }
  void play(){
    int hand =0;
    while(teamScores[0]<pointsToWin&&teamScores[1]<pointsToWin)
    {
        play_hand(hand);
        hand++;
    }
    if(teamScores[0]>pointsToWin)
        cout<<(*players[0]).get_name()<<" and "<<(*players[2]).get_name()
        <<" win!\n";
    else
        cout<<(*players[1]).get_name()<<" and "<<(*players[3]).get_name()
        <<" win!\n";

    for (size_t i = 0; i < players.size(); ++i) {
        delete players[i];
        }
  }

 private:
  bool shuffleBool;
  std::vector<Player*> players;
  Pack pack;
  int pointsToWin;
  int dealer;
  Suit trump;
  Card up;
  int teamMadeTrump; //team 0 or 1 team 0 is person 0 and 2 team 1 is 1,3
  int teamScores[2] = {0,0};//scores for teams
  int trickwins[2] = {0,0}; //trick wins for team 0 and 1

  void shuffle(){
    pack.shuffle();
  }
  //REQUIRES: numdeal be 3 or 2
  void deal3or2(int pIndex,int numDeal){
    for(int i=0;i<numDeal;i++)
        (*players[pIndex]).add_card(pack.deal_one());
  }
  void deal(){
    for(int i=1;i<5;i++){
        if(i%2==1)
            deal3or2((i+dealer)%4,3);
        else
            deal3or2((i+dealer)%4,2);
    }
    for(int i=1;i<5;i++){
        if(i%2==1)
            deal3or2((i+dealer)%4,2);
        else
            deal3or2((i+dealer)%4,3);
    }

  }
  void make_trump(){
    up = pack.deal_one();
    cout<<up<<" turned up\n";
    Suit orderedUp;
    for(int j=dealer+1;j<dealer+9;j++)
    {
        int i=j%4;
        if(i==dealer){
         if((*players[i]).make_trump(up,true,(j-dealer)/(5)+1,orderedUp)){
            trump = orderedUp;
            teamMadeTrump=i%2;
            cout<<(*players[i]).get_name()<<" orders up "<<trump<<endl;
            if(j<dealer+5)
                (*players[dealer%4]).add_and_discard(up);
            return;
         }
         else  
            cout<<(*players[i]).get_name()<<" passes\n";
        }
        else{
         if((*players[i]).make_trump(up,false,(j-dealer)/(5)+1,orderedUp)){
            trump = orderedUp;
            teamMadeTrump=i%2;
            cout<<(*players[i]).get_name()<<" orders up "<<trump<<endl;
            if(j<dealer+5)
                (*players[dealer%4]).add_and_discard(up);
            return;
         }
         else  
            cout<<(*players[i]).get_name()<<" passes\n";
        }
    }
    /*for(int j=dealer+1;j<dealer+5;j++){
        int i=j%4;
        if(i==dealer){
         if((*players[i]).make_trump(up,true,2,orderedUp)){
            trump = orderedUp;
            teamMadeTrump=i%2;
            cout<<(*players[i]).get_name()<<" orders up "<<trump<<endl;
            return;
         }
        else  
            cout<<(*players[i]).get_name()<<" passes\n";
        }
        else{
         if((*players[i]).make_trump(up,false,2,orderedUp)){
            trump = orderedUp;
            teamMadeTrump=i%2;
            cout<<(*players[i]).get_name()<<" orders up "<<trump<<endl;
            return;
         }
         else  
            cout<<(*players[i]).get_name()<<" passes\n";
        }
    }*/
  }
//returns the index of whoever won the trick
  int play_trick(int trickLeader){
    Card curTrick[4];
    curTrick[trickLeader] = (*players[trickLeader]).lead_card(trump);
    cout<<curTrick[trickLeader]<<" led by "<<(*players[trickLeader]).get_name()<<endl;
    for(int i=trickLeader+1;i<trickLeader+4;i++){
        curTrick[i%4] = (*players[i%4]).play_card(curTrick[trickLeader],trump);
        cout<<curTrick[i%4]<<" played by "<<(*players[i%4]).get_name()<<endl;
    }
    int winIndex =0;
    for(int i=1;i<4;i++){
        if(Card_less(curTrick[winIndex],curTrick[i],curTrick[trickLeader],trump))
            winIndex=i;
    }
    cout<<(*players[winIndex]).get_name()<<" takes the trick\n"<<endl;
    return winIndex;
  }

  void play_hand(int handNum){
    pack.reset();
    if(shuffleBool)
        pack.shuffle();
    cout<<"Hand "<<handNum<<endl;
    dealer = handNum%4;
    cout<<(*players[dealer]).get_name()<<" deals\n";
    deal();
    make_trump();

    cout<<endl;

    trickwins[0] =0;
    trickwins[1] =0;
    int leader = (dealer+1)%4;
    for(int i=0;i<5;i++)
    {
       leader = play_trick(leader);
       trickwins[leader%2]++;
    }

    updateScore();
  }

  void updateScore(){
    for(int i=0;i<2;i++){
    if(trickwins[i]>2){
        cout<<(*players[i]).get_name()<<" and "<<(*players[i+2]).get_name()
            <<" win the hand\n";
        if(teamMadeTrump==i&&(trickwins[i]==3||trickwins[i]==4))
                teamScores[i]++;
        else if(teamMadeTrump==i&&trickwins[i]==5){
                teamScores[i]+=2;
                cout<<"march!"<<endl;
            }
        else{
            teamScores[i]+=2;
            cout<<"euchred!"<<endl;
        }
    }
    }
    cout<<(*players[0]).get_name()<<" and "<<(*players[2]).get_name()<<
    " have "<<teamScores[0]<<" points\n";
    cout<<(*players[1]).get_name()<<" and "<<(*players[3]).get_name()<<
    " have "<<teamScores[1]<<" points\n"<<endl;
  }
  
};


int main(int argc, char **argv) {
    
  if(argc!=12||atoi(argv[3])<1||atoi(argv[3])>100
    ||(strcmp(argv[2],"shuffle")!=0&&strcmp(argv[2],"noshuffle")!=0)){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
        return -1;
    }
    for(int i=5;i<=argc;i+=2)
        if(strcmp(argv[i],"Simple")!=0&&strcmp(argv[i],"Human")!=0){
           cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
            return -1; 
    }
    string filename = argv[1];
    ifstream fin;
    fin.open(filename.c_str());
    if (!fin.is_open()){
       cout << "Error opening " << filename << endl;
       return -1;
  }
  for(int i=0;i<argc;i++)
        cout<<argv[i]<<" ";
    cout<<endl;
  string info[8];
  for(int i=0;i<8;i++){
    info[i] = argv[4+i];
  }
  int points = stoi(argv[3]);
  Game game(argv[2],points,fin,info);
  game.play();
}



