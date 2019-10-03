

%
% ### rheobase
%
%
% **Syntax**
%
% ```matlab
% I = x.rheobase
% I = x.rheobase('PropertyName', PropertyValue, ...)
% I = x.rheobase(options)
% ```
%
% **Description**
%
% Finds the minimum injected current required to cause a xolotl model to .
% The model is simulated with increasing amounts of constant injected current until one spike is elicited.
% This minimum amount of current is called the rheobase.
% The output `I` contains the current magnitude needed to cause the model to spike,
%
% If called without arguments and one output, a struct
% containing fields for all optional arguments, `options`,
% is returned.
%
% Otherwise, the first argument should be a xolotl object,
% and the latter should be either name, value keyword pairs,
% or a struct to specify options.
% Options with a `NaN` value are ignored, and the default is used instead.
%
% | Option Name | Default Value | Units |
% | ----------- | ------------- | ----- |
% | `I_min` | -0.2 | nA |
% | `I_max` | 4 | nA |
% | `SpikeThreshold` | 0 | mV |
% | `t_end` | 10e3 | ms |
%
%
%
% !!! info "See Also"
%     xtools.V2metrics
%     xtools.findNSpikes
%     xtools.findNSpikeTimes
%     xolotl.fI
%

function I = rheobase(self, varargin)

% options and defaults
options.I_min = -2;
options.I_max = 4;
options.SpikeThreshold = 0;
options.t_end = 10e3;


% validate and accept options
options = corelib.parseNameValueArguments(options, varargin{:});

% save the initial state
self.reset;
self.snapshot('rheobase');


I = fminbnd(@(y) nSpikesForCurrent(self,y) ,options.I_min,options.I_max);



function N = nSpikesForCurrent(x, I_ext)

	x.reset('rheobase');
	x.I_ext = I_ext;

	x.closed_loop = true;
	x.integrate;
	V = x.integrate;

	N = xtools.findNSpikes(V(:,1)) - 1;
	if N < 0
		N = abs(I_ext);
	end

end


end