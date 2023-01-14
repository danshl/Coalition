#include "Simulation.h"
#include "Party.h"
Simulation::Simulation(Graph graph, vector<Agent> agents) :coalitions(vector<vector<int>>((int)agents.size())), mGraph(graph) ,mAgents(agents)  
{
     for(int i=0;i<(int)mAgents.size();i++){ coalitions.pop_back();}
     for(int i=0;i<(int)mAgents.size();i++){
          vector<int> A = vector<int> (0);
           A.push_back(mAgents[i].getPartyId());
           coalitions.push_back(A);
}
    //Initalize numcoalition;
     for(int i=0; i<(int) mAgents.size();i++){
        mGraph.Change(i,mAgents.at(i).getPartyId());
    } 
}


void Simulation::step()
{
     mGraph.StepParty(*this);
   
    


    //Each agent send offers to party;
    for(int i=0; i< (int)mAgents.size();i++){
        mAgents[i].step(*this);
    }

}
bool Simulation::shouldTerminate() const
{
  for(int i=0;i<(int)coalitions.size();i++){
        if(Sum(i)>60){
            return true;
        }
    }
    for(int i=0;i<(int)getGraph().getNumVertices();i++){
        if(getGraph().getParty(i).getState()!=Joined){
            return false;
        }

    }
    return true;
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    // TODO: you MUST implement this method for getting proper output, read the documentation above.

    return coalitions;
}
const void Simulation:: Add_agent(Agent &curr_Agent, int Party_id,int curr_party_id){
    mAgents.push_back(curr_Agent);
    mGraph.UpdateCoaltion(Party_id, curr_party_id);
    
    
}
const int Simulation:: Size_vector(){
    return (int)mAgents.size();
}
int Simulation::Sum(int numCoalition) const{
    int total=0;
    for(int i=0;i<(int)coalitions[numCoalition].size();i++){
        int Party_id = coalitions.at(numCoalition).at(i);
        total=total+(int)getGraph().getMandates(Party_id);
    }
    return total;
}


void Simulation::push_req(Agent &A , int Party_id){
    mGraph.push_req(A,Party_id);
}
void Simulation::setState(int Partyid){
    mGraph.setState(Partyid);
}