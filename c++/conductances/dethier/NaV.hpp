// _  _ ____ _    ____ ___ _
//  \/  |  | |    |  |  |  |
// _/\_ |__| |___ |__|  |  |___
//
// Sodium CONDUCTANCE
// Dethier, Drion, Franci, Sepulchre 2015
// https://www.ncbi.nlm.nih.gov/pmc/articles/PMC4620135/

#ifndef NAV
#define NAV
#include "conductance.hpp"

//inherit conductance class spec
class NaV: public conductance {

public:

    // specify parameters + initial conditions
    NaV(double gbar_, double E_, double m_, double h_)
    {
        gbar = gbar_;
        E = E_;
        m = m_;
        h = h_;

        // defaults
        if (isnan(gbar)) { gbar = 0; }
        
        
        if (isnan (E)) { E = 30; }


        p = 3;
        q = 1;

        name = "NaV";

    }

    double m_inf(double, double);
    double h_inf(double, double);
    double tau_m(double, double);
    double tau_h(double, double);


};



double NaV::m_inf(double V, double Ca) {return (1.0/(1.0+exp(((V)+35.5)/-5.29)));}
double NaV::h_inf(double V, double Ca) {return (1.0/(1.0+exp(((V)+48.9)/5.18)));}
double NaV::tau_m(double V, double Ca) {return 1.32- (1.26/(1.0+exp(((V)+120.0)/-25.0)));}
double NaV::tau_h(double V, double Ca) {return ((0.67)/(1.0+exp(((V)+62.9)/(-10.0))))*(1.5+(1.0/(1.0+exp(((V)+34.9)/3.6))));}


#endif
