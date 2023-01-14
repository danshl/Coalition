#include "../include/Simulation.h"
#include "../include/SelectionPolicy.h"
#include "../include/Party.h"

string MandatesSelectionPolicy::check1(){
    return "M";
}
string EdgeWeightSelectionPolicy::check1(){
    return "E";
}

MandatesSelectionPolicy::~MandatesSelectionPolicy(){
}

EdgeWeightSelectionPolicy::~EdgeWeightSelectionPolicy(){
}

