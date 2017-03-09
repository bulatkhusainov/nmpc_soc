#include "user_protoip_definer.h"
#include "user_main_header.h"

// this function evaluates node gradient 
void node_gradient_eval(float node_gradient[n_node_theta],float node_theta[n_node_theta])
{
	node_gradient[0] =   node_theta[1-1]*2.0;
	node_gradient[1] =   node_theta[2-1]*2.0E-4;
	node_gradient[2] =   node_theta[3-1]*2.0;
	node_gradient[3] =   node_theta[4-1]*2.0E-4;
	node_gradient[4] =   node_theta[5-1]*2.0;
	node_gradient[5] =   node_theta[6-1]*2.0E-4;
	node_gradient[6] =   node_theta[7-1]*2.0E-5;
	node_gradient[7] =   node_theta[8-1]*2.0E-5;
	node_gradient[8] =   0.0;
	node_gradient[9] =   0.0;
	node_gradient[10] =   0.0;
	node_gradient[11] =   0.0;
	node_gradient[12] =   0.0;
	node_gradient[13] =   0.0;
	node_gradient[14] =   0.0;
	node_gradient[15] =   0.0;
	node_gradient[16] =   0.0;
	node_gradient[17] =   0.0;
	node_gradient[18] =   0.0;
	node_gradient[19] =   0.0;
	node_gradient[20] =   0.0;
}

// this function evaluates terminal gradient 
void term_gradient_eval(float term_gradient[n_term_theta],float term_theta[n_term_theta])
{
	term_gradient[0] =   term_theta[1-1]*2.0E1;
	term_gradient[1] =   term_theta[2-1]*(1.0/5.0E2);
	term_gradient[2] =   term_theta[3-1]*2.0E1;
	term_gradient[3] =   term_theta[4-1]*(1.0/5.0E2);
	term_gradient[4] =   term_theta[5-1]*2.0E1;
	term_gradient[5] =   term_theta[6-1]*(1.0/5.0E2);
	term_gradient[6] =   0.0;
}
