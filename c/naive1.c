#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void isPrime(bool* result,int number){
  int i;
  for( i = 2; i < number;i++){
    if (number%i == 0)
        *result = false;
  }
}

int main(int argc,char* argv[]){
  int value = atoi(argv[1]);
  int counter,are;
  are = 0; 
  counter = 2;
  bool answer = true;
  for( ; counter <= value ; counter++){
      isPrime(&answer,counter);
      if (answer) are++;
      answer = true;
  }
  
  printf("Son primos %d\n",are);
  return ;
}


