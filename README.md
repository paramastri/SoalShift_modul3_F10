# SoalShift_modul3_F10

## Jawaban Soal Shift Sistem Operasi 2019 

## Modul 3

Oleh: 

* 05111640000125 Fadhlan Aulia
* 05111740000019 Paramastri Ardiningrum


## Daftar Isi
* [1. Faktorial](#1-faktorial)
* [2. Penjual Pembeli yang Terintegrasi secara Online](#2-penjual-pembeli-yang-terintegrasi-secara-online)
* [3. Thread Kehidupan Agmal dan Iraj](#3-thread-kehidupan-agmal-dan-iraj)
* [4. Simpan, Zip, Unzip](#4-simpan-zip-unzip)
* [5. Monster](#5-monster)


## 1. Faktorial
#### Penjelasan
##### Soal:
Buatlah program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan

Contoh:
	
	./faktorial 5 3 4
	
	3! = 6
	
	4! = 24
	
	5! = 120

##### Solusi:

Pertama, kita deklarasikan variabel global untuk threadnya misal input[100], kemudian variabel untuk menampung input di parameter misal t[100], dan juga variabel x untuk iterasi threadnya nanti.

```
pthread_t input[100];
int t[100];
int x;
```

Lalu, buat fungsi faktorial() yang dimana berisi algoritma yang menghasilkan output bilangan faktorial. Bermodalkan operasi perkalian yang diberi perulangan. Diberikan juga printf untuk menampilkan hasil faktorialnya.

```
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
```

Pada main program yang diberikan parameter variabel argc (argumen jumlah parameter yang dipassing) dan argv[] yang digunakan untuk menampung sejumlah parameter tadi.

misal:
``
./soal1 3 5 2
``
argc nya 4.

Kita deklarasikan variabelnya:

```
int n = argc-1, a, b, iter, tukar;
```

Ada perulangan sejumlah argc-1 yang akan mengubah angka yang diinputkan dimana awalnya merupakan char, lalu diubah menjadi integer supaya dapat diproses setelahnya. Ini menggunakan fungsi atoi.
```
for(iter = 0; iter < n; iter++)
	{
		t[iter] = atoi(argv[iter+1]);
	}
``` 

Kami membuat sorting menggunakan bubble sort untuk mengurutkan outputnya nanti. Bubble sort adalah metode/algoritma pengurutan dengan dengan cara melakukan penukaran data dengan tepat disebelahnya secara terus menerus sampai bisa dipastikan dalam satu iterasi tertentu tidak ada lagi perubahan. Jika tidak ada perubahan berarti data sudah terurut.

```
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
```

Terakhir, gunakan variabel x tadi untuk iterasi pembuatan threadnya. Jangan lupa juga gunakan join thread.
```
	for(x = 0; x < n; x++)
	{
		pthread_create(&(input[x]),NULL,&faktorial,NULL);
	 	pthread_join(input[x], NULL);
	}
```

![alt text](https://github.com/paramastri/SoalShift_modul3_F10/blob/master/soal1/1.PNG)

## 2. Penjual Pembeli yang Terintegrasi secara Online
#### Penjelasan
##### Soal:
Pada suatu hari ada orang yang ingin berjualan 1 jenis barang secara private, dia memintamu membuat program C dengan spesifikasi sebagai berikut:
	* Terdapat 2 server: server penjual dan server pembeli
	* 1 server hanya bisa terkoneksi dengan 1 client
	* Server penjual dan server pembeli memiliki stok barang yang selalu sama
	* Client yang terkoneksi ke server penjual hanya bisa menambah stok
	   - Cara menambah stok: client yang terkoneksi ke server penjual mengirim string “tambah” ke server lalu stok bertambah 1
	* Client yang terkoneksi ke server pembeli hanya bisa mengurangi stok
	   - Cara mengurangi stok: client yang terkoneksi ke server pembeli mengirim string “beli” ke server lalu stok berkurang 1
	* Server pembeli akan mengirimkan info ke client yang terhubung dengannya apakah transaksi berhasil atau tidak berdasarkan ketersediaan 	  stok
	   - Jika stok habis maka client yang terkoneksi ke server pembeli akan mencetak “transaksi gagal”
	   - Jika stok masih ada maka client yang terkoneksi ke server pembeli akan mencetak “transaksi berhasil”
	* Server penjual akan mencetak stok saat ini setiap 5 detik sekali
	
##### Solusi:
Pertama, Membuat sebuah server yaitu untuk Pembeli dan Penjual.
Kedua server ini harus terhubung dengan masing-masing client agar mereka dapat melakukan suatu transaksi, diberikan 2 Client yaitu untuk pembeli dan Penjual.

Server Penjual dapat melakukan Penambahan Stock.
diberikan sebuah thread guna mencetak keterangan stock barang dan mengecek apabila client penjual melakukan penambahan stock  
```
void* cek (void* arg)
{
        if(strcmp(buffer,"tambah")==0)
        {
                *stok = *stok + 1;
        }
        
        memset(buffer, 0, 1024);
}

void* cetak (void* arg)
{
    while(1)
    {
        printf("Stock barang %d\n",*stok);
        sleep(5);
    }
    
}
```

Server Pembeli dapat melakukan pembelian sehingga terjadi Pengurangan Stock.
diberikan thread untuk mengecek apakah client pembeli melakukan pembelian, sekaligus memberi notifikasi transaksi tersebut
```
void* cek (void* arg)
{
    char *pesangagal = "transaksi gagal";
    char *pesansukses = "transaksi berhasil";
    char *pesangagal1 = "perintah salah";
    if(strcmp(buffer,"beli")==0)
    {
        if(*stok > 0)
        {
            *stok = *stok - 1;
            printf("%s\n",pesansukses);
            send(new_socket , pesansukses , strlen(pesansukses) , 0 );
        }
        else
        {
            printf("%s\n",pesangagal);
            send(new_socket , pesangagal , strlen(pesangagal) , 0 );
        }
    }
    else
    {
        printf("%s\n",pesangagal1);
        send(new_socket , pesangagal1 , strlen(pesangagal1) , 0 );
    }
        
    memset(buffer, 0, 1024);
}
```
Client Pembeli dan Penjual hanya sebagai penginput String yang String tersebut dicek pada masing-masing servernya.

## 3. Thread Kehidupan Agmal dan Iraj
#### Penjelasan
##### Soal:
Agmal dan Iraj merupakan 2 sahabat yang sedang kuliah dan hidup satu kostan, sayangnya mereka mempunyai gaya hidup yang berkebalikan, dimana Iraj merupakan laki-laki yang sangat sehat,rajin berolahraga dan bangun tidak pernah kesiangan sedangkan Agmal hampir menghabiskan setengah umur hidupnya hanya untuk tidur dan ‘ngoding’. Dikarenakan mereka sahabat yang baik, Agmal dan iraj sama-sama ingin membuat satu sama lain mengikuti gaya hidup mereka dengan cara membuat Iraj sering tidur seperti Agmal, atau membuat Agmal selalu bangun pagi seperti Iraj. Buatlah suatu program C untuk menggambarkan kehidupan mereka  dengan spesifikasi sebagai berikut:
* Terdapat 2 karakter Agmal dan Iraj
* Kedua karakter memiliki status yang unik
  - Agmal mempunyai WakeUp_Status, di awal program memiliki status 0
  - Iraj memiliki Spirit_Status, di awal program memiliki status 100
* Terdapat 3 Fitur utama
  - All Status, yaitu menampilkan status kedua sahabat
    Ex: Agmal WakeUp_Status = 75 
        Iraj Spirit_Status = 30
  - “Agmal Ayo Bangun” menambah WakeUp_Status Agmal sebesar 15 point
  - “Iraj Ayo Tidur” mengurangi Spirit_Status Iraj sebanyak 20 point
* Terdapat Kasus yang unik dimana:
  - Jika Fitur “Agmal Ayo Bangun” dijalankan sebanyak 3 kali, maka Fitur “Iraj Ayo Tidur” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Fitur Iraj Ayo Tidur disabled 10 s”)
  - Jika Fitur  “Iraj Ayo Tidur” dijalankan sebanyak 3 kali, maka Fitur “Agmal Ayo Bangun” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Agmal Ayo Bangun disabled 10 s”)
* Program akan berhenti jika Salah Satu :
  - WakeUp_Status Agmal >= 100 (Tampilkan Pesan “Agmal Terbangun,mereka bangun pagi dan berolahraga”)
  - Spirit_Status Iraj <= 0 (Tampilkan Pesan “Iraj ikut tidur, dan bangun kesiangan bersama Agmal”)

###### Solusi:
* Membuat 2 Thread yang dimana Thread tersebut berisi Kehidupan Agmal dan dan Kehidupan Iraj.
* Thread Agmal
```
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
```
* Thread Iraj
```
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
```
* Membuat sebuah Interface untuk menjalankan Program Mereka serta melihat kedua status mereka. 
```
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
```



## 4. Simpan, Zip, Unzip
#### Penjelasan
##### Soal:
Buatlah sebuah program C dimana dapat menyimpan list proses yang sedang berjalan (ps -aux) maksimal 10 list proses. Dimana awalnya list proses disimpan dalam di 2 file ekstensi .txt yaitu  SimpanProses1.txt di direktori /home/Document/FolderProses1 dan SimpanProses2.txt di direktori /home/Document/FolderProses2 , setelah itu masing2 file di  kompres zip dengan format nama file KompresProses1.zip dan KompresProses2.zip dan file SimpanProses1.txt dan SimpanProses2.txt akan otomatis terhapus, setelah itu program akan menunggu selama 15 detik lalu program akan mengekstrak kembali file KompresProses1.zip dan KompresProses2.zip 

Dengan Syarat : 
* Setiap list proses yang di simpan dalam masing-masing file .txt harus berjalan bersama-sama
* Ketika mengkompres masing-masing file .txt harus berjalan bersama-sama
* Ketika Mengekstrak file .zip juga harus secara bersama-sama
* Ketika Telah Selesai melakukan kompress file .zip masing-masing file, maka program akan memberi pesan “Menunggu 15 detik untuk mengekstrak kembali”
* Wajib Menggunakan Multithreading
* Boleh menggunakan system


##### Solusi:

Pertama, kita deklarasikan variabel global untuk threadnya misal tid[6]. Disini kami memberi nilai array 6 karena akan ada 6 thread yang akan kami buat.

```
pthread_t tid[6];
```
Pada main program, terdapat fungsi-fungsi yang akan menjalankan perintah-perintah sesuai pada soal.

* Untuk menyimpan list proses yang sedang berjalan (ps -aux) maksimal 10 list proses, kami menggunakan ``ps -aux | head -n 10``

* Untuk menyimpan di 2 file ekstensi .txt yaitu SimpanProses1.txt di direktori /home/Document/FolderProses1 dan SimpanProses2.txt di direktori /home/Document/FolderProses2, kami menggunakan ``> /home/paramastri/Documents/FolderProses1/SimpanProses1.txt``

Dan perintah-perintah tersebut kami mesukkan dalam fungsi system().

```
void* save1()  {system("ps -aux | head -n 10 > /home/paramastri/Documents/FolderProses1/SimpanProses1.txt");return 0;}
void* save2()  {system("ps -aux | head -n 10 > /home/paramastri/Documents/FolderProses2/SimpanProses2.txt");return 0;}
```

* Untuk membuat masing2 file di kompres zip dengan format nama file KompresProses1.zip dan KompresProses2.zip dan file SimpanProses1.txt dan SimpanProses2.txt akan otomatis terhapus, kami menggunakan ``zip -rm -j KompresProses1 /home/paramastri/Documents/FolderProses1/SimpanProses1.txt``

-rm digunakan supaya kedua file .txt tadi otomatis terhapus setelah di zip.

-j sebagai junk yang membuang direktori. Jadi, sebelum kami beri -j, file zip ketika melalui proses unzip, mereka akan membuat folder sesuai dengan direktori ``/home/paramastri/Documents/FolderProses1/SimpanProses1.txt`` dan menyimpan hasil ekstrak pada direktori tersebut. Untuk itu, kami memberi command -j ini.

* Hasil file zip kami akan muncul pada direktori dimana soal4.c dijalankan.

Dan perintah-perintah tersebut kami mesukkan dalam fungsi system().

```
void* zip1()   {system("zip -rm -j KompresProses1 /home/paramastri/Documents/FolderProses1/SimpanProses1.txt");return 0;}
void* zip2()   {system("zip -rm -j KompresProses2 /home/paramastri/Documents/FolderProses2/SimpanProses2.txt");return 0;}
```

* Untuk mengekstrak file zip tadi, kami menggunakan ``unzip /home/paramastri/sisop19/modul3/KompresProses1.zip -d /home/paramastri/sisop19/modul3/``

* Hasil ekstrak (.txt) nya akan muncul di path ``/home/paramastri/sisop19/modul3/`` dimana kami menjalankan soal4.c

Dan perintah tersebut kami mesukkan dalam fungsi system().

```
void* unzip1() {system("unzip /home/paramastri/sisop19/modul3/KompresProses1.zip -d /home/paramastri/sisop19/modul3/");return 0;}
void* unzip2() {system("unzip /home/paramastri/sisop19/modul3/KompresProses2.zip -d /home/paramastri/sisop19/modul3/");return 0;}
```

Karena setiap list proses yang di simpan dalam masing-masing file .txt harus berjalan bersama-sama, kami membuat thread dengan memanggil fungsi save1 dan save2, lalu di-join-kan.

```
pthread_create(&tid[1],NULL,&save1,NULL);
pthread_create(&tid[2],NULL,&save2,NULL);

pthread_join(tid[1],NULL);
pthread_join(tid[2],NULL);
```

Karena ketika mengkompres file .zip juga harus secara bersama-sama. Sehingga, kami membuat thread dengan memanggil fungsi zip1 dan zip2, lalu di-join-kan.

```
pthread_create(&tid[3],NULL,&zip1,NULL);
pthread_create(&tid[4],NULL,&zip2,NULL);

pthread_join(tid[3],NULL);
pthread_join(tid[4],NULL);
```

Ketika Mengekstrak file .zip juga harus secara bersama-sama. Dan ketika telah Selesai melakukan kompress file .zip masing-masing file, maka program akan memberi pesan “Menunggu 15 detik untuk mengekstrak kembali”.

Sehingga, kami membuat thread dengan memanggil fungsi unzip1 dan unzip2, lalu di-join-kan. Dan tidak lupa memberikan sleep(15). Serta mengeprint pesan “Menunggu 15 detik untuk mengekstrak kembali”.

```
printf("Menunggu 15 detik untuk mengekstrak kembali\n");
  
sleep(15);

pthread_create(&tid[5],NULL,&unzip1,NULL);
pthread_create(&tid[6],NULL,&unzip2,NULL);

pthread_join(tid[5],NULL);
pthread_join(tid[6],NULL);
```

Pada gambar di bawah ini, dapat dilihat setelah program dijalankan, dia akan memngompres dan mengekstrak (ditunggu 15 detik). Dan dapat dilihat juga file original pada Documents/FolderProses1 dan Documents/FolderProses2 sudah terhapus otomatis.

![alt text](https://github.com/paramastri/SoalShift_modul3_F10/blob/master/soal4/4.PNG)


## 5. Monster
#### Penjelasan
##### Soal:
Angga, adik Jiwang akan berulang tahun yang ke sembilan pada tanggal 6 April besok. Karena lupa menabung, Jiwang tidak mempunyai uang sepeserpun untuk membelikan Angga kado. Kamu sebagai sahabat Jiwang ingin membantu Jiwang membahagiakan adiknya sehingga kamu menawarkan bantuan membuatkan permainan komputer sederhana menggunakan program C. Jiwang sangat menyukai idemu tersebut. Berikut permainan yang Jiwang minta. 

Pemain memelihara seekor monster lucu dalam permainan. Pemain dapat  memberi nama pada monsternya.

Monster pemain memiliki hunger status yang berawal dengan nilai 200 (maksimalnya) dan nanti akan berkurang 5 tiap 10 detik.Ketika hunger status mencapai angka nol, pemain akan kalah. Hunger status dapat bertambah 15 apabila pemain memberi makan kepada monster, tetapi banyak makanan terbatas dan harus beli di Market.

Monster pemain memiliki hygiene status yang berawal dari 100 dan nanti berkurang 10 tiap 30 detik. Ketika hygiene status mencapai angka nol, pemain akan kalah. Hygiene status' dapat bertambah 30 hanya dengan memandikan monster. Pemain dapat memandikannya setiap 20 detik(cooldownnya 20 detik).

Monster pemain memiliki health status yang berawal dengan nilai 300. Variabel ini bertambah (regenerasi)daa 5 setiap 10 detik ketika monster dalam keadaan standby.

Monster pemain dapat memasuki keadaan battle. Dalam keadaan ini, food status(fitur b), hygiene status'(fitur c), dan ‘regenerasi’(fitur d) tidak akan berjalan. Health status dari monster dimulai dari darah saat monster pemain memasuki battle. Monster pemain akan bertarung dengan monster NPC yang memiliki darah 100. Baik monster pemain maupun NPC memiliki serangan sebesar 20. Monster pemain dengan monster musuh akan menyerang secara bergantian. 

Fitur shop, pemain dapat membeli makanan sepuas-puasnya selama stok di toko masih tersedia.
Pembeli (terintegrasi dengan game)
Dapat mengecek stok makanan yang ada di toko.
Jika stok ada, pembeli dapat membeli makanan.

Penjual (terpisah)
Bisa mengecek stok makanan yang ada di toko.
Penjual dapat menambah stok makanan.

Spesifikasi program:

Program mampu mendeteksi input berupa key press. (Program bisa berjalan tanpa perlu menekan tombol enter)

Program terdiri dari 3 scene yaitu standby, battle, dan shop.

Pada saat berada di standby scene, program selalu menampilkan health status, hunger status, hygiene status, stok makanan tersisa, dan juga status kamar mandi (“Bath is ready” jika bisa digunakan, “Bath will be ready in [bath cooldown]s” jika sedang cooldown). Selain itu program selalu menampilkan 5 menu, yaitu memberi makan, mandi, battle, shop, dan exit. Contoh :

Standby Mode
* Health : [health status]
* Hunger : [hunger status]
* Hygiene : [hygiene status]
* Food left : [your food stock]
* Bath will be ready in [cooldown]s
Choices

1. Eat
2. Bath
3. Battle
4. Shop
5. Exit

Pada saat berada di battle scene, program selalu menampilkan health status milik pemain dan monster NPC. Selain itu, program selalu menampilkan 2 menu yaitu serang atau lari. Contoh :

Battle Mode
* Monster’s Health : [health status]
* Enemy’s Health : [enemy health status]

Choices

1. Attack
2. Run

Pada saat berada di shop scene versi pembeli, program selalu menampilkan food stock toko dan milik pemain. Selain itu, program selalu menampilkan 2 menu yaitu beli dan kembali ke standby scene. Contoh :

Shop Mode

* Shop food stock : [shop food stock]
* Your food stock : [your food stock]

Choices

1. Buy
2. Back

Pada program penjual, program selalu menampilkan food stock toko. Selain itu, program juga menampilkan 2 menu yaitu restock dan exit. Contoh :

Shop
* Food stock : [shop food stock]

Choices

1. Restock
2. Exit

Pastikan terminal hanya mendisplay status detik ini sesuai scene terkait (hint: menggunakan system(“clear”))

##### Solusi:

Ada library tambahan yaitu ``#include<termios.h>``. Gunanya untuk mendeteksi input keypress.

```
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
```

Kita deklarasikan variabel dan nilainya.

```
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
```

Fungsi void dibawah ini adalah untuk memenuhi syarat monster pemain memiliki hunger status yang berawal dengan nilai 200 (maksimalnya) dan nanti akan berkurang 5 tiap 10 detik.

Detik kelaparannya yang dideklarasikan awal 10, apabila tidak memenuhi if(det_hung==1) maka dia di-decreament hingga detiknya kembali ke 1, maka memenuhi if(det_hung==1) dan direset lagi menjadi 10 serta Hungry Statusnya berkurang 5.
```
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

```

Fungsi void dibawah ini adalah untuk memenuhi syarat monster pemain memiliki hygiene status yang berawal dari 100 dan nanti berkurang 10 tiap 30 detik. 

Detik kelaparannya yang dideklarasikan awal 30, apabila tidak memenuhi if(det_hyg==1) maka dia di-decreament hingga detiknya kembali ke 1, maka memenuhi if(det_hyg==1) dan direset lagi menjadi 10 serta Hygiene Statusnya berkurang 10.

```
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

```

Fungsi void dibawah ini adalah untuk memenuhi syarat monster pemain memiliki health status yang berawal dengan nilai 300. Variabel ini bertambah (regenerasi) 5 setiap 10 detik ketika monster dalam keadaan standby.


Detik kelaparannya yang dideklarasikan awal 30, apabila tidak memenuhi if(det_health==1) maka dia di-increament hingga detiknya kembali ke 1, maka memenuhi if(det_health==1) dan direset lagi menjadi 10 serta Hygiene Statusnya bertambah 5.

```
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
```
Ketika hygiene status mencapai angka nol, pemain akan kalah. Hygiene status' dapat bertambah 30 hanya dengan memandikan monster. Pemain dapat memandikannya setiap 20 detik (cooldownnya 20 detik).

```
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
```
Untuk build fitur shop, kami menggunakan shared memory
```
int *maem_shop;
void* ini_shop (void* arg){
    key_t key = 1234;


    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    maem_shop = shmat(shmid, NULL, 0);

    *maem_shop = 0;
}
```

Thread-thread yang dibuat:
```
    pthread_create(&(thread[0]),NULL,laper,NULL);
    pthread_create(&(thread[1]),NULL,hyginis,NULL);
    pthread_create(&(thread[2]),NULL,sehat,NULL);
    pthread_create(&(thread[3]),NULL,itungan_mandi,NULL);
    pthread_create(&(thread[4]),NULL,tampilan_asli,NULL);
    pthread_create(&(thread[5]),NULL,ini_shop,NULL);
    pthread_create(&(thread[6]),NULL,tampilan_food,NULL);
```

Apabila pemain memilih fitur 1 yaitu Eat, hungry status akan bertambah 15 sementara stok makanan kita berkurang.

```
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
```
Apabila pemain memilih fitur 2 yaitu Bath, hygiene status akan bertambah 30.
```
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
```

Apabila memilih 3 untuk fitur battle, setiap kita memilih attack, status kesehatan lawan dan kita berkurang 20.

```
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
```

Apabila memilih 4 untuk fitur shop, akan dijeda ke menu shop yang jika kita pilih Buy akan menambah stok makanan kita dan mengurangi stok makanan toko
```
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
```

Yang terakhir jika memilih 5, program akan keluar

```
else if(choose=='5')
        {
            system("clear");
            printf("Thanks for playing!\n");
            exit(EXIT_FAILURE);
            break;
        }
```

Jangan lupa menjoinkan threadnya

```
pthread_join(thread[0],NULL);
    pthread_join(thread[1],NULL);
    pthread_join(thread[2],NULL);
    pthread_join(thread[3],NULL);
    pthread_join(thread[4],NULL);
    pthread_join(thread[5],NULL);
    pthread_join(thread[6],NULL);
```
Untuk soal5shop.c yang berguna memunculkan menu restock makanan dengan shared memory, berikut penjabarannya.

Pertama diberikan juga library tambahan yaitu ``#include<termios.h>``. Gunanya untuk mendeteksi input keypress. Dan juga diikuti dengan template fungsi-fungsi termios lainnya.

Fungsi untuk shared memory seperti di soal5.c

```
void* shop_ini (void* arg)
{
    key_t key = 1234;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    maem_shop = shmat(shmid, NULL, 0);
  
    *maem_shop = 0;

}
```

Fungsi untuk interface menu shopnya

```
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
```
Ketika memilih poin 1 yaitu Restock, stok makanan di toko akan bertambah. Yang dimana nantinya akan bisa dibeli pada shop menu di soal5.c
```
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
```

* Memberi nama monster


![alt text](https://github.com/paramastri/SoalShift_modul3_F10/blob/master/soal5/5-nama.PNG)


* Standby Mode


![alt text](https://github.com/paramastri/SoalShift_modul3_F10/blob/master/soal5/5-standby.PNG)


* Shop menu (shared memory implementation)


![alt text](https://github.com/paramastri/SoalShift_modul3_F10/blob/master/soal5/5-food.PNG)

![alt text](https://github.com/paramastri/SoalShift_modul3_F10/blob/master/soal5/5-food-2.PNG)


* Battle Mode


![alt text](https://github.com/paramastri/SoalShift_modul3_F10/blob/master/soal5/5-battle.PNG)


* Bath is ready


![alt text](https://github.com/paramastri/SoalShift_modul3_F10/blob/master/soal5/5-bath.PNG)
