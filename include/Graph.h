#pragma once
#include <vector>
#include "Party.h"

using std::vector;

class Graph
{
public:
    Graph(vector<Party> vertices, vector<vector<int>> edges);
    int getMandates(int partyId) const;
    int getEdgeWeight(int v1, int v2) const;
    int getNumVertices() const;
    const Party &getParty(int partyId) const;
    void Change(int id, int Party_id);
    void StepParty(Simulation &s);
    void UpdateCoaltion(int Party_id, int curr_party_id);
    void push_req(Agent &A , int Party_id);
    void setState(int Partyid);
private:
    vector<Party> mVertices;
    vector<vector<int>> mEdges;
};
