#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_DIM 8192 

__device__ void isPrime(bool* result,int number){
  int i;
  for( i = 2; i < number;i++){
    if (number%i == 0)
        *result = false;
  }
}

__global__ void primality(bool* result,int number){
  int i = threadIdx.x + blockIdx.x * blockDim.x +2;
  bool answer = true;
  while( i < number){
      isPrime(&answer,i);
      result[i] = answer; 
      answer = true;
      i+= BLOCK_DIM;
  }
}

int main(int argc,char* argv[]){
  int value = atoi(argv[1]);
  bool *numbers;

  bool *results = (bool*)malloc(sizeof(bool)*value);
  cudaMalloc( (void**)&numbers,sizeof(bool)*value); 

  dim3  blocks_per_grid(64,1);
  dim3  thread_per_block(128,1);

  primality<<<blocks_per_grid,thread_per_block>>>(numbers,value);
  cudaError_t Error = cudaGetLastError();
  if( cudaSuccess != Error){
        printf("CUDA Error en el Llamado del Kernel: %s\n", cudaGetErrorString(Error));
  }

  cudaMemcpy(results,numbers,sizeof(bool)*value,cudaMemcpyDeviceToHost); 
  
  Error = cudaGetLastError();
  if( cudaSuccess != Error){
        printf("CUDA Error en la copia: %s\n", cudaGetErrorString(Error));
  }
  
  cudaFree(numbers);
  


  int i = 2;
  int counter = 0;
  for( ; i < value;i++)
      if (results[i])
        counter++;
  printf("%d\n",counter);

  free(results);

  return 0;
}
