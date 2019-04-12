#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int WakeUp_Status=0;
int Spirit_Status=100;
int AgmalCount=1;
int IrajCount=1;
int ThreadSleep=0;
int choice=0;


void Status(){
    // system("clear");
    IrajCount=1;
    AgmalCount=1;

    printf("\nAgmal Wake Up Status = %d\n",WakeUp_Status);
    printf("Iraj Spirit Status = %d\n\n",Spirit_Status);

    return;
}

void *AgmalAyoBangun(){
    while(1) {
        if(choice!=2) {
            continue;
        }
        if(choice==2 && ThreadSleep==2) {
            printf("\nFitur \"Agmal Ayo Bangun\" tidak bisa dijalankan selama 10 detik\n\n");
            sleep(10);
            choice=0;
            AgmalCount=1;
            IrajCount=1;
            ThreadSleep=0;   
        }
        else if(choice==2) {
            WakeUp_Status+=15;
            printf("\nAgmal Wake Up Status +15\n\n");
            if(WakeUp_Status>=100) {
                printf("\nAgmal telah terbangun, mereka bangu pagi dan berolahraga\n");
                exit(0);
            }
            choice=0;
        }  
    }
}

void *IrajAyoTidur(){
    while(1) {
        if(choice!=3) {
            continue;
        }
        if(choice==3 && ThreadSleep==1) {
            printf("\nFitur \"Iraj Ayo Tidur\" tidak bisa dijalankan selama 10 detik\n\n");
            sleep(10);
            choice=0;
            AgmalCount=1;
            IrajCount=1;
            ThreadSleep=0;
        }
        else if(choice==3) {
            Spirit_Status-=20;
            printf("\nIraj Spirit Status -20\n\n");
            if(Spirit_Status<=0) {
                printf("\nIraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
                exit(0);
            }
            choice=0;
        }   
    }
}

void Menu(){
    while(1) {
        char input[1024];
        gets(input);

        if(!strcmp(input,"Status")) {
            Status();
        }
        else if(!strcmp(input,"Agmal Ayo Bangun")) {
            choice=2;
            if(AgmalCount!=0 && AgmalCount%3==0) {
                ThreadSleep=1;
                printf("\nFitur \"Iraj Ayo Tidur\" tidak bisa dijalankan selama 10 detik\n");
            }
            IrajCount=0;
            AgmalCount+=1;

           
        }
        else if(!strcmp(input,"Iraj Ayo Tidur")) {
            choice=3;
            if(IrajCount!=0 && IrajCount%3==0) {
                ThreadSleep=2;
                printf("\nFitur \"Agmal Ayo Bangun\" tidak bisa dijalankan selama 10 detik\n");
            }
            IrajCount++;
            AgmalCount=0;
        }
        else {
            printf("\nInput Salah\n\n");
        }
    }
}

int main(){
    pthread_t t_id[2];
    // pthread_create(&(t_id[3]),NULL,Menu,NULL);
    
    pthread_create(&(t_id[0]),NULL,AgmalAyoBangun,NULL);
    pthread_create(&(t_id[1]),NULL,IrajAyoTidur,NULL);
    Menu();
    // pthread_join(t_id[0],NULL);
    // pthread_join(t_id[1],NULL);
    
}
