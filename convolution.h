//
//  convolution.cpp
//  cnn_2
//
//  Created by tqy on 3/10/17.
//  Copyright � 2017 tqy. All rights reserved.
//

#ifndef __CONVOLUTION_H__
#define __CONVOLUTION_H__

#include <stdio.h>
#include "configure.h"
#include <string.h>


void load(TYPE_T *buf, TYPE_T *in, int size){
    memcpy(buf, in, size);
    //buf=in;
}

void store(TYPE_T *out, TYPE_T *buf, int size){
    memcpy(out, buf, size);
}

template<int R_IN, int C_IN, int N, int K, int M, int P, int S, int R_OUT = (R_IN-K+2*P)/S+1, int C_OUT = (C_IN-K+2*P)/S+1>
//R_IN 227, C_IN 227, K 11, R_OUT 55, C_OUT 55, M 96, S 4
class Convolution{
public:
    void forward (TYPE_T fm_in[N][R_IN][C_IN], TYPE_T fm_out[M][R_OUT][C_OUT], TYPE_T *weight,TYPE_T *bias){
#pragma HLS INTERFACE ap_ctrl_chain port=fm_out
#pragma HLS INTERFACE bram port=fm_in
#pragma HLS INTERFACE bram port=fm_out
#pragma HLS INTERFACE m_axi port=weight depth=512 offset=slave bundle=gmem2
#pragma HLS INTERFACE m_axi port=bias depth=512 offset=slave bundle=gmem2
#pragma HLS INTERFACE s_axilite port=return bundle=control
    	TYPE_T local_bias[M1];
#pragma HLS ARRAY_RESHAPE variable=local_bias complete
    	memcpy(local_bias, bias, sizeof(TYPE_T)*M1);
    	TYPE_T buf_weight[96][3][11][11];
#pragma HLS ARRAY_RESHAPE variable=buf_weight complete dim=1
        memcpy(buf_weight, weight,sizeof(TYPE_T)*96*3*11*11);
                        for(int i = 0; i < K; i++) {
                            for(int j = 0; j < K; j++) {
                                for (int trr = 0;trr <  R_OUT; trr++) {
                                    for (int tcc = 0; tcc < C_OUT; tcc++) {
                        #pragma HLS PIPELINE
                        #pragma HLS INLINE OFF
                                    	for (int too = 0; too < M; too++) {
                        #pragma HLS UNROLL
                                        	for(int tii = 0; tii < N; tii++) {
                        #pragma HLS UNROLL
                                                fm_out[too][trr][tcc] += buf_weight[too][tii][i][j] * fm_in[tii][S * trr + i][S * tcc + j];
                                            }}}}}}


      for (int j = 0;j<55;j++)
          for (int k = 0;k<55;k++){
#pragma HLS PIPELINE
             for (int i = 0;i<96;i++){
                   fm_out[i][j][k]=max(0, bias[i] + fm_out[i][j][k]);
                 }
           }

    }
};
#endif
