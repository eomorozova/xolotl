// _  _ ____ _    ____ ___ _
//  \/  |  | |    |  |  |  |
// _/\_ |__| |___ |__|  |  |___
//
// Modulatory Input Conductance
// http://www.jneurosci.org/content/34/14/4963/tab-figures-data
// based on RPCH/proctolin recordings
#ifndef MICURRENT
#define MICURRENT
#include "conductance.hpp"

//inherit conductance class spec
class MICurrent: public conductance {

public:


    //specify both gbar and erev and initial conditions
    MICurrent(double gbar_, double E_, double m_)
    {
        gbar = gbar_;
        E = E_;
        m = m_;

        // defaults
        if (isnan (E)) { E = 30; }

        p = 1;

        name = "MICurrent";
    }

    double m_inf(double V, double Ca);
    double h_inf(double V, double Ca);
    double tau_m(double V, double Ca);
    double tau_h(double V, double Ca);
    

};



double MICurrent::m_inf(double V, double Ca) {return 1.0/(1.0+exp((V+12.0)/-5));}
double MICurrent::tau_m(double V, double Ca) {return 0.5;}
double MICurrent::h_inf(double V, double Ca) {return   0;}
double MICurrent::tau_h(double V, double Ca) {return   0;}

#endif
