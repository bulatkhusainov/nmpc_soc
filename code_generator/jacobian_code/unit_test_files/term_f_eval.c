#include "mex.h"
#include "matrix.h"

#include "../../../src/user_main_header.h"
#include "../../../src/user_jacobians.c"



void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[])
{
	int i,j,k;
	double *term_f_double, *term_theta_double;
	
	// interface input matrix
	term_theta_double = mxGetPr(prhs[0]);
	//n = mxGetN(prhs[0]);
	
	// interface output matrix
	plhs[0] = mxCreateDoubleMatrix(n_term_eq,1,mxREAL);
	term_f_double = mxGetPr(plhs[0]);

	// local input and output matrices
	float term_theta[n_term_theta];
	float term_f[n_term_eq] = {0};

	// input interface loop
	for(i = 0; i < n_term_theta; i++)
	{
		term_theta[i] = (float) term_theta_double[i];
	}

	//call function
	term_f_eval(term_f,term_theta);
	
	//output interface loop
	for(i = 0; i < n_term_eq; i++)
	{
		term_f_double[i] = (double) term_f[i];
	}
}
