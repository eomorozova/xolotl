// _  _ ____ _    ____ ___ _
//  \/  |  | |    |  |  |  |
// _/\_ |__| |___ |__|  |  |___
//
// Delayed Rectifier Potassium Conductance
// http://www.jneurosci.org/content/32/32/10995
// Kispersky, Caplan, Marder 2012
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

         // defaults
        if (isnan(gbar)) { gbar = 0; }        
        if (isnan (E)) { E = 0; }

        p = 3;

        name = "Kd";

    }

    double m_inf(double, double);
    double tau_m(double, double);
    

};



double Kd::m_inf(double V, double Ca) {return (1.0/(1.0+exp(((V)+12.3)/-11.8)));}
double Kd::tau_m(double V, double Ca) {return 7.2-(6.4/(1.0+exp(((V)+28.3)/-19.2)));}


#endif
