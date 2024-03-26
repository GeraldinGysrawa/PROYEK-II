#ifndef GERALDIN_H
#define GERALDIN_H

#define MAX_KEY 100
#define MAX_CATATAN 100

struct Catatan {
    int no;
    char judul[100];
    char tanggal[11];
    char isi[1000];
};

//geraldin
void enkripsiVigenere(char teks[], char kunci[]);
void tambahCatatan();

#endif 
