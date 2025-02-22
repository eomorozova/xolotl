// _  _ ____ _    ____ ___ _
//  \/  |  | |    |  |  |  |
// _/\_ |__| |___ |__|  |  |___
//
// component info: mutant EAG channels that are inactivated by Calcium.
// mutant, less sensitive to Ca
// component source [Bronk et al. 2017](https://www.physiology.org/doi/10.1152/jn.00820.2017)

#ifndef EAGMUT
#define EAGMUT
#include "conductance.hpp"

//inherit conductance class spec
class EAGmut: public conductance {

public:

    // specify parameters + initial conditions
    EAGmut(double gbar_, double E_, double m_)
    {
        gbar = gbar_;
        E = E_;
        m = m_;

        // defaults
        if (isnan (E)) { E = -80; }

        name = "EAGmut";

        p = 1;

    }


    double m_inf(double V, double Ca);
    double tau_m(double, double);
    

};


double EAGmut::m_inf(double V, double Ca) { return (.92*(1-.05)/(Ca+.92) + .05)/(1.0+exp((V+23.12)/-16.94)); }
double EAGmut::tau_m(double V, double Ca) {return 5497 - 5500/(1.0+exp((V+251.5 )/-51.5));}

#endif
