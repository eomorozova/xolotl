// _  _ ____ _    ____ ___ _
//  \/  |  | |    |  |  |  |
// _/\_ |__| |___ |__|  |  |___
//
// Cell MCN1 Potassium Conductance
// http://www.jneurosci.org/content/18/13/5053
// Nadim 1998
#ifndef KD
#define KD
#include "conductance.hpp"

//inherit conductance class spec
class Kd: public conductance {

public:


    //specify both gbar and erev and initial conditions
    Kd(double gbar_, double E_, double m_)
    {
        gbar = gbar_;
        E = E_;
        m = m_;

        p = 4;


        // defaults
        if (isnan(gbar)) { gbar = 0; }
        if (isnan (E)) { E = 0; }

        name = "Kd";

    }

    double m_inf(double, double);
    double tau_m(double, double);
    

};



double Kd::m_inf(double V, double Ca) {return (1.0/(1.0+exp(-0.045*((V)+33.0))));}
double Kd::tau_m(double V, double Ca) {return (104.0/(1.0+exp(0.065*((V)+5.0))));}


#endif
