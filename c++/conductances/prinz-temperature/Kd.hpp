// _  _ ____ _    ____ ___ _
//  \/  |  | |    |  |  |  |
// _/\_ |__| |___ |__|  |  |___
//
// component info: temperature-sensitive inward Potassium
// component source [Prinz et al. 2003](http://jn.physiology.org/content/jn/90/6/3998.full.pdf)
//
#ifndef KD
#define KD
#include "conductance.hpp"

//inherit conductance class spec
class Kd: public conductance {

private: 
    double delta_temp = 0;
    double pow_Q_tau_m_delta_temp = 1;
    double pow_Q_g = 1;


public:


    double Q_g;
    double Q_tau_m;

    //specify both gbar and erev and initial conditions
    Kd(double gbar_, double E_, double m_, double Q_g_, double Q_tau_m_)
    {
        gbar = gbar_;
        E = E_;
        m = m_;

        Q_g = Q_g_;
        Q_tau_m = Q_tau_m_;

        // defaults 
        if (isnan(gbar)) { gbar = 0; }
        
        if (isnan (Q_g)) { Q_g = 1; }
        if (isnan (Q_tau_m)) { Q_tau_m = 2; }
        if (isnan (E)) { E = -80; }

        p = 4;

        name = "Kd";

    }

    void integrate(double, double);
    void integrateLangevin(double, double);
    void init(void);

    double m_inf(double, double);
    double tau_m(double, double);
    

};




void Kd::init() {
    conductance::init();
    // also set up some useful things
    delta_temp = (temperature - temperature_ref)/10;
    pow_Q_tau_m_delta_temp = 1/(pow(Q_tau_m, delta_temp));
    pow_Q_g = pow(Q_g, delta_temp);
}


void Kd::integrate(double V, double Ca) {
    conductance::integrate(V,Ca);
    g = pow_Q_g*g;
}

void Kd::integrateLangevin(double V, double Ca) {
    conductance::integrateLangevin(V,Ca);
    g = pow_Q_g*g;
}


double Kd::m_inf(double V, double Ca) {return 1.0/(1.0+exp((V+12.3)/-11.8));}
double Kd::tau_m(double V, double Ca) {return (pow_Q_tau_m_delta_temp)*(14.4 - 12.8/(1.0+exp((V+28.3)/-19.2)));}


#endif
