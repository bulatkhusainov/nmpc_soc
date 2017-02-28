%% this part is problem dependent
% define integrator Butcher table
if exist('design','var') && any(strcmp('Integrator',fieldnames(design)))
    if design.Integrator == 1
        butcher_table_A = [0]; % Euler integrator
        butcher_table_beta =  [1];
    elseif design.Integrator == 2
        butcher_table_A = [ 0 0; 0.5 0.5]; % Trapezoidal integrator
        butcher_table_beta =  [0.5; 0.5];
    elseif design.Integrator == 3
        butcher_table_A = [0 0 0; 5/24 1/3 -1/24; 1/6 2/3 1/6]; % Simpson integrator
        butcher_table_beta =  [1/6; 2/3; 1/6];
    end
else
    %butcher_table_A = [0]; % Euler integrator
    %butcher_table_beta =  [1];
    butcher_table_A = [ 0 0; 0.5 0.5]; % Trapezoidal integrator
    butcher_table_beta =  [0.5; 0.5];
    %butcher_table_A = [0 0 0; 5/24 1/3 -1/24; 1/6 2/3 1/6]; % Simpson integrator
    %butcher_table_beta =  [1/6; 2/3; 1/6];   
end;

%heterogeneity = 0;
if exist('design','var') && any(strcmp('heterogeneity',fieldnames(design))); heterogeneity = design.heterogeneity; else heterogeneity = 1; end;
x_init = [0.5;0];
Tsim = 1;
MINRES_prescaled = 1;
d_type = 'float';
IP_iter = 20;
MINRES_iter = 'n_linear';
PAR =4;
if exist('design','var') && any(strcmp('N',fieldnames(design))); N = design.N; else N = 10; end;
if exist('design','var') && any(strcmp('Ts',fieldnames(design))); Ts = design.Ts; else Ts = 0.1; end;
n_stages = size(butcher_table_A,1); % number of integrator stages per node
n_states = 2;
m_inputs = 1;
n_node_slack = 1;
n_node_slack_eq = 1;
n_term_slack = 1;
n_term_eq = 1;
n_node_theta = n_states + m_inputs + n_node_slack + n_stages*n_states;
n_term_theta = n_states + n_term_slack;
n_node_eq = n_states*(n_stages+1) + n_node_slack_eq;


node_theta = sym('node_theta',[n_node_theta 1]);
x = node_theta(1:n_states);
u = node_theta(n_states+1:n_states+m_inputs);
s = node_theta(n_states+m_inputs+1:n_states+m_inputs+n_node_slack);
r = node_theta(n_states+m_inputs+n_node_slack+1: n_states+m_inputs+n_node_slack+n_stages*n_states); % integrator intermediate steps
term_theta = sym('term_theta',[n_term_theta 1]);
term_x = term_theta(1:n_states);
term_s = term_theta(n_states+1:n_states+n_term_slack);

% define objective (function of x,u,s)
node_objective_residual = sqrt(Ts)*[ sqrt(1)*((x(1))); 
                                     sqrt(1)*(x(2)); 
                                     sqrt(0.001)*(s(1));]; % least squares format
term_objective_residual = [sqrt(1)*(term_x(1)); 
                           sqrt(1)*(term_x(2))]; % least squares format

% define ode (function of x,u)
ode(1) = (1-x(2)^2)*x(1) - x(2) + u(1);
ode(2) = x(1);
%ode(1) = x(2);
%ode(2) = u(1);

% define equality constraints with slack variables (function of x,u,s)
%f_slack = [];
f_slack = sym(zeros(n_node_slack_eq,1));
f_slack(1) = u(1)- s(1) ;


%term_f = [];
term_f = sym(zeros(n_term_eq,1));
term_f(1) = term_x(1) - term_s(1);


% define bounds on x,u,s
% bound indeces [x' u' s']'
upper_bounds_indeces = [3]-1; % in C format
lower_bounds_indeces = [3]-1; % in C format
upper_bounds = [ 0.5];
lower_bounds = [ -0.5];

n_upper_bounds = max(size(upper_bounds_indeces));
n_lower_bounds = max(size(lower_bounds_indeces));
n_bounds = n_upper_bounds + n_lower_bounds;

% optimization problem dimensions
n_all_theta = n_node_theta*N + n_term_theta;
n_all_nu = n_node_eq*N + n_term_eq+n_states;
n_all_lambda = n_bounds*N;
n_linear = n_all_theta+n_all_nu;

% simulation data (calculate the required number of calculations)
N_sim_full = floor(Tsim/Ts);
Tsim_last = Tsim - N_sim_full*Ts;

% parallelization/pipelining data
part_size = ceil(N/PAR);
PAR = floor(N/part_size);
rem_partition = N - PAR*part_size;
ii_required = 1;

% save the workspace
save problem_data

