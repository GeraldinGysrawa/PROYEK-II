#include "allmodul.h"
#include <stdio.h>

int nomorCatatanTerakhir = 0;

void tambahCatatan() {

    FILE *file = fopen("Catatan.txt", "a");
    if (file == NULL) {
        printf("Error: Gagal membuka file.\n");
        return;
    }

    struct Catatan catatan;
    nomorCatatanTerakhir++;        

    catatan.no = nomorCatatanTerakhir;

    printf("Masukkan judul catatan: ");
    scanf(" %[^\n]s", catatan.judul);

    printf("Masukkan tanggal catatan (DD/MM/YYYY): ");
    scanf(" %[^\n]s", catatan.tanggal);

    printf("Masukkan isi catatan:\n");
    scanf(" %[^\n]s", catatan.isi);

    char kunci[MAX_KEY];
    printf("Masukkan kunci enkripsi: ");
    scanf(" %[^\n]s", kunci);

    enkripsi(catatan.judul, kunci);
    enkripsi(catatan.isi, kunci);
    
    fprintf(file, "%d|%s|%s|%s\n", catatan.no, catatan.judul, catatan.tanggal, catatan.isi);

    fclose(file);

    printf("Catatan berhasil ditambahkan.\n");
}
