#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

pthread_t input[100];
int t[100];
int x;

void* faktorial()
{
	int inputnya = t[x];
	int jawaban = 1;

	while(inputnya > 0)
	{
		jawaban *= inputnya;
	 	inputnya--;
	}

	printf("%d! = %d\n", t[x], jawaban);
}

int main(int argc, char *argv[])
{
	int n = argc-1, a, b, iter, tukar;

	// ubah char ke integer
	for(iter = 0; iter < n; iter++)
	{
		t[iter] = atoi(argv[iter+1]);
	}

	// bubble sort
  	for (iter = 0 ; iter < n-1; iter++)
  	{
    	  for (b = 0 ; b < n-a-1; b++)
    	  {
      		if (t[b] > t[b+1])
      		{
        	  tukar = t[b];
        	  t[b] = t[b+1];
        	  t[b+1] = tukar;
      		}
    	  }
  	}


	for(x = 0; x < n; x++)
	{
		pthread_create(&(input[x]),NULL,&faktorial,NULL);
	 	pthread_join(input[x], NULL);
	}

	return 0;
}

