#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;
using namespace std;
#include <iostream>
class JoinPolicy;
class Simulation;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};
class Agent; //ADD

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *); //constructor
    ~Party(); //destructor
    Party(const Party &other); //copy constructor
    Party &operator=(const Party &other);// copy assignment operator
    Party(Party &&other); //move constructor
    Party &operator=(Party &&other);// move assignment operator
    vector<Agent> ReqAgents;
    int cooldown; 
    int numCoalition;
   

 
    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    const string &getName() const;
    
    void Push_coalition(Simulation &s , Agent &curr,int partyId);  
    void Max_val(Simulation &s); 
    void Last_val(Simulation &s);
    bool arrangeReq(Simulation &s,Agent &offer)const ;
    int totalMandat(Simulation &s,int numCoalition2);
 

private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
};
