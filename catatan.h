#ifndef CATATAN_H
#define CATATAN_H

// Struktur data untuk catatan
struct Catatan {
    int no;
    char judul[100];
    char tanggal[20];
    char isi[500];
};

void enkripsiVigenere(char teks[], char kunci[]);
void dekripsiVigenere(char teks[], char kunci[]);
struct Catatan buatCatatan(char *judul, char *tanggal, char *isi, char *kunciEnkripsi);
void tambahCatatanKeFile(struct Catatan catatanBaru);
int bacaCatatanDariFile(struct Catatan *catatan);
void tampilkanCatatan(struct Catatan *catatan, int jumlahCatatan);
void tampilkanIsiCatatanBerdasarkanJudul(struct Catatan *catatan, int jumlahCatatan, char *judul, char *kunciEnkripsi);
void simpanCatatanKeFile(struct Catatan *catatan, int jumlahCatatan);
void editCatatanBerdasarkanJudul(struct Catatan *catatan, int jumlahCatatan, char *judul, char *kunciEnkripsi);
void hapusCatatanBerdasarkanJudul(struct Catatan *catatan, int *jumlahCatatan, char *judul);


#endif
