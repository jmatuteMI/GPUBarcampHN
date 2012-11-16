#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool isPrime(int number){
  int i;
  if ( number != 2 && number % 2 == 0) return false;
  
  for( i = 3; i < number;i += 2){
    if (number%i == 0)
        return false;
  }
  return true;
}

int main(int argc,char* argv[]){
  int value = atoi(argv[1]);
  int counter,are;
  are = 0; 
  counter = 2;
  for( ; counter <= value ; counter++){
      if ( isPrime(counter) ) are++;
  }
  
  printf("Son primos %d\n",are);
  return 0;
}

