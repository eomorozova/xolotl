% 
%        __ _ _   
% __  __/ _(_) |_ 
% \ \/ / |_| | __|
%  >  <|  _| | |_ 
% /_/\_\_| |_|\__|
%                 
% 
% ### show
% 
% **Syntax**
% 
% ```matlab
% xf.show()
% ```
% 
% **Description**
% 
% Assuming `xf` is a `xfit` object, and you have run the xfit
% algorithm many times and run `xf.save`, and you have been
% saving results to a `.xfit` file, then this method runs
% the user-defined `ShowFcn` and goes over all the results
% If `ShowFcn` is not defined, then it simply plots the result
% 
% See Also:
% xfit.evaluate
%     * [How to fit a xolotl model](https://xolotl.readthedocs.io/en/master/how-to/fit-parameters/)

function show(self)


if isempty(self.SaveParameters)
	return
end



hash = hashlib.md5hash([self.SaveParameters{:}]);

% get the results
savename = [hash '.xfit'];
if exist(savename,'file') == 2
	load(savename,'-mat')
else
	error('No results saved!')
end

self.SimFcnHash = hashlib.md5hash(which(func2str(self.SimFcn)),'file');


% more than one SimFcnHash, needs to be recomputed
disp('Recomputing costs...')
for i = 1:length(SimFcnHash)

	corelib.textbar(i,length(SimFcnHash))

	if SimFcnHash(i) == self.SimFcnHash
		continue
	end

	SimFcnHash(i) = self.SimFcnHash;

	self.x.set(self.SaveParameters,params(i,:))

	cost(i) = self.evaluate(self.x.get(self.parameter_names));



end

% save it...
save(savename,'cost','SimFcnHash','-append')


[~,idx] = sort(cost,'ascend');

for i = 1:length(cost)

	self.x.set(self.SaveParameters,params(idx(i),:))

	if ~isempty(self.ShowFcn)
		self.ShowFcn(self.x)
	else
		self.x.integrate;
		self.x.plot()
	end

	title(['Cost =  ' strlib.oval(cost(idx(i)))])

	self.evaluate(self.x.get(self.parameter_names));

	drawnow;


	pause(.5)

end
