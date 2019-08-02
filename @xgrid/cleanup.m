%
% __   ____ _ _ __(_) __| |
% \ \/ / _` | '__| |/ _` |
%  >  < (_| | |  | | (_| |
% /_/\_\__, |_|  |_|\__,_|
%      |___/
%
% ### cleanup
%
%
% **Syntax**
%
% ```matlab
% 	p.cleanup()
% ```
%
% **Description**
%
% Removes all auxiliary files generated by xgrid on all clusters
% and frees all workers.
%
% **Technical Details**
%
% All `.ppp` files will be erased on all clusters,
% and the local directory will be cleaned of `.error` files.
%
% See Also:
% xgrid.delete
% 

function cleanup(self)

do_folder = [self.xgrid_folder filesep 'do' filesep ];
doing_folder = [self.xgrid_folder filesep 'doing' filesep ];
done_folder = [self.xgrid_folder filesep 'done' filesep ];

% remove all .ppp files
allfiles = dir([do_folder '*.ppp']);
for i = 1:length(allfiles)
	delete(pathlib.join(allfiles(i).folder,allfiles(i).name))
end
allfiles = dir([doing_folder '*.ppp']);
for i = 1:length(allfiles)
	delete(pathlib.join(allfiles(i).folder,allfiles(i).name))
end
allfiles = dir([done_folder '*.ppp']);
for i = 1:length(allfiles)
	delete(pathlib.join(allfiles(i).folder,allfiles(i).name))
end

allfiles = dir([done_folder '*.ppp.data']);
for i = 1:length(allfiles)
	delete(pathlib.join(allfiles(i).folder,allfiles(i).name))
end

% destroy all error files
% in the current directory
[e,o]=system('rm *.error');

% wipe all files in the folder
allfiles = dir(self.xgrid_folder);
for i = 1:length(allfiles)
	[~,~,ext]=fileparts(allfiles(i).name);
	if strcmp(ext,'.mat')
		continue
	end
	if allfiles(i).isdir
		if strcmp(allfiles(i).name(1),'+') | strcmp(allfiles(i).name(1),'@')
			% class or package, destroy
			try
				rmdir([allfiles(i).folder filesep allfiles(i).name],'s')
			catch
			end
		end
		continue
	end
	try
		delete([allfiles(i).folder filesep allfiles(i).name])
	catch
	end
end


% destroy all workers
self.workers = [];

% cleanup all remotes
for i = 1:length(self.clusters)
	if strcmp(self.clusters(i).Name,'local')
		continue
	end
	self.tellRemote(self.clusters(i).Name,'cleanup');
end