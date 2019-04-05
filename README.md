# SoalShift_modul3_F10

## Jawaban Soal Shift Sistem Operasi 2019 

## Modul 3

Oleh: 

* 05111640000125 Fadhlan Aulia
* 05111740000019 Paramastri Ardiningrum

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
