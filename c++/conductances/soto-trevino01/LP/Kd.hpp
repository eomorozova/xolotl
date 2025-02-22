// _  _ ____ _    ____ ___ _
//  \/  |  | |    |  |  |  |
// _/\_ |__| |___ |__|  |  |___
//
// potassium conductance
// https://www.nature.com/articles/nn0301_297#methods
// Soto-Trevino et al. 2001

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

        p = 1;
         // defaults
        if (isnan(gbar)) { gbar = 0; }
        if (isnan (E)) { E = -80; }

        name = "Kd";
    }

    double m_inf(double, double);
    double tau_m(double, double);
    

};



double Kd::m_inf(double V, double Ca) {return (0.5)*(1.0+tanh((V)+10.0)/20.0);}
double Kd::tau_m(double V, double Ca) {return 1.0 / ( 0.008*cosh((V)/30.0) );}


#endif
