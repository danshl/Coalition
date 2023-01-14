#pragma once

#include <vector>
#include "Graph.h"
using std::string;
class SelectionPolicy;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy); //constructor
    Agent(Agent &curr_agent,Simulation &s,int id_party_curr); //clone_agent
    ~Agent();//destructor
    Agent(const Agent &other); //copy constructor
    Agent &operator=(const Agent &other);//copy assignment operator
    Agent(Agent &&other); //move constructor
    Agent &operator=(Agent &&other); // move assignment operator

    int getPartyId() const;
    int getId() const;
    void step(Simulation &);
    void M(Simulation &s);
    void E(Simulation &s);
    private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
};
