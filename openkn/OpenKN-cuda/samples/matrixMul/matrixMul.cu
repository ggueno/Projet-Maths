/*
 * Copyright 1993-2007 NVIDIA Corporation.  All rights reserved.
 *
 * NOTICE TO USER:
 *
 * This source code is subject to NVIDIA ownership rights under U.S. and
 * international Copyright laws.  Users and possessors of this source code
 * are hereby granted a nonexclusive, royalty-free license to use this code
 * in individual and commercial software.
 *
 * NVIDIA MAKES NO REPRESENTATION ABOUT THE SUITABILITY OF THIS SOURCE
 * CODE FOR ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR
 * IMPLIED WARRANTY OF ANY KIND.  NVIDIA DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOURCE CODE, INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL NVIDIA BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS,  WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION,  ARISING OUT OF OR IN CONNECTION WITH THE USE
 * OR PERFORMANCE OF THIS SOURCE CODE.
 *
 * U.S. Government End Users.   This source code is a "commercial item" as
 * that term is defined at  48 C.F.R. 2.101 (OCT 1995), consisting  of
 * "commercial computer  software"  and "commercial computer software
 * documentation" as such terms are  used in 48 C.F.R. 12.212 (SEPT 1995)
 * and is provided to the U.S. Government only as a commercial end item.
 * Consistent with 48 C.F.R.12.212 and 48 C.F.R. 227.7202-1 through
 * 227.7202-4 (JUNE 1995), all U.S. Government End Users acquire the
 * source code with only those rights set forth herein.
 *
 * Any use of this source code in individual and commercial software must
 * include, in the user documentation and internal comments to the code,
 * the above Disclaimer and U.S. Government End Users Notice.
 */

/* Matrix multiplication: C = A * B.
 * Host code.
 *
 * This sample implements matrix multiplication and is exactly the same as
 * Chapter 7 of the programming guide.
 * It has been written for clarity of exposition to illustrate various CUDA
 * programming principles, not with the goal of providing the most
 * performant generic kernel for matrix multiplication.
 *
 * CUBLAS provides high-performance matrix multiplication.
 */

// includes, system
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// includes, project
#include <cutil.h>

// includes, kernels
#include <matrixMul_kernel.cu>

////////////////////////////////////////////////////////////////////////////////
// declaration, forward
void runTest(int argc, char** argv);
void randomInit(float*, int);
void printDiff(float*, float*, int, int);

extern "C"
void computeGold(float*, const float*, const float*, unsigned int, unsigned int, unsigned int);


void initMatrixMul(CudaParams * c) {
    CUT_DEVICE_INIT(0,NULL);

    // set seed for rand()
    srand(2006);

    // allocate host memory for matrices A and B
    c->size_A = WA * HA;
    c->mem_size_A = sizeof(float) * c->size_A;
    c->h_A = (float*) malloc(c->mem_size_A);
    c->size_B = WB * HB;
    c->mem_size_B = sizeof(float) * c->size_B;
    c->h_B = (float*) malloc(c->mem_size_B);

    // initialize host memory
    randomInit(c->h_A, c->size_A);
    randomInit(c->h_B, c->size_B);

    // allocate device memory
    CUDA_SAFE_CALL(cudaMalloc((void**) &(c->d_A), c->mem_size_A));
    CUDA_SAFE_CALL(cudaMalloc((void**) &(c->d_B), c->mem_size_B));

    // copy host memory to device
    CUDA_SAFE_CALL(cudaMemcpy(c->d_A, c->h_A, c->mem_size_A,
                              cudaMemcpyHostToDevice) );
    CUDA_SAFE_CALL(cudaMemcpy(c->d_B, c->h_B, c->mem_size_B,
                              cudaMemcpyHostToDevice) );

    // allocate device memory for result
    c->size_C = WC * HC;
    c->mem_size_C = sizeof(float) * c->size_C;
    CUDA_SAFE_CALL(cudaMalloc((void**) &(c->d_C), c->mem_size_C));

    // allocate host memory for the result
    c->h_C = (float*) malloc(c->mem_size_C);
}


void runMatrixMul(CudaParams *c) {
    // create and start timer
    unsigned int timer = 0;
    CUT_SAFE_CALL(cutCreateTimer(&timer));
    CUT_SAFE_CALL(cutStartTimer(timer));

    // setup execution parameters
    dim3 threads(BLOCK_SIZE, BLOCK_SIZE);
    dim3 grid(WC / threads.x, HC / threads.y);

    // execute the kernel
    matrixMul<<< grid, threads >>>(c->d_C, c->d_A, c->d_B, WA, WB);

    // check if kernel execution generated and error
    CUT_CHECK_ERROR("Kernel execution failed");

    // copy result from device to host
    CUDA_SAFE_CALL(cudaMemcpy(c->h_C, c->d_C, c->mem_size_C,
                              cudaMemcpyDeviceToHost) );

    // stop and destroy timer
    CUT_SAFE_CALL(cutStopTimer(timer));
    printf("Processing time: %f (ms) \n", cutGetTimerValue(timer));
    CUT_SAFE_CALL(cutDeleteTimer(timer));

    // compute reference solution
    float* reference = (float*) malloc(c->mem_size_C);
    computeGold(reference, c->h_A, c->h_B, HA, WA, WB);

    // check result
    CUTBoolean res = cutCompareL2fe(reference, c->h_C, c->size_C, 1e-6f);
    printf("Test %s \n", (1 == res) ? "PASSED" : "FAILED");
    if (res!=1) printDiff(reference, c->h_C, WC, HC);
}

void releaseMatrixMul(CudaParams * c) {
    // clean up memory
    free(c->h_A);
    free(c->h_B);
    free(c->h_C);
    //free(reference);
    CUDA_SAFE_CALL(cudaFree(c->d_A));
    CUDA_SAFE_CALL(cudaFree(c->d_B));
    CUDA_SAFE_CALL(cudaFree(c->d_C));
}



// Allocates a matrix with random float entries.
void randomInit(float* data, int size)
{
    for (int i = 0; i < size; ++i)
        data[i] = rand() / (float)RAND_MAX;
}

void printDiff(float *data1, float *data2, int width, int height)
{
  int i,j,k;
  int error_count=0;
  for (j=0; j<height; j++) {
    for (i=0; i<width; i++) {
      k = j*width+i;
      if (data1[k] != data2[k]) {
         printf("diff(%d,%d) CPU=%4.4f, GPU=%4.4f n", i,j, data1[k], data2[k]);
         error_count++;
      }
    }
  }
  printf(" nTotal Errors = %d n", error_count);
}
