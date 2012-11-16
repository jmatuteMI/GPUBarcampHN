#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


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
  
  while (1){
    while( numbers[++start] == 0 );
    squared = start*start;
    if (squared > value)
        break;
    trying = numbers[start];
    while(squared < value){
      if(numbers[squared] % trying == 0)
          numbers[squared] = 0;
      squared += trying; 
    }
  }

  int total = 0;
  for( i = 0; i < value;i++)
    if ( numbers[i] != 0 ) total += 1;

  printf("%d\n",total);
  free(numbers);
  return 0;  
}
