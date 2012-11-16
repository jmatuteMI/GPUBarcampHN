#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>

static bool isPrime(int number){
  int i;
  bool result = true;
  if (number == 0 || number == 1)
      return false;
  for( i = 2; i < number;i++){
    if (number%i == 0)
        result = false;
  }
  return result;
}

int main(int argc,char* argv[]){
  int value = atoi(argv[1]);
  int comm_sz;
  int rank;
  int i,count,start,stop, amount;
  int total;

  MPI_Init(NULL,NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  count = value/(comm_sz-1); //without the master thread
  start = (rank -1)* count; // the thread with rank 1 will start the job
  stop =  start + count;
  amount = 0;

  if (rank != 0){
      for(i = start; i < stop; ++i){
        if(isPrime(i))
            amount++;
      }
      MPI_Send( &amount,1,MPI_INT,0,0,MPI_COMM_WORLD);
  }
  else{
    total = 0;
    for( i = 1; i < comm_sz; i++){
        MPI_Recv( &amount,1,MPI_INT,i,0,MPI_COMM_WORLD,0);
        total += amount;
    }
  
    printf("there is a total of %d primes \n",total);
  } 

  
  MPI_Finalize();
  return 0;
}


