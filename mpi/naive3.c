#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>

bool isPrime(int number){
  int i;
  if ( number < 2 && number % 2 == 0) return false;
  
  for( i = 3; i < number;i += 2){
    if (number%i == 0)
        return false;
  }
  return true;
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
  count = value/(comm_sz); //without the master thread
  start = rank * count; // the thread with rank 1 will start the job
  stop =  start + count;
  amount = 0;

  for(i = start; i < stop; i++)
    if(isPrime(i))
      amount++;
  
  total = 0;
  MPI_Reduce(&amount,&total,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);   
  
  if ( rank == 0){
    printf("there is a total of %d primes \n",total);
  }

  MPI_Finalize();
  return 0;
}


