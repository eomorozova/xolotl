// Fast Calcium CONDUCTANCE
// http://jn.physiology.org/content/94/1/590.short
#ifndef CATPD
#define CATPD
#include "conductance.hpp"

//inherit conductance class spec
class CaTPD: public conductance {

public:

    // specify parameters + initial conditions
    CaTPD(double gbar_, double E_, double m_, double h_)
    {
        gbar = gbar_;
        E = E_;
        m = m_;
        h = h_;

        p = 3;
        q = 1;

        is_calcium = true;

        // defaults
        if (isnan(gbar)) { gbar = 0; }
        if (isnan (E)) { E = 50; }

        name = "CaTPD";

    }

    double m_inf(double, double);
    double h_inf(double, double);
    double tau_m(double, double);
    double tau_h(double, double);
    
};


double CaTPD::m_inf(double V, double Ca) {return 1.0/(1.0 + exp((V+25)/-7.2));}
double CaTPD::h_inf(double V, double Ca) {return 1.0/(1.0 + exp((V+36)/7));}
double CaTPD::tau_m(double V, double Ca) {return 55 - 49.5/(1.0 + exp(-(V+58)/17));}
double CaTPD::tau_h(double V, double Ca) {return 350 - 300/(1.0 + exp(-(V+50.0)/16.9));}

#endif
