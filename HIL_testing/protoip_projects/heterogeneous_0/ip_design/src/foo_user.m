%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% icl::protoip
% Author: asuardi <https://github.com/asuardi>
% Date: November - 2014
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


function [y_out_out_int] = foo_user(project_name,block_in_int, x_in_in_int)


	% load project configuration parameters: input and output vectors (name, size, type, NUM_TEST, TYPE_TEST)
	load_configuration_parameters(project_name);

	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	% compute with Matlab and save in a file simulation results y_out_out_int
	for i=1:Y_OUT_OUT_LENGTH
		y_out_out_int(i)=0;
		for i_block = 1:BLOCK_IN_LENGTH
			y_out_out_int(i)=y_out_out_int(i) + block_in_int(i_block);
		end
		for i_x_in = 1:X_IN_IN_LENGTH
			y_out_out_int(i)=y_out_out_int(i) + x_in_in_int(i_x_in);
		end
	end

end

