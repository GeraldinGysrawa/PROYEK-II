//catatan.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "catatan.h"
#include "LoginRegister.h"

int nomorCatatanTerakhir = 0;

void MenuUtama() {
    int pilihan;
    char judul[100];

    do {
        hapusLayar(); // Clear console screen
        printf("\t\t\t\t===================================\n");
        printf("\t\t\t\t          Menu Utama\n");
        printf("\t\t\t\t===================================\n");
        printf("\t\t\t\t1. Tambah Catatan\n");
        printf("\t\t\t\t2. Tampil Daftar Catatan\n");
        printf("\t\t\t\t3. Tampil Isi Catatan\n");
        printf("\t\t\t\t4. Edit Catatan\n");
        printf("\t\t\t\t5. Hapus Catatan\n");
        printf("\t\t\t\t0. Keluar\n");
        printf("\t\t\t\t===================================\n");
        printf("\t\t\t\tPilihan Anda: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tambahCatatan();
                break;
            case 2:
                tampilDaftarCatatan();
                break;
            case 3:
                hapusLayar(); // Clear console screen
                tampilDaftarCatatan();
                printf("\t\t\t\tMasukkan judul catatan: ");
                scanf(" %[^\n]s", judul);
                tampilIsiCatatan(judul);
                break;
            case 4:
                hapusLayar(); // Clear console screen
                tampilDaftarCatatan();
                printf("\t\t\t\tMasukkan judul catatan yang ingin diedit: ");
                scanf(" %[^\n]s", judul);
                editCatatan(judul);
                break;
            case 5:
                hapusLayar(); // Clear console screen
                tampilDaftarCatatan();
                printf("\t\t\t\tMasukkan judul catatan yang ingin dihapus: ");
                scanf(" %[^\n]s", judul);
                hapusCatatan(judul);
                break;
            case 0:
                printf("\tKeluar...\n");
                break;
            default:
                printf("\t\t\t\tPilihan tidak valid.\n");
        }
        printf("\tTekan tombol 'Enter' untuk melanjutkan...");
        while (getchar() != '\n'); // Clear input buffer
        getchar(); // Wait for Enter key
    } while (pilihan != 0);
}

void hapusLayar() {
    system("cls"); 
}

void tambahCatatan() {
    FILE *file = fopen("Catatan.txt", "a");
    if (file == NULL) {
        printf("Error: Gagal membuka file.\n");
        return;
    }

    struct Catatan catatan;
    nomorCatatanTerakhir++;        

    catatan.no = nomorCatatanTerakhir;

    printf("\tMasukkan judul catatan: ");
    scanf(" %[^\n]s", catatan.judul);

    // Ambil tanggal saat ini
    time_t rawtime;
    struct tm *info;
    char buffer[11];
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", info);
    strcpy(catatan.tanggal, buffer);

    printf("\tMasukkan isi catatan:\n");
    scanf(" %[^\n]s", catatan.isi);

    //proses enkripsi
    char kunci[MAX_KEY] = "PROYEK";
    enkripsiVigenere(catatan.isi, kunci);
    
    enkripsiVigenere(catatan.isi, kunci);
    
    fprintf(file, "%d|%s|%s|%s\n", catatan.no, catatan.judul, catatan.tanggal, catatan.isi);

    fclose(file);

    printf("\tCatatan berhasil ditambahkan.\n");
}

void tampilDaftarCatatan() {
    FILE *file = fopen("Catatan.txt", "r");
    if (file == NULL) {
        printf("Error: Gagal membuka file.\n");
        return;
    }

    struct Catatan catatan[MAX_CATATAN];
    int count = 0;
    while (fscanf(file, "%d|%[^|]|%[^|]|%[^\n]\n", &catatan[count].no, catatan[count].judul, catatan[count].tanggal, catatan[count].isi) != EOF) {
        count++;
    }

    fclose(file);

    // Mengupdate nomor catatan
    for (int i = 0; i < count; i++) {
        catatan[i].no = i + 1;
    }

    // Urutkan catatan berdasarkan tanggal terbaru menggunakan bubble sort
    int i, j;
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            // Konversi tanggal dari format "DD/MM/YYYY" menjadi integer untuk perbandingan
            int tahun1, bulan1, hari1;
            int tahun2, bulan2, hari2;
            sscanf(catatan[j].tanggal, "%d/%d/%d", &hari1, &bulan1, &tahun1);
            sscanf(catatan[j + 1].tanggal, "%d/%d/%d", &hari2, &bulan2, &tahun2);

            // Bandingkan tahun
            if (tahun1 < tahun2 || (tahun1 == tahun2 && bulan1 < bulan2) || (tahun1 == tahun2 && bulan1 == bulan2 && hari1 < hari2)) {
                // Tukar posisi catatan
                struct Catatan temp = catatan[j];
                catatan[j] = catatan[j + 1];
                catatan[j + 1] = temp;
            }
        }
    }

    // Tampilkan daftar catatan yang sudah diurutkan
    printf("\t==============================================================\n");
    printf("\tNo\t| Judul\t\t\t\t| Tanggal\n");
    printf("\t==============================================================\n");
    for (i = 0; i < count; i++) {
        printf("\t%d\t| %-25s     | %-10s\n", catatan[i].no, catatan[i].judul, catatan[i].tanggal);
    }
    printf("\t==============================================================\n");

    if (count == 0) {
        printf("\tDaftar catatan kosong.\n");
    }
}



