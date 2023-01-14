#pragma once

class SelectionPolicy {
     public:
     virtual string check1()=0;
     virtual ~SelectionPolicy() =default;
 };

class MandatesSelectionPolicy: public SelectionPolicy{
    public: 
    virtual string check1();
    ~MandatesSelectionPolicy();
 };

class EdgeWeightSelectionPolicy: public SelectionPolicy{ 
    public: 
    virtual string check1();
    ~EdgeWeightSelectionPolicy();
};