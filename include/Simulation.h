#pragma once

#include <vector>

#include "Graph.h"
#include "Agent.h"

using std::string;
using std::vector;

class Simulation
{
public:
    Simulation(Graph g, vector<Agent> agents);
    void step();
    bool shouldTerminate() const;
    const Graph &getGraph() const;
    const vector<Agent> &getAgents() const;
    const Party &getParty(int partyId) const;
    const vector<vector<int>> getPartiesByCoalitions() const;
    vector<vector<int>> coalitions;//ADD -check warning
    const void Add_agent(Agent &curr_Agent, int Party_id, int curr_party_id);
    const int Size_vector();
    int Sum(int numCoalition) const ;
    void push_req(Agent &A , int Party_id);
    void setState(int Partyid);
private:
    Graph mGraph;
    vector<Agent> mAgents;
};
