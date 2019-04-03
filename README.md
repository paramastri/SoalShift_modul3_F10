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
