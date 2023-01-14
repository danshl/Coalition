#include "Party.h"
#include "Agent.h"
#include "JoinPolicy.h"
#include "Simulation.h"
#include <iostream>
using namespace std;

//constructor
Party::Party(int id, string name, int mandates, JoinPolicy *jp) :ReqAgents(),cooldown((int)0),numCoalition((int)-1) ,mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting) 
{    
}

//Destructor
Party::~Party(){
  if (mJoinPolicy) { delete mJoinPolicy; }
}

//Copy constructor
Party::Party(const Party &other) :ReqAgents(),cooldown(other.cooldown),numCoalition(other.numCoalition),mId(other.mId),mName(other.mName),mMandates(other.mMandates),mJoinPolicy(),mState(other.mState){
    if(other.mJoinPolicy->check()=="M" ){
        mJoinPolicy = new MandatesJoinPolicy();
    }
    else
    {
        mJoinPolicy = new LastOfferJoinPolicy();
    }
    for (int i=0; i<(int)other.ReqAgents.size(); i++) 
        ReqAgents.push_back(other.ReqAgents[i]); 
}

//copy assignment operator
Party& Party:: operator=(const Party &other){
if(this!=&other){
   if(mJoinPolicy){
    delete mJoinPolicy;
   }
    mId=other.mId;
    mName=other.mName;
    mMandates=other.mMandates;
    if(other.mJoinPolicy->check()=="M" ){
        mJoinPolicy = new MandatesJoinPolicy();
    }
    else
    {
        mJoinPolicy = new LastOfferJoinPolicy();
    }
    mState=other.mState;
    cooldown=other.cooldown;
    numCoalition=other.numCoalition;
    for (int i=0; i<(int)other.ReqAgents.size(); i++) 
        ReqAgents.push_back(other.ReqAgents[i]); 
}
    return *this;
}


//move_constructor
Party::Party(Party &&other):ReqAgents(other.ReqAgents),cooldown(other.cooldown),numCoalition(other.numCoalition), mId(other.mId) , mName(other.mName) , mMandates(other.mMandates),mJoinPolicy(other.mJoinPolicy),mState(other.mState) 
{
    other.mJoinPolicy = nullptr;
}
//move assignment operator
Party& Party:: operator=(Party &&other){
    if (mJoinPolicy) delete mJoinPolicy;
    ReqAgents = other.ReqAgents;
    cooldown=other.cooldown;
    numCoalition=other.numCoalition;
    mId=other.mId;
    mName=other.mName;
    mMandates=other.mMandates;
    mJoinPolicy = other.mJoinPolicy;
    mState=other.mState;
    other.mJoinPolicy = nullptr;
    
   return *this;
}



State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

int Party::getMandates() const
{
    return mMandates;
}

const string & Party::getName() const
{
    return mName;
}



void Party::step(Simulation &s){

    //Check the Party state;
    if(ReqAgents.size()!=0){ this->setState(CollectingOffers); cooldown =cooldown+1;}

    else if (this->getState()==CollectingOffers && cooldown<3){
        cooldown= cooldown+1;
    }

    if(cooldown==3){

        if(mJoinPolicy->check()=="M"){
            Max_val(s);
        }
        else{
            Last_val(s);
        }
    }
}
//Puah the Max_val;
void Party:: Max_val(Simulation &s){
    int Party_first_Numcoalition= s.getGraph().getParty(ReqAgents.at(0).getPartyId()).numCoalition;

    int Max_Mandat = totalMandat(s,Party_first_Numcoalition);
    Agent Max_Agent=ReqAgents.at(0);
    for(int i=1; i<(int) ReqAgents.size();i++){
        int sum = totalMandat(s,s.getGraph().getParty(ReqAgents.at(i).getPartyId()).numCoalition);
        if(Max_Mandat < sum ){
            Max_Mandat =sum;
            Max_Agent = ReqAgents.at(i);
        }
    }
    int curr = mId;
    //Agent(clone)
    Agent clone_agent = Agent(Max_Agent,s,curr); //New pointer
    s.Add_agent(clone_agent,Max_Agent.getPartyId(),mId);
    
    
    //State(Joined), coalition(id);
    this->setState(Joined);
    Push_coalition(s,Max_Agent,curr);
}

//Push the Last_Val
void Party:: Last_val(Simulation &s){
    Agent Max_Agent =ReqAgents.at((int)ReqAgents.size()-1); //Check push_back - if the last;
    int curr = mId;
    //Agent(clone)
    Agent clone_agent = Agent(Max_Agent,s,curr); //New pointer
    s.Add_agent(clone_agent,Max_Agent.getPartyId(),mId);
    //State(Joined), coalition(id);
    this->setState(Joined);
    Push_coalition(s,Max_Agent,curr);
}
bool Party::arrangeReq(Simulation &s,Agent & offer) const{
    int numOfCoaltions=s.coalitions.size();
    int checkOffer=s.getGraph().getParty(offer.getPartyId()).numCoalition;
    
    vector<int> curr;
    for(int i=0;i<numOfCoaltions;i++){curr.push_back(0);}
    for(int i=0;i<(int)ReqAgents.size();i++){
        int number=s.getGraph().getParty(ReqAgents.at(i).getPartyId()).numCoalition;
        if(curr[number]==0){
            curr[number]=1;
        }


    }
    if(curr[checkOffer]==0){
        return true;
    }
    return false;

}
void Party::Push_coalition(Simulation &s , Agent &Max_Agent,int partyId){
    bool check = true;
    int id=Max_Agent.getPartyId();
    for(int i=0;i<(int)s.coalitions.size() ;i++){
        if (check){
        for(int j=0;j<(int)s.coalitions[i].size();j++){
            if(check){
            if((s.coalitions.at(i).at(j))==id){s.coalitions.at(i).push_back(partyId); check=false;numCoalition=i;}
        }
        }
        }
    }

}
int Party::totalMandat(Simulation &s,int numCoalition2){
    int total=0;
    for(int i=0;i<(int)s.coalitions[numCoalition2].size();i++){
        int Party_id = s.coalitions.at(numCoalition2).at(i);
        total=total+s.getGraph().getMandates(Party_id);
    }
    return total;
}

