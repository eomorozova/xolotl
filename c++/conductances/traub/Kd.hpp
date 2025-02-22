// _  _ ____ _    ____ ___ _
//  \/  |  | |    |  |  |  |
// _/\_ |__| |___ |__|  |  |___
//
// delayed rectifier
// Traub et al. 1991
// https://www.researchgate.net/publication/21491281_A_Model_of_CA3_Hippocampal_Pyramidal_Neuron_Incorporating_Voltage-Clamp_Data_on_Intrinsic_Conductances

#ifndef KD
#define KD
#include "conductance.hpp"

//inherit conductance class spec
class Kd: public conductance {

public:

    // specify parameters + initial conditions
    Kd(double gbar_, double E_, double m_)
    {
        gbar = gbar_;
        E = E_;
        m = m_;

        p = 4;


        // defaults
        if (isnan(gbar)) { gbar = 0; }        
        if (isnan (E)) { E = -80; }

        name = "Kd";
    }

    double m_inf(double, double);
    double tau_m(double, double);
    

};


double Kd::m_inf(double V, double Ca) {return (0.016*(35.1-V)/(exp((35.1-V)/5.0)-1.0))/((0.016*(35.1-V)/(exp((35.1-V)/5.0)-1.0))+(0.25*exp((20.0-V)/40.0))); }
double Kd::tau_m(double V, double Ca) {return 1.0/((0.016*(35.1-V)/(exp((35.1-V)/5.0)-1.0))+(0.25*exp((20.0-V)/40.0)));}


#endif
