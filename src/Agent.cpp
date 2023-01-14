#include "Agent.h"
#include "Simulation.h"
#include "SelectionPolicy.h"
//constructor
Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy)
{   
}
//clone constructor
Agent::Agent(Agent &curr_agent ,Simulation &s ,int id_curr_party) : mAgentId(s.Size_vector()) , mPartyId(id_curr_party) , mSelectionPolicy() {

    if(curr_agent.mSelectionPolicy->check1()=="M" ){
    mSelectionPolicy = new MandatesSelectionPolicy();
}
else
{
    mSelectionPolicy = new EdgeWeightSelectionPolicy();
}
}

//destructor
Agent::~Agent(){
   if (mSelectionPolicy) { delete mSelectionPolicy; }
}

//copy constructor
Agent::Agent(const Agent &other) : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(){
if(other.mSelectionPolicy->check1()=="M" ){
    mSelectionPolicy = new MandatesSelectionPolicy();
}
else
{
    mSelectionPolicy = new EdgeWeightSelectionPolicy();
}
}

//copy assignment operator
Agent& Agent:: operator=(const Agent &other){
if(this!=&other){
   if(mSelectionPolicy){
    delete mSelectionPolicy;
   }
}
mAgentId = other.mAgentId;
mPartyId = other.mPartyId;
if(other.mSelectionPolicy->check1()=="M" ){
    mSelectionPolicy = new MandatesSelectionPolicy();
}
else
{
    mSelectionPolicy = new EdgeWeightSelectionPolicy();
}
    return *this;
}

//move_constructor
Agent::Agent(Agent &&other): mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy)
{
    other.mSelectionPolicy = nullptr;
}

//move assignment operator
Agent& Agent:: operator=(Agent &&other){
    if (mSelectionPolicy) delete mSelectionPolicy;
    mAgentId = other.mAgentId;
    mPartyId = other.mPartyId;
    mSelectionPolicy = other.mSelectionPolicy;

    other.mSelectionPolicy =nullptr;
    return *this;
}


int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

void Agent::step(Simulation &sim)
{
   if(mSelectionPolicy->check1()=="M"){
        M(sim);
    }
    else {
        E(sim);
    }
}
void Agent::M(Simulation &s){
    int hold=-1;
    bool check=false;
    for(int i=0; i< s.getGraph().getNumVertices();i++){
        if(!check){
        if ((s.getGraph().getEdgeWeight(this->mPartyId, i ) !=0) &( s.getGraph().getParty(i).getState()!= Joined)  & (s.getGraph().getParty(i).arrangeReq(s,*this))){
           if(!check){
            hold=i;
            check=true;
           }

        }
        }
    }
    if(check){
        Party won = s.getGraph().getParty(hold);
        for(int i=hold; i< s.getGraph().getNumVertices();i++){
            if (((s.getGraph().getEdgeWeight(this->mPartyId, i ) !=0)) & (((s.getGraph().getParty(i).getState())!= Joined) & (s.getGraph().getParty(i).arrangeReq(s,*this)))){
                if (s.getParty(i).getMandates()  > won.getMandates()){
                     won = s.getGraph().getParty(i);
                     hold=i;}
            }
        }
        s.push_req(*this,hold);
        s.setState(hold); 
           }
}

void Agent::E(Simulation &s){
    
    int hold=-1;
    bool check=false;
    for(int i=0; i<s.getGraph().getNumVertices();i++){
       if(!check){
        if(i!=this->getPartyId()){
        if (((s.getGraph().getEdgeWeight(this->mPartyId, i ) !=0)) & ((s.getGraph().getParty(i).getState()!= Joined) & (s.getGraph().getParty(i).arrangeReq(s,*this)))){
            hold=i;
            check=true;

        }
        }
       }
    }
    if(check){
        Party won = s.getGraph().getParty(hold);
        int weight = s.getGraph().getEdgeWeight(hold,mPartyId);
        for(int i=0; i<s.getGraph().getNumVertices();i++){
           if(i!=this->getPartyId()){
            if ((s.getGraph().getEdgeWeight(this->mPartyId, i ) !=0) & (s.getGraph().getParty(i).getState()!= Joined) & (s.getGraph().getParty(i).arrangeReq(s,*this))){
                if (s.getGraph().getEdgeWeight(this->mPartyId,i) > weight) {
                    won = s.getGraph().getParty(i); 
                    hold=i;
                    weight = s.getGraph().getEdgeWeight(this->mPartyId,i);}
            }
        }
        }
        s.push_req(*this,hold); 
        s.setState(hold); 
    }
}
