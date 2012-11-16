#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define BLOCK_DIM 8192

__global__ void primality(int* result,int val,int limit,int offset){
  int i = threadIdx.x + blockIdx.x * blockDim.x;
  int start = i*val + offset;
  while (start < limit){
    if(result[start] % val == 0){
       result[start] = 0;
    }
    i += BLOCK_DIM;
    start += i*val + offset; 
  } 
}

int main(int argc,char *argv[]){
  int value = atoi(argv[1]);
  int* numbers = (int*)malloc(sizeof(int)*(value));
  int i;
  int trying,squared;
  numbers[0] = numbers[1] = 0;
  for(i = 2; i < value;i++)
      numbers[i] = i;
  
  int start;
  squared = 0;
  start = -1; 
  dim3  blocks_per_grid(64,1);
  dim3  thread_per_block(128,1);
  
  int *cuda_mem_array;
  cudaMalloc( (void**)&cuda_mem_array,(value)*sizeof(int));
  cudaMemcpy( cuda_mem_array ,numbers,value*sizeof(int),cudaMemcpyHostToDevice);
  cudaError_t Error = cudaGetLastError();
  if( cudaSuccess != Error){
        printf("CUDA Error: %s\n", cudaGetErrorString(Error));
  }
  while (1){
     while( numbers[++start] == 0 );
     squared = start*start;
     if (squared > value)
        break;
     trying = numbers[start];
     primality<<<blocks_per_grid,thread_per_block>>>(cuda_mem_array,trying,value,squared);
     cudaThreadSynchronize();
     cudaMemcpy(numbers,cuda_mem_array,value*sizeof(int),cudaMemcpyDeviceToHost); 
     Error = cudaGetLastError();
     if( cudaSuccess != Error){
        printf("CUDA Error: %s\n", cudaGetErrorString(Error));
     }

     cudaThreadSynchronize();
  }

  cudaFree(cuda_mem_array);

  int total = 0;
  for( i = 0; i < value;i++)
    if ( numbers[i] != 0 ) total += 1;

  free(numbers);
  printf("%d\n",total);
  return 0;  
}

