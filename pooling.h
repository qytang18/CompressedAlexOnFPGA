
//
//  pooling.cpp
//  cnn_2
//
//  Created by tqy on 3/11/17.
//  Copyright � 2017 tqy. All rights reserved.
//
#ifndef __POOLING_H__
#define __POOLING_H__

#include <stdio.h>
#include <string.h>
#include "configure.h"

template<int IN_ROW, int IN_COL, int N, int POOL_ROW = 2, int POOL_COL = 2, int POOL_S = 1, int OUT_ROW = (IN_ROW-POOL_ROW)/POOL_S+1, int OUT_COL = (IN_COL-POOL_COL)/POOL_S+1>
class MaxPooling2D
{
public:
    void forward(TYPE_T data[N][IN_ROW][IN_COL], TYPE_T *res)
    {
#pragma HLS INTERFACE bram port=data
#pragma HLS INTERFACE m_axi port=res depth=512 offset=slave bundle=gmem1
#pragma HLS INTERFACE s_axilite port=return bundle=control
    	TYPE_T out[N][OUT_ROW][OUT_COL];
#pragma HLS ARRAY_RESHAPE variable=out complete dim=1
        
        for (int row = 0; row < OUT_ROW; row++)
        {
            for (int col = 0; col < OUT_COL; col++)
                {
        #pragma HLS INLINE OFF
                    for (int k = 0; k < N; k++)
                    {
        #pragma HLS UNROLL
                    TYPE_T max = data[k][row*POOL_S][col * POOL_S];
                    for (int i = 0; i < POOL_ROW; i++)
                    {
                        for (int j = 0; j < POOL_COL; j++)
                        {
        #pragma HLS pipeline
                            TYPE_T v = data[k][row*POOL_S + i][col * POOL_S + j];
                            if (v > max)
                                max = v;
                        }
                    }
                    out[k][row][col] = max;
                }
            }
        }
        memcpy (res, out, sizeof(N*OUT_ROW*OUT_COL));
    }
};

#endif
