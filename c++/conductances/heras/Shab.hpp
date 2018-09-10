// _  _ ____ _    ____ ___ _
//  \/  |  | |    |  |  |  |
// _/\_ |__| |___ |__|  |  |___
//
// Potassium Conductance
// https://www.biorxiv.org/content/biorxiv/early/2018/06/13/344325.full.pdf
// Francisco J. H. Heras, Mikko Vahasoyrinki, and Jeremy E. Niven 2018
#ifndef SHAB
#define SHAB
#include "conductance.hpp"

//inherit conductance class spec
class Shab: public conductance {

public:


    //specify both gbar and erev and initial conditions
    Shab(double g_, double E_, double m_, double h_)
    {
        gbar = g_;
        E = E_;
        m = m_;
        h = h_;

        // defaults
        if (isnan(gbar)) { gbar = 0; }
        if (isnan (m)) { m = 0; }
        if (isnan (h)) { h = 1; }
        if (isnan (E)) { E = -80; }

    }

    void integrate(double, double);

    double m_inf(double, double);
    double h_inf(double, double);
    double tau_m(double, double);
    double tau_h(double, double);
    string getClass(void);

};

string Shab::getClass(){return "Shab";}

void Shab::integrate(double V, double Ca)
{
    m = m_inf(V,Ca) + (m - m_inf(V,Ca))*exp(-dt/tau_m(V,Ca));
    h = 0.7 * (h_inf(V,Ca) + (h - h_inf(V,Ca))*exp(-dt/tau_h(V,Ca))) + (1 - 0.7) * (h_inf(V,Ca) + (h - h_inf(V,Ca))*exp(-dt/3000.0));
    g = gbar*m*m*h;
}


double Shab::m_inf(double V, double Ca) {return (1.0/(1.0+exp(sqrt((-1.0-V)/9.1))));}
double Shab::tau_m(double V, double Ca) {return 1.0/(0.116*exp((-V-25.7)/32.2)+0.00659*(-V-23.8)/(exp((-V-23.8)/1.35)-1.0));}
double Shab::h_inf(double V, double Ca) {return 1.0/(1.0+exp((25.7+V)/6.4));}
double Shab::tau_h(double V, double Ca) {return 335.0*exp(V/71.3)+73.2;}


#endif
