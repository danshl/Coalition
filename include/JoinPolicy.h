#pragma once

class JoinPolicy { 
    public: 
    virtual string check()=0;
    virtual ~JoinPolicy() = default;
};

class MandatesJoinPolicy : public JoinPolicy { 
    public: 
    virtual string check();
    ~MandatesJoinPolicy();
};

class LastOfferJoinPolicy : public JoinPolicy {
    public:
    virtual string check();
    ~LastOfferJoinPolicy();
};