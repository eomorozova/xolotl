// _  _ ____ _    ____ ___ _
//  \/  |  | |    |  |  |  |
// _/\_ |__| |___ |__|  |  |___
//
// component info: Sodium conductance
// component source [Prinz et al. 2003](http://jn.physiology.org/content/jn/90/6/3998.full.pdf)
//
#ifndef NAV
#define NAV

class conductance;

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
        if (isnan (E)) { E = 50; }

        p = 3;
        q = 1;

        name = "NaV";


        perm.Na = 1;

    }

    double m_inf(double, double);
    double h_inf(double, double);
    double tau_m(double, double);
    double tau_h(double, double);
    


};




double NaV::m_inf(double V, double Ca) {return 1.0/(1.0+exp((V+25.5)/-5.29));}
double NaV::h_inf(double V, double Ca) {return 1.0/(1.0+exp((V+48.9)/5.18));}
double NaV::tau_m(double V, double Ca) {return 2.64 - 2.52/(1+exp((V+120.0)/-25.0));}
double NaV::tau_h(double V, double Ca) {return (1.34/(1.0+exp((V+62.9)/-10.0)))*(1.5+1.0/(1.0+exp((V+34.9)/3.6)));}

#endif
