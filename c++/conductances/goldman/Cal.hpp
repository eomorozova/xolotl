// _  _ ____ _    ____ ___ _
//  \/  |  | |    |  |  |  |
// _/\_ |__| |___ |__|  |  |___
//
// Combined Fast and SLow Calcium Conductance
// http://www.jneurosci.org/content/21/14/5229.long
// Goldman, Golowasch, Marder, Abbott 2012
#ifndef CAL
#define CAL
#include "conductance.hpp"

//inherit conductance class spec
class Cal: public conductance {

public:


    //specify both gbar and erev and initial conditions
    Cal(double gbar_, double E_, double m_, double h_)
    {
        gbar = gbar_;
        E = E_;
        m = m_;
        h = h_;

         // defaults
        if (isnan(gbar)) { gbar = 0; }
        if (isnan (E)) { E = 0; }

        p = 3;
        q = 1;

        is_calcium = true;
        name = "Cal";

    }


    double m_inf(double, double);
    double h_inf(double, double);
    double tau_m(double, double);
    double tau_h(double, double);
    

};


double Cal::m_inf(double V, double Ca) {return (1.0/(1.0+exp(((V)+35.0)/-12.0)));}
double Cal::tau_m(double V, double Ca) {return 7.0+(0.4/(1.0+exp(((V)+70.0)/-15.0)));}
double Cal::h_inf(double V, double Ca) {return (1.0/(1.0+exp(((V)+40.0)/30.0)));}
double Cal::tau_h(double V, double Ca) {return 90.0;}


#endif
