#include "user_protoip_definer.h"
#include "user_main_header.h"
#include "user_nnz_header.h"
#include "user_structure_header.h"
#include "user_prototypes_header.h"


void wrap_mv_mult_prescaled_HW(float y_out[n_all_theta+n_all_nu],float block[N*nnz_block_tril + nnz_term_block_tril],float out_block[(N+1)*n_states],float x_in[n_all_theta+n_all_nu])
{
	int i,j,k;

	// interface structure
	part_vector x_in_struct;
	part_vector y_out_struct;
	part_matrix block_struct;
	d_type_lanczos out_blocks_casted[(N+1)*n_states];

	// pack vector into structure
	for(i = 0, k = 0; i < n_states; i++, k++) x_in_struct.vec0[i] = x_in[k];
	for(i = 0; i < PAR; i++)
		for(j = 0; j < part_size*(n_node_theta+n_node_eq); j++, k++) x_in_struct.vec[i][j] = x_in[k]; 
	#ifdef rem_partition
		for(i = 0; i < rem_partition*(n_node_theta+n_node_eq); i++, k++)  x_in_struct.vec_rem[i] = x_in[k];
	#endif
	for(i = 0; i < n_term_theta+n_term_eq; i++, k++) x_in_struct.vec_term[i] = x_in[k];

	// pack matrix into structure
	for(i = 0, k = 0; i < PAR; i++)
		for(j = 0; j < part_size*nnz_block_tril; j++, k++) block_struct.mat[i][j] = block[k];
	#ifdef rem_partition		
		for(i = 0; i < rem_partition*nnz_block_tril; i++, k++) block_struct.mat_rem[i] = block[k];
	#endif
	for(i = 0; i < nnz_term_block_tril; i++, k++) block_struct.mat_term[i] = block[k];


	// cast out blocks to required precision
	for(i = 0; i < (N+1)*n_states; i++)
		out_blocks_casted[i] = (d_type_lanczos) out_block[i];

	// call the function
	mv_mult_prescaled_HW( &y_out_struct, &block_struct, out_blocks_casted, &x_in_struct);



	// unpack structure into a vector
	for(i = 0, k = 0; i < n_states; i++, k++) y_out[k] = y_out_struct.vec0[i];
	for(i = 0; i < PAR; i++)
		for(j = 0; j < part_size*(n_node_theta+n_node_eq); j++, k++) y_out[k] = y_out_struct.vec[i][j]; 
	#ifdef rem_partition
		for(i = 0; i < rem_partition*(n_node_theta+n_node_eq); i++, k++)  y_out[k] = y_out_struct.vec_rem[i];
	#endif
	for(i = 0; i < n_term_theta+n_term_eq; i++, k++) y_out[k] = y_out_struct.vec_term[i];
	

}