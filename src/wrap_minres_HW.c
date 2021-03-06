#include "user_protoip_definer.h"
#include "user_main_header.h"
#include "user_nnz_header.h"
#include "user_structure_header.h"
#include "user_prototypes_header.h"


void wrap_minres_HW(float blocks[], float out_blocks[], float b[], float x_current[], float minres_data[])
{
	#if heterogeneity == 3

	int i,j,k;

	// interface structure
	part_matrix block_struct;
	d_type_lanczos out_blocks_casted[(N+1)*n_states];

	// pack matrix into structure
	k = 0;
	for(i = 0; i < PAR; i++)
		for(j = 0; j < part_size*nnz_block_tril; j++, k++) block_struct.mat[i][j] = blocks[k];
	#ifdef rem_partition		
		for(i = 0; i < rem_partition*nnz_block_tril; i++, k++) block_struct.mat_rem[i] = blocks[k];
	#endif
	for(i = 0; i < nnz_term_block_tril; i++, k++) block_struct.mat_term[i] = blocks[k];

	// cast out blocks to required precision
	for(i = 0; i < (N+1)*n_states; i++)
		out_blocks_casted[i] = (d_type_lanczos) out_blocks[i];

	// call the function
	minres_HW(&block_struct,  out_blocks_casted, b, x_current, minres_data);
	
	#endif
}