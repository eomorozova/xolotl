// _  _ ____ _    ____ ___ _    
//  \/  |  | |    |  |  |  |    
// _/\_ |__| |___ |__|  |  |___ 
//
// Persisent Sodium
// http://jn.physiology.org/content/94/1/590.short
#ifndef NAP
#define NAP
#include "../../conductance.hpp"

//inherit conductance class spec
class NaP: public conductance {

public:

    // specify parameters + initial conditions 
    NaP(double g_, double E_, double m_, double h_, double Q_g_, double Q_tau_m_, double Q_tau_h_)
{
    gbar = g_;
    E = E_;
    m = m_;
    h = h_;
    

    Q_g = Q_g_;
    Q_tau_m = Q_tau_m_;
    Q_tau_h = Q_tau_h_;
}
    
    void integrate(double V, double Ca, double dt, double delta_temp);
    void connect(compartment *pcomp_);
    double m_inf(double V);
    double h_inf(double V);
    double tau_m(double V);
    double tau_h(double V); 
};

void NaP::connect(compartment *pcomp_) {container = pcomp_; }

void NaP::integrate(double V, double Ca, double dt, double delta_temp)
{
    m = m_inf(V) + (m - m_inf(V))*exp(-(dt*pow(Q_tau_m, delta_temp))/tau_m(V));
    h = h_inf(V) + (h - h_inf(V))*exp(-(dt*pow(Q_tau_h, delta_temp))/tau_h(V));
    g = pow(Q_g, delta_temp)*gbar*m*m*m*h;
}

double NaP::m_inf(double V) {return 1.0/(1.0+exp(-(V+26.8)/8.2));}
double NaP::h_inf(double V) {return 1.0/(1.0+exp((V+48.5)/4.8));}
double NaP::tau_m(double V) {return 19.8 - 10.7/(1+exp(-(V+26.5)/8.6));}
double NaP::tau_h(double V) {return 666 - 379/(1+exp(-(V+33.6)/11.7));}

#endif
