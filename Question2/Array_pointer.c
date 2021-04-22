#include <stdio.h>
#include <time.h>
int main(void) {
  int arr[100][100];
  int *ptr = &arr[0][0];

  int i, j;
  clock_t start, stop;
  clock_t start1, stop1;

  start = clock();
  for(i = 0; i< 100;i++){
    for(j = 0; j< 100;j++){
      arr[i][j] = i + j;
    //   printf( "Value for [%d][%d] is %d: \n",i,j, arr[i][j]);
    }    
  }
  stop = clock();
  printf("%ld\n", start);
  printf("%ld\n", stop);
  printf("%ld\n", stop - start);
  

  start1 = clock();
  for(i = 0; i< 100 * 100;i++){
       *(ptr + i) = 0;
  }
  stop1 = clock();
//   printf(ptr);

  printf("%ld\n", stop1);
  printf("%ld\n", start1);
  printf("%ld\n", (stop1 - start1));
  
  return 0;
}