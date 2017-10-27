% tests a neuron that reproduces Fig 3 in Tim's paper

try
	x.cleanup;
	clear x
catch
end

vol = 1; % this can be anything, doesn't matter
f = 1.496; % uM/nA
tau_Ca = 200;
F = 96485; % Faraday constant in SI units
phi = (2*f*F*vol)/tau_Ca;
Ca_target = 7; % used only when we add in homeostatic control 

x = xolotl;
x.cleanup;
x.addCompartment('AB',-60,0.02,10,0.0628,vol,phi,3000,0.05,tau_Ca,Ca_target);

g0 = 1*rand(7,1);

x.addConductance('AB','liu/NaV',g0(1),30);
x.addConductance('AB','liu/CaT',g0(2),30);
x.addConductance('AB','liu/CaS',g0(3),30);
x.addConductance('AB','liu/ACurrent',g0(4),-80);
x.addConductance('AB','liu/KCa',g0(5),-80);
x.addConductance('AB','liu/Kd',g0(6),-80);
x.addConductance('AB','liu/HCurrent',g0(7),-20);
x.addConductance('AB','Leak',.99,-50);

tau_g = 5e3;

x.addIntegralController('AB','NaV',666,tau_g);
x.addIntegralController('AB','CaT',55555,tau_g);
x.addIntegralController('AB','CaS',45454,tau_g);
x.addIntegralController('AB','ACurrent',5000,tau_g);
x.addIntegralController('AB','KCa',1250,tau_g);
x.addIntegralController('AB','Kd',2000,tau_g);
x.addIntegralController('AB','HCurrent',125000,tau_g);


x.t_end = 100e3;
x.dt = 100e-3;
x.integrate;

x.t_end = 5e3;

if usejava('jvm')
	round(x.getConductances('AB'))'
	figure, hold on
	plot(x.integrate)
else
	st = xolotl.findSpikes(x.integrate);
	assert(length(st)>0,'Neuron did not spike')
	disp('Integral control test passed!')
end