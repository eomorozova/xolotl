// _  _ ____ _    ____ ___ _
//  \/  |  | |    |  |  |  |
// _/\_ |__| |___ |__|  |  |___
//
// H current. again, for mysterious reasons, the compiler
// won't let me call this class "H"
// http://www.jneurosci.org/content/jneuro/18/7/2309.full.pdf
#ifndef HCURRENT
#define HCURRENT
#include "conductance.hpp"
//inherit conductance class spec
class HCurrent: public conductance {

private: 
    double delta_temp = 0;
    double pow_Q_tau_m_delta_temp = 1;
    double pow_Q_g = 1;


public:

    double Q_g;
    double Q_tau_m;
    double Q_tau_h;

    //specify both gbar and erev and initial conditions
    HCurrent(double gbar_, double E_, double m_, double Q_g_, double Q_tau_m_)
    {
        gbar = gbar_;
        E = E_;
        m = m_;


        Q_g = Q_g_;
        Q_tau_m = Q_tau_m_;

        // defaults 
        if (isnan(gbar)) { gbar = 0; }
        
        
        if (isnan (Q_g)) { Q_g = 1; }
        if (isnan (Q_tau_m)) { Q_tau_m = 2; }
        if (isnan (E)) { E = -20; }

        name = "HCurrent";
    }

    void integrate(double, double);
    void integrateLangevin(double, double);

    void connect(compartment*);

    double m_inf(double, double);
    double tau_m(double, double);
    

};


void HCurrent::connect(compartment *pcomp_) {
    // call super class method
    conductance::connect(pcomp_);

    // also set up some useful things

    delta_temp = (temperature - temperature_ref)/10;
    pow_Q_tau_m_delta_temp = 1/(pow(Q_tau_m, delta_temp));
    pow_Q_g = pow(Q_g, delta_temp);
}


void HCurrent::integrateLangevin(double V, double Ca) {
    conductance::integrateLangevin(V,Ca);
    g = pow_Q_g*g;
}


void HCurrent::integrate(double V, double Ca) {
    conductance::integrate(V,Ca);
    g = pow_Q_g*g;
}



double HCurrent::m_inf(double V, double Ca) {return 1.0/(1.0+exp((V+70.0)/6.0));}
double HCurrent::tau_m(double V, double Ca) {return pow_Q_tau_m_delta_temp*((272.0 + 1499.0/(1.0+exp((V+42.2)/-8.73))));}

#endif
