// _  _ ____ _    ____ ___ _
//  \/  |  | |    |  |  |  |
// _/\_ |__| |___ |__|  |  |___
//
// HCurrent
// http://jn.physiology.org/content/94/1/590.short
#ifndef HCURRENT
#define HCURRENT
#include "conductance.hpp"

//inherit conductance class spec
class HCurrent: public conductance {

public:

    //specify both gbar and erev and initial conditions
    HCurrent(double gbar_, double E_, double m_)
    {
        gbar = gbar_;
        E = E_;
        m = m_;

        p = 1;

        
        // defaults
        if (isnan(gbar)) { gbar = 0; }
        if (isnan (E)) { E = -20; }

        name = "HCurrent";
    }

    double m_inf(double, double);
    double tau_m(double, double);

};



double HCurrent::m_inf(double V, double Ca) {return 1.0/(1.0+exp((V+70.0)/6.0));}
double HCurrent::tau_m(double V, double Ca) {return (272.0 + 1499.0/(1.0+exp((V+42.2)/-8.73)));}


#endif
