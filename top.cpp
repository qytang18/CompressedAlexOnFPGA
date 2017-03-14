#include <iostream>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "configure.h"
#include "convolution.h"
//#include "bias.h"
#include "pooling.h"

using namespace std;


void CNN (TYPE_T *img_in, TYPE_T *weight1, TYPE_T *bias1, TYPE_T *pool1_out)
{
    /* define the interface */
#pragma HLS INTERFACE m_axi port=img_in depth=512 offset=slave bundle=gmem1
#pragma HLS INTERFACE m_axi port=pool1_out depth=512 offset=slave bundle=gmem1
#pragma HLS INTERFACE m_axi port=weight1 depth=512 offset=slave bundle=gmem2
#pragma HLS INTERFACE m_axi port=bias1 depth=512 offset=slave bundle=gmem2
#pragma HLS INTERFACE s_axilite port=img_in bundle=control
#pragma HLS INTERFACE s_axilite port=weight1 bundle=control
#pragma HLS INTERFACE s_axilite port=bias1 bundle=control
#pragma HLS INTERFACE s_axilite port=pool1_out bundle=control
#pragma HLS INTERFACE s_axilite port=return bundle=control

	TYPE_T buf_in[3][227][227];
#pragma HLS ARRAY_RESHAPE variable=buf_in complete dim=1
	memcpy(buf_in, img_in, sizeof(TYPE_T)*3*227*227);
    /* define the first Convolution2D layer */
	TYPE_T conv1_out[96][55][55];
#pragma HLS ARRAY_RESHAPE variable=conv1_out complete dim=1


	Convolution<R_IN1, C_IN1, N1, K1, M1, P1,S1> conv1;
    conv1.forward(buf_in, conv1_out, weight1, bias1);

    
    MaxPooling2D<R_OUT1, C_OUT1,M1, POOL_R1, POOL_C1,POOL_S1> pool1;
    pool1.forward(conv1_out, pool1_out);
    return;
}
