////tambahcatatan.c
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
//#include <time.h>
//#include "catatan.h"
//#include "LoginRegister.h"
//
//
////int nomorCatatanTerakhir = 0;
//
//void tambahCatatan() {
//    FILE *file = fopen("Catatan.txt", "a");
//    if (file == NULL) {
//        printf("Error: Gagal membuka file.\n");
//        return;
//    }
//
//    struct Catatan catatan;
//    nomorCatatanTerakhir++;        
//
//    catatan.no = nomorCatatanTerakhir;
//
//    printf("\tMasukkan judul catatan: ");
//    scanf(" %[^\n]s", catatan.judul);
//
//    // Ambil tanggal saat ini
//    time_t rawtime;
//    struct tm *info;
//    char buffer[11];
//    time(&rawtime);
//    info = localtime(&rawtime);
//    strftime(buffer, sizeof(buffer), "%d/%m/%Y", info);
//    strcpy(catatan.tanggal, buffer);
//
//    printf("\tMasukkan isi catatan:\n");
//    scanf(" %[^\n]s", catatan.isi);
//
//     // proses enkripsi
//      char kunci[MAX_KEY] = "PROYEK";
//      enkripsiVigenere(catatan.isi, kunci);
//    
//    fprintf(file, "%d|%s|%s|%s\n", catatan.no, catatan.judul, catatan.tanggal, catatan.isi);
//
//    fclose(file);
//
//    printf("\tCatatan berhasil ditambahkan.\n");
//}