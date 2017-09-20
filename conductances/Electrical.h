// One-way electrical Synapse 
// For symmetric electrical synapses, connect two copies
// of this in opposite polarities 
#ifndef ELECTRICAL
#define ELECTRICAL
#include "../synapse.h"

class Electrical: public synapse {

public:

    // specify parameters + initial conditions 
    Electrical(double g_)
    {
        gbar = g_;
    }
    
    void integrate(double dt);
    void connect(compartment *pcomp1_, compartment *pcomp2_);
    double getCurrent(double V_post);
};

void Electrical::integrate(double dt)
{       
    // do nothing
}

double Electrical::getCurrent(double V_post)
{   
    double V_pre = pre_syn->V;
    double I_out = gbar*(V_post-V_pre)/1000.0; // in units of nA
    return I_out;

}

void Electrical::connect(compartment *pcomp1_, compartment *pcomp2_) 
{
    pre_syn = pcomp1_; 
    post_syn = pcomp2_; 

    // tell the post-synaptic cell that we're connecting to it
    post_syn->addSynapse(this);
}

#endif
