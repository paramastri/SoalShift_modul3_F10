#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

pthread_t tid[6];

int main()
{

void* save1()  {system("ps -aux | head -n 10 > /home/paramastri/Documents/FolderProses1/SimpanProses1.txt");return 0;}
void* save2()  {system("ps -aux | head -n 10 > /home/paramastri/Documents/FolderProses2/SimpanProses2.txt");return 0;}
void* zip1()   {system("zip -rm -j KompresProses1 /home/paramastri/Documents/FolderProses1/SimpanProses1.txt");return 0;}
void* zip2()   {system("zip -rm -j KompresProses2 /home/paramastri/Documents/FolderProses2/SimpanProses2.txt");return 0;}
void* unzip1() {system("unzip /home/paramastri/sisop19/modul3/KompresProses1.zip -d /home/paramastri/sisop19/modul3/");return 0;}
void* unzip2() {system("unzip /home/paramastri/sisop19/modul3/KompresProses2.zip -d /home/paramastri/sisop19/modul3/");return 0;}

pthread_create(&tid[1],NULL,&save1,NULL);
pthread_create(&tid[2],NULL,&save2,NULL);

pthread_join(tid[1],NULL);
pthread_join(tid[2],NULL);

pthread_create(&tid[3],NULL,&zip1,NULL);
pthread_create(&tid[4],NULL,&zip2,NULL);

pthread_join(tid[3],NULL);
pthread_join(tid[4],NULL);

sleep(15);

pthread_create(&tid[5],NULL,&unzip1,NULL);
pthread_create(&tid[6],NULL,&unzip2,NULL);

pthread_join(tid[5],NULL);
pthread_join(tid[6],NULL);

  return 0;
}