void tampilIsiCatatan(char judul[]) {
    FILE *file = fopen("Catatan.txt", "r");
    if (file == NULL) {
        printf("Error: Gagal membuka file.\n");
        return;
    }

    struct Catatan catatan;
    int found = 0;
    while (fscanf(file, "%d|%[^|]|%[^|]|%[^\n]\n", &catatan.no, catatan.judul, catatan.tanggal, catatan.isi) != EOF) {
        if (strcmp(catatan.judul, judul) == 0) {
            found = 1;
            printf("\t====================================\n");
            printf("\tJudul: %s\n", catatan.judul);
            printf("\tTanggal: %s\n", catatan.tanggal);
            printf("\tIsi:\n");
            
            // Baca kunci enkripsi dari pengguna
            char kunci[MAX_KEY] = "PROYEK";
            dekripsiVigenere(catatan.isi, kunci);
            
            // Tampilkan isi catatan yang telah didekripsi dengan format vertikal
            char *token = strtok(catatan.isi, "\n");
            while (token != NULL) {
                printf("\t- %s\n", token);
                token = strtok(NULL, "\n");
            }
            printf("\t====================================\n");
            break;
        }
    }

    fclose(file);
    if (!found) {
        printf("\tCatatan dengan judul '%s' tidak ditemukan.\n", judul);
    }
}


void editCatatan(char judul[]) {
    int i, j;

    FILE *file = fopen("Catatan.txt", "r");
    if (file == NULL) {
        printf("Error: Gagal membuka file.\n");
        return;
    }

    struct Catatan catatan[MAX_CATATAN];
    int count = 0;
    while (fscanf(file, "%d|%[^|]|%[^|]|%[^\n]\n", &catatan[count].no, catatan[count].judul, catatan[count].tanggal, catatan[count].isi) != EOF) {
        count++;
    }

    fclose(file);

    int found = 0;
    for (i = 0; i < count; i++) {
        if (strcmp(catatan[i].judul, judul) == 0) {
            found = 1;
            printf("\tCatatan ditemukan.\n");
            printf("\tApa yang ingin Anda edit?\n");
            printf("\t1. Judul\n");
            printf("\t2. Isi\n");
            printf("\tPilihan Anda: ");
            int pilihanEdit;
            scanf("%d", &pilihanEdit);

            switch (pilihanEdit) {
                case 1:
                    printf("\tMasukkan judul baru: ");
                    scanf(" %[^\n]s", catatan[i].judul);
                    // Perbarui tanggal saat ini
                    time_t rawtime;
                    struct tm *info;
                    char buffer[11];
                    time(&rawtime);
                    info = localtime(&rawtime);
                    strftime(buffer, sizeof(buffer), "%d/%m/%Y", info);
                    strcpy(catatan[i].tanggal, buffer);
                    break;
                case 2:
                    printf("\tMasukkan isi baru:\n");
                    scanf(" %[^\n]s", catatan[i].isi);
                    // Perbarui tanggal saat ini
                    time(&rawtime);
                    info = localtime(&rawtime);
                    strftime(buffer, sizeof(buffer), "%d/%m/%Y", info);
                    strcpy(catatan[i].tanggal, buffer);
                    //// Baca kunci enkripsi dari pengguna
                    char kunci[MAX_KEY] = "PROYEK";
                    enkripsiVigenere(catatan[i].isi, kunci);
                    break;
                default:
                    printf("\tPilihan tidak valid.\n");
                    return;
            }

            printf("\tApakah Anda yakin ingin menyimpan perubahan? (Y/N): ");
            char konfirmasi;
            scanf(" %c", &konfirmasi);
            if (konfirmasi == 'Y' || konfirmasi == 'y') {
                FILE *file = fopen("Catatan.txt", "w");
                if (file == NULL) {
                    printf("Error: Gagal membuka file.\n");
                    return;
                }

                for (j = 0; j < count; j++) {
                    fprintf(file, "%d|%s|%s|%s\n", catatan[j].no, catatan[j].judul, catatan[j].tanggal, catatan[j].isi);
                }

                fclose(file);

                printf("\tCatatan berhasil diubah.\n");
            } else {
                printf("\tPerubahan dibatalkan.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("\tCatatan dengan judul '%s' tidak ditemukan.\n", judul);
    }
}



void hapusCatatan(char judul[]) {
    
    int i,j;
    
    FILE *file = fopen("Catatan.txt", "r");
    if (file == NULL) {
        printf("Error: Gagal membuka file.\n");
        return;
    }

    struct Catatan catatan[MAX_CATATAN];
    int count = 0;
    while (fscanf(file, "%d|%[^|]|%[^|]|%[^\n]\n", &catatan[count].no, catatan[count].judul, catatan[count].tanggal, catatan[count].isi) != EOF) {
        count++;
    }

    fclose(file);

    int found = 0;
    for (i = 0; i < count; i++) {
        if (strcmp(catatan[i].judul, judul) == 0) {
            found = 1;
            for (j = i; j < count - 1; j++) {
                catatan[j] = catatan[j + 1];
            }
            count--;

            FILE *file = fopen("Catatan.txt", "w");
            if (file == NULL) {
                printf("Error: Gagal membuka file.\n");
                return;
            }

            for (j = 0; j < count; j++) {
                fprintf(file, "%d|%s|%s|%s\n", catatan[j].no, catatan[j].judul, catatan[j].tanggal, catatan[j].isi);
            }

            fclose(file);

            printf("\tCatatan berhasil dihapus.\n");
            break;
        }
    }

    if (!found) {
        printf("\tCatatan dengan judul '%s' tidak ditemukan.\n", judul);
    }
}

