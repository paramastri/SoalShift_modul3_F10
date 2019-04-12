#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<termios.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>

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

char monster[800];
int Hung_Stat=200;
int Hyg_Stat=100;
int Health_Stat=300;
int det_mandi=20;
int det_health=10;
int det_hyg=30;
int det_hung=10;
int langsung_mandi=0;
int jeda=0;
pthread_t thread[7];
char choose;
int maem_monster=0;
void* tampilan_asli(void*);

void* laper (void *ptr)
{
    while(1)
    {
        // sleep(10);
        while(jeda!=0)
        {

        }
        sleep(1);
        if(det_hung==1)
        {
        	// berkurang 5 tiap 10 det_hungry
            det_hung=10;
            Hung_Stat-=5;
        }
        else det_hung-=1;
        if(jeda==0)
        {


            if(Hung_Stat<=0) // hunger status = 0
            {
                printf("Kelaperan. Mati deh :(\n");
                exit(EXIT_FAILURE);
            }

        }


    }
}

void* hyginis (void *ptr)
{
    while(1)
    {
        // sleep(30);
        while(jeda!=0)
        {

        }
        sleep(1);
        if(det_hyg==1)
        {
            det_hyg=30;
            Hyg_Stat-=10;
        }
        else det_hyg-=1;
        if(jeda==0)
        {

            if(Hyg_Stat<=0)
            {
                printf("Kotor banget. Monster dah mati\n");
                exit(EXIT_FAILURE);
            }
        }

    }
}

void* sehat (void *ptr)
{
    while(1)
    {
        while(jeda!=0)
        {

        }
        sleep(1);
        if(det_health==1)
        {
            det_health=10;
            Health_Stat+=5;
        }
        else det_health-=1;
        if(jeda==0)
        {


            if(Health_Stat<=0)
            {
                printf("Monster mati. Sakit-sakitan sih\n");
                exit(EXIT_FAILURE);
            }

        }

    }
}

void* itungan_mandi (void *ptr)
{
    while(1)
    {
        while(jeda!=0)
        {

        }
        if(langsung_mandi==0)
        {
            sleep(1);
            if(det_mandi==0)
            {
                det_mandi=20;
                langsung_mandi=1;
            }
            else det_mandi-=1;
        }

    }
}

int *maem_shop;
void* ini_shop (void* arg){
    key_t key = 1234;


    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    maem_shop = shmat(shmid, NULL, 0);

    *maem_shop = 0;
}


void* tampilan_asli(void *arg)
{
    while(1){
    while(jeda!=0)
    {

    }
    system("clear");
    printf("Standby Mode\n");
    printf("monster : %s\n",monster);
    printf("Health : %d\n",Health_Stat);
    printf("Hunger : %d\n",Hung_Stat);
    printf("Hygiene : %d\n",Hyg_Stat);
    printf("Food Left : %d\n",maem_monster);
    if(langsung_mandi==0)
    printf("Bath will be ready in %d\n",det_mandi);
    else printf("Bath is ready\n");
    printf("Choice :\n");
    printf("1. Eat\n");
    printf("2. Bath\n");
    printf("3. Battle\n");
    printf("4. Shop\n");
    printf("5. Exit\n");
    sleep(1);
    }
}

void* tampilan_food(void *arg)
{
    while(1){
    while(jeda!=2)
    {

    }
    system("clear");
    printf("Shop Mode\n");
    printf("Shop food stock : %d\n",*maem_shop);
    printf("Your food stock : %d\n",maem_monster);
    printf("Choices\n");
    printf("1. Buy\n");
    printf("2. Back\n");
    sleep(1);
    }
}

int main()
{
    char c;
    int i;
    printf("Beri monster monstermu > ");
    c=getchar();
    while(c!='\n')
    {
        monster[i]=c;
        c=getchar();
        i++;
    }
    pthread_create(&(thread[0]),NULL,laper,NULL);
    pthread_create(&(thread[1]),NULL,hyginis,NULL);
    pthread_create(&(thread[2]),NULL,sehat,NULL);
    pthread_create(&(thread[3]),NULL,itungan_mandi,NULL);
    pthread_create(&(thread[4]),NULL,tampilan_asli,NULL);
    pthread_create(&(thread[5]),NULL,ini_shop,NULL);
    pthread_create(&(thread[6]),NULL,tampilan_food,NULL);

    while(1)
    {
        // tampilan_asli();
        choose=getch();
        if(choose=='1')
        {
            if(maem_monster>0)
            {
                Hung_Stat+=15;
                maem_monster--;
                if(Hung_Stat>200)
	            {
	                Hung_Stat=200;
	            }
            }

        }
        else if(choose=='2')
        {
            if(langsung_mandi==1)
            {
                Hyg_Stat+=30;
                if(Hyg_Stat>100)
                {
                    Hyg_Stat=100;
                }
                langsung_mandi=0;
            }

        }
        else if(choose=='3')
        {
            int statusLawan=100;
            jeda=1;
            while(1)
            {
                system("clear");
                printf("Battle Mode\n");
                printf("Monster's Health : %d\n",Health_Stat);
                printf("Enemy's Health : %d\n",statusLawan);
                printf("Choices\n");
                printf("1. Attack\n");
                printf("2. Run\n");
                char pilih;
                pilih = getch();
                if(pilih=='1')
                {
                    if(Health_Stat>0 && statusLawan>0)
                    {
                        Health_Stat-=20;
                        if(statusLawan>0)
                        {
                            statusLawan-=20;
                        }
                    }
                    if(Health_Stat<0)
                    {
                        Health_Stat=0;
                        jeda=0;
                        break;
                    }
                    else if(statusLawan<0)
                    {
                        statusLawan=0;
                    }
                }
                else if(pilih=='2')
                {
                    jeda=0;
                    break;
                }


            }
        }
        else if(choose=='4')
        {
            jeda=2;
            char pilih;
            while(1)
            {
                pilih = getch();
                if(pilih=='1')
                {
                    if(*maem_shop > 0)
                    {
                        *maem_shop = *maem_shop - 1;
                        maem_monster++;
                    }

                }
                else if(pilih=='2')
                {
                    jeda=0;
                    break;
                }


            }
        }
        else if(choose=='5')
        {
            system("clear");
            printf("Thanks for playing!\n");
            exit(EXIT_FAILURE);
            break;
        }
    }
    pthread_join(thread[0],NULL);
    pthread_join(thread[1],NULL);
    pthread_join(thread[2],NULL);
    pthread_join(thread[3],NULL);
    pthread_join(thread[4],NULL);
    pthread_join(thread[5],NULL);
    pthread_join(thread[6],NULL);
    return 0;
}
