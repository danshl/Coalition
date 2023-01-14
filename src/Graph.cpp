#include "Graph.h"
#include "Agent.h"
Graph::Graph(vector<Party> vertices, vector<vector<int>> edges) : mVertices(vertices), mEdges(edges) 
{
    // You can change the implementation of the constructor, but not the signature!
}

int Graph::getMandates(int partyId) const
{
    return mVertices[partyId].getMandates();
}

int Graph::getEdgeWeight(int v1, int v2) const
{
    return mEdges[v1][v2];
}

int Graph::getNumVertices() const
{
    return mVertices.size();
}

const Party &Graph::getParty(int partyId) const
{
    return mVertices[partyId];
}


void Graph::Change(int id ,int Party_id){
    

    for(int i=0;i<(int)mVertices.size();i++){
        if (i==Party_id){
            mVertices.at(i).numCoalition=id;
         }
    }
}
void Graph::StepParty(Simulation &s){
    for(int i=0;i<getNumVertices();i++){
       if(mVertices.at(i).getState()!=Joined){
          mVertices.at(i).step(s);}
    }
}
void Graph::UpdateCoaltion(int id,int curr_party_id){
   mVertices.at(curr_party_id).numCoalition=(int)mVertices.at(id).numCoalition;

}

void Graph::push_req(Agent &A , int Party_id){
    mVertices.at(Party_id).ReqAgents.push_back(A);
}
void Graph::setState(int Partyid){
    mVertices[Partyid].setState(CollectingOffers);
}