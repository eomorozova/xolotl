// _  _ ____ _    ____ ___ _
//  \/  |  | |    |  |  |  |
// _/\_ |__| |___ |__|  |  |___
//
// Shaker current
// an inactivating K current in Drosophila
// first characterized here: http://www.sciencedirect.com/science/article/pii/089662739190255X

#ifndef SHAKER
#define SHAKER
#include "conductance.hpp"

//inherit conductance class spec
class Shaker: public conductance {

public:

    // specify parameters + initial conditions
    Shaker(double gbar_, double E_, double m_, double h_)
    {
        gbar = gbar_;
        E = E_;
        m = m_;
        h = h_;

        // defaults 
        if (isnan(gbar)) { gbar = 0; }
        if (isnan (E)) { E = -80; }

        p = 1;
        q = 1;

        name = "Shaker";

    }

    double m_inf(double, double);
    double h_inf(double, double);
    double tau_m(double, double);
    double tau_h(double, double);
    


};

double Shaker::m_inf(double V, double Ca) {return 1.0/(1.0+exp((V+62.8)/-8.2)); }
double Shaker::h_inf(double V, double Ca) {return 1.0/(1.0+exp((V+80.0)/5.23)); }
double Shaker::tau_m(double V, double Ca) {return 50.0 - 47.88/(1.0+exp((V+92.24)/-8.0));}
double Shaker::tau_h(double V, double Ca) {return 50;}

#endif
