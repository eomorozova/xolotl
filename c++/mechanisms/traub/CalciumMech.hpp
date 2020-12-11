// _  _ ____ _    ____ ___ _
//  \/  |  | |    |  |  |  |
// _/\_ |__| |___ |__|  |  |___
//
// CalciumMech mechanism
// as in Traub et al 1991
// https://www.physiology.org/doi/pdf/10.1152/jn.1991.66.2.635

#ifndef CALCIUMMECH
#define CALCIUMMECH
#include "mechanism.hpp"
#include <limits>


//inherit controller class spec
class CalciumMech: public mechanism {

protected:
public:


    // parameters for calciumMech1
    double tau_Ca = 13.33;  // milliseconds

    // parameter to convert from i_Ca to uM
    double f = 5941;

    // specify parameters + initial conditions for
    // mechanism that controls a conductance
    CalciumMech(double tau_Ca_, double f_)
    {
        f = f_;
        tau_Ca = tau_Ca_;

        controlling_class = "unset";

    }

    void checkSolvers(int);

    void integrate(void);
    void integrateMS(int, double, double);

    double Cadot(double);

    void connectCompartment(compartment*);

    string getClass(void);


};

string CalciumMech::getClass() {
    return "CalciumMech";
}



// connection methods
void CalciumMech::connectCompartment(compartment* comp_) {
    comp = comp_;
    comp->addMechanism(this);
}



double CalciumMech::Cadot(double Ca_) {
    return -f * (comp->i_Ca) * (comp->A) - Ca_/tau_Ca;
}

void CalciumMech::integrate(void) {
    double Ca = comp->Ca_prev;
    Ca = Ca + dt * Cadot(Ca);
    comp->Ca = Ca;

}

// Runge-Kutta 4 integrator
void CalciumMech::integrateMS(int k, double V, double Ca_) {
    if (k == 4){return;}

    comp->k_Ca[k] = dt*(Cadot(Ca_));
    // mexPrintf("k_Ca[k] = %f\n", comp->k_Ca[k]);
}

void CalciumMech::checkSolvers(int k) {
    if (k == 0){
        return;
    } else if (k == 4){
        return;
    } else {
        mexErrMsgTxt("[CalciumMech] unsupported solver order\n");
    }
}



#endif
