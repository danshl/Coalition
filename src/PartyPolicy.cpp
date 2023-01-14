#include "../include/Simulation.h"
#include "../include/JoinPolicy.h"
#include "../include/Party.h"

string MandatesJoinPolicy::check()
{
    return "M";
}

string LastOfferJoinPolicy::check(){
    return "L";
}

MandatesJoinPolicy::~MandatesJoinPolicy(){
}

LastOfferJoinPolicy::~LastOfferJoinPolicy(){
}