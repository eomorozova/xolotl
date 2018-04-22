// _  _ ____ _    ____ ___ _    
//  \/  |  | |    |  |  |  |    
// _/\_ |__| |___ |__|  |  |___ 
//
// Fast Calcium CONDUCTANCE
// http://jn.physiology.org/content/94/1/590.short
#ifndef CATAB
#define CATAB
#include "../../conductance.hpp"

//inherit conductance class spec
class CaTAB: public conductance {

public:

    // specify parameters + initial conditions 
    CaTAB(double g_, double E_, double m_, double h_)
    {
        gbar = g_;
        E = E_;
        m = m_;
        h = h_;

         // defaults
        if (isnan (m)) { m = 0; }
        if (isnan (h)) { h = 1; }
        if (isnan (E)) { E = 50; }
        
    }

    void integrate(double V, double Ca, double dt, double delta_temp);
    void connect(compartment *pcomp_);
    double m_inf(double V);
    double h_inf(double V);
    double tau_m(double V);
    double tau_h(double V); 
    string getClass(void);
};

string CaTAB::getClass(){return "CaTAB";}

void CaTAB::connect(compartment *pcomp_) { container = pcomp_; }

void CaTAB::integrate(double V, double Ca, double dt, double delta_temp)
{
    // update E by copying E_Ca from the cell 
    E = container->E_Ca;
    m = m_inf(V) + (m - m_inf(V))*exp(-dt/tau_m(V));
    h = h_inf(V) + (h - h_inf(V))*exp(-dt/tau_h(V));
    g = gbar*m*m*m*h;

    // compute the specific calcium current and update it in the cell 
    double this_I = g*(V-E);
    container->i_Ca += this_I;
}


double CaTAB::m_inf(double V) {return 1.0/(1.0 + exp((V+25)/-7.2));}
double CaTAB::h_inf(double V) {return 1.0/(1.0 + exp((V+36)/7));}
double CaTAB::tau_m(double V) {return 55 - 49.5/(1.0 + exp(-(V+58)/17));}
double CaTAB::tau_h(double V) {return 87.5 - 75/(1.0 + exp(-(V+50.0)/16.9));}

#endif
