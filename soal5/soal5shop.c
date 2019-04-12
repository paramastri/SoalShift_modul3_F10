#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include<stdlib.h>
#include<termios.h>
#include<pthread.h>

static struct termios old, new;
/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  new = old; /* make new settings same as old settings */
  new.c_lflag &= ~ICANON; /* disable buffered i/o */
  if (echo) {
      new.c_lflag |= ECHO; /* set echo mode */
  } else {
      new.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
  return getch_(0);
}

int *maem_shop;
pthread_t thread[2];

void* shop_ini (void* arg)
{
    key_t key = 1234;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    maem_shop = shmat(shmid, NULL, 0);
  
    *maem_shop = 0;

}

void* shopping (void* arg)
{
    while(1)
    {
        system("clear");
        printf("Shop\n");
        printf("Food Stock : %d\n",*maem_shop);
        printf("Choice : \n");
        printf("1. Restock\n");
        printf("2. Exit\n");
        sleep(1);
    }

}
void main()
{
    pthread_create(&(thread[0]),NULL,shop_ini,NULL);
    pthread_create(&(thread[1]),NULL,shopping,NULL);
    char choose;
    while(1)
    {
        choose=getch();
        if(choose=='1')
        {
            *maem_shop = *maem_shop + 1;
        }
        else if(choose=='2')
        {
            break;
        }
    }
}
