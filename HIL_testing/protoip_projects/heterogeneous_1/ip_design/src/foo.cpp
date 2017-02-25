/* 
* icl::protoip
* Author: asuardi <https://github.com/asuardi>
* Date: November - 2014
*/


#include "foo_data.h"


void foo_user(  data_t_block_in block_in_int[BLOCK_IN_LENGTH],
				data_t_out_block_in out_block_in_int[OUT_BLOCK_IN_LENGTH],
				data_t_x_in_in x_in_in_int[X_IN_IN_LENGTH],
				data_t_y_out_out y_out_out_int[Y_OUT_OUT_LENGTH]);


void foo	(
				uint32_t byte_block_in_offset,
				uint32_t byte_out_block_in_offset,
				uint32_t byte_x_in_in_offset,
				uint32_t byte_y_out_out_offset,
				volatile data_t_memory *memory_inout)
{

	//for synthesis

	data_t_interface_block_in  block_in[BLOCK_IN_LENGTH];
	data_t_interface_out_block_in  out_block_in[OUT_BLOCK_IN_LENGTH];
	data_t_interface_x_in_in  x_in_in[X_IN_IN_LENGTH];
	data_t_interface_y_out_out  y_out_out[Y_OUT_OUT_LENGTH];

	static data_t_block_in  block_in_int[BLOCK_IN_LENGTH];
	static data_t_out_block_in  out_block_in_int[OUT_BLOCK_IN_LENGTH];
	static data_t_x_in_in  x_in_in_int[X_IN_IN_LENGTH];
	data_t_y_out_out  y_out_out_int[Y_OUT_OUT_LENGTH];

	#if FLOAT_FIX_BLOCK_IN == 1
	///////////////////////////////////////
	//load input vectors from memory (DDR)

	if(!(byte_block_in_offset & (1<<31)))
	{
		memcpy(block_in,(const data_t_memory*)(memory_inout+byte_block_in_offset/4),BLOCK_IN_LENGTH*sizeof(data_t_memory));

    	//Initialisation: cast to the precision used for the algorithm
		input_cast_loop_block:for (int i=0; i< BLOCK_IN_LENGTH; i++)
			block_in_int[i]=(data_t_block_in)block_in[i];

	}
	

	#elif FLOAT_FIX_BLOCK_IN == 0
	///////////////////////////////////////
	//load input vectors from memory (DDR)

	if(!(byte_block_in_offset & (1<<31)))
	{
		memcpy(block_in_int,(const data_t_memory*)(memory_inout+byte_block_in_offset/4),BLOCK_IN_LENGTH*sizeof(data_t_memory));
	}

	#endif


	#if FLOAT_FIX_OUT_BLOCK_IN == 1
	///////////////////////////////////////
	//load input vectors from memory (DDR)

	if(!(byte_out_block_in_offset & (1<<31)))
	{
		memcpy(out_block_in,(const data_t_memory*)(memory_inout+byte_out_block_in_offset/4),OUT_BLOCK_IN_LENGTH*sizeof(data_t_memory));

    	//Initialisation: cast to the precision used for the algorithm
		input_cast_loop_out_block:for (int i=0; i< OUT_BLOCK_IN_LENGTH; i++)
			out_block_in_int[i]=(data_t_out_block_in)out_block_in[i];

	}
	

	#elif FLOAT_FIX_OUT_BLOCK_IN == 0
	///////////////////////////////////////
	//load input vectors from memory (DDR)

	if(!(byte_out_block_in_offset & (1<<31)))
	{
		memcpy(out_block_in_int,(const data_t_memory*)(memory_inout+byte_out_block_in_offset/4),OUT_BLOCK_IN_LENGTH*sizeof(data_t_memory));
	}

	#endif


	#if FLOAT_FIX_X_IN_IN == 1
	///////////////////////////////////////
	//load input vectors from memory (DDR)

	if(!(byte_x_in_in_offset & (1<<31)))
	{
		memcpy(x_in_in,(const data_t_memory*)(memory_inout+byte_x_in_in_offset/4),X_IN_IN_LENGTH*sizeof(data_t_memory));

    	//Initialisation: cast to the precision used for the algorithm
		input_cast_loop_x_in:for (int i=0; i< X_IN_IN_LENGTH; i++)
			x_in_in_int[i]=(data_t_x_in_in)x_in_in[i];

	}
	

	#elif FLOAT_FIX_X_IN_IN == 0
	///////////////////////////////////////
	//load input vectors from memory (DDR)

	if(!(byte_x_in_in_offset & (1<<31)))
	{
		memcpy(x_in_in_int,(const data_t_memory*)(memory_inout+byte_x_in_in_offset/4),X_IN_IN_LENGTH*sizeof(data_t_memory));
	}

	#endif



	///////////////////////////////////////
	//USER algorithm function (foo_user.cpp) call
	//Input vectors are:
	//block_in_int[BLOCK_IN_LENGTH] -> data type is data_t_block_in
	//out_block_in_int[OUT_BLOCK_IN_LENGTH] -> data type is data_t_out_block_in
	//x_in_in_int[X_IN_IN_LENGTH] -> data type is data_t_x_in_in
	//Output vectors are:
	//y_out_out_int[Y_OUT_OUT_LENGTH] -> data type is data_t_y_out_out
	foo_user_top: foo_user(	block_in_int,
							out_block_in_int,
							x_in_in_int,
							y_out_out_int);


	#if FLOAT_FIX_Y_OUT_OUT == 1
	///////////////////////////////////////
	//store output vectors to memory (DDR)

	if(!(byte_y_out_out_offset & (1<<31)))
	{
		output_cast_loop_y_out: for(int i = 0; i <  Y_OUT_OUT_LENGTH; i++)
			y_out_out[i]=(data_t_interface_y_out_out)y_out_out_int[i];

		//write results vector y_out to DDR
		memcpy((data_t_memory *)(memory_inout+byte_y_out_out_offset/4),y_out_out,Y_OUT_OUT_LENGTH*sizeof(data_t_memory));

	}
	#elif FLOAT_FIX_Y_OUT_OUT == 0
	///////////////////////////////////////
	//write results vector y_out to DDR
	if(!(byte_y_out_out_offset & (1<<31)))
	{
		memcpy((data_t_memory *)(memory_inout+byte_y_out_out_offset/4),y_out_out_int,Y_OUT_OUT_LENGTH*sizeof(data_t_memory));
	}

	#endif




}
