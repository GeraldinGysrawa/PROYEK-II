#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Vigenere cipher function
void enkripsiVigenere(char teks[], char kunci[]) {
    int teksLen = strlen(teks);
    int kunciLen = strlen(kunci);
    int i, j;

    for (i = 0, j = 0; i < teksLen; ++i) {
        if (isalpha(teks[i])) {
            int shift = tolower(kunci[j % kunciLen]) - 'a';
            int base = islower(teks[i]) ? 'a' : 'A';
            teks[i] = ((teks[i] - base + shift) % 26 + base);
            j++;
        }
    }
}


void dekripsiVigenere(char teks[], char kunci[]) {
    int teksLen = strlen(teks);
    int kunciLen = strlen(kunci);
    int i, j;

    for (i = 0, j = 0; i < teksLen; ++i) {
        if (isalpha(teks[i])) {
            int shift = tolower(kunci[j % kunciLen]) - 'a';
            int base = islower(teks[i]) ? 'a' : 'A';
            teks[i] = ((teks[i] - base - shift + 26) % 26 + base);
            j++;
        }
    }
}


// Struktur data untuk catatan
struct Catatan {
    int no;
    char judul[100];
    char tanggal[20];
    char isi[500];
};

// Variabel global untuk menyimpan no catatan terakhir
int idCatatanTerakhir = 0;

// Fungsi bantuan untuk membandingkan dua catatan berdasarkan tanggal
int bandingkanCatatan(const void *a, const void *b) {
    struct Catatan *catatanA = (struct Catatan *)a;
    struct Catatan *catatanB = (struct Catatan *)b;
    return strcmp(catatanB->tanggal, catatanA->tanggal); // Urutkan secara descending berdasarkan tanggal
}


// Fungsi untuk membuat catatan baru dengan enkripsi Vigenere
struct Catatan buatCatatan(char *judul, char *tanggal, char *isi, char *kunciEnkripsi) {
    struct Catatan catatanBaru;
    strcpy(catatanBaru.judul, judul);
    strcpy(catatanBaru.tanggal, tanggal);
    strcpy(catatanBaru.isi, isi);
    
    // Encrypt note content using Vigenere cipher
    enkripsiVigenere(catatanBaru.isi, kunciEnkripsi);

    return catatanBaru;
}

// Fungsi untuk menambahkan catatan ke dalam file
void tambahCatatanKeFile(struct Catatan catatanBaru) {
    FILE *file = fopen("Catatan.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    fprintf(file, "%d|%s|%s|%s\n", catatanBaru.no, catatanBaru.judul, catatanBaru.tanggal, catatanBaru.isi);
    fclose(file);
}

// Fungsi untuk membaca catatan dari file dan menyimpannya dalam array
int bacaCatatanDariFile(struct Catatan *catatan) {
    FILE *file = fopen("Catatan.txt", "r");
    if (file == NULL) {
        printf("Tidak ada catatan yang tersedia.\n");
        return 0;
    }
    int jumlahCatatan = 0;
    struct Catatan temp;
    while (fscanf(file, "%d|%[^|]|%[^|]|%[^\n]\n", &temp.no, temp.judul, temp.tanggal, temp.isi) != EOF) {
        catatan[jumlahCatatan] = temp;
        jumlahCatatan++;
        // Update nilai idCatatanTerakhir jika no catatan yang dibaca lebih besar
        if (temp.no > idCatatanTerakhir) {
            idCatatanTerakhir = temp.no;
        }
    }
    fclose(file);
    return jumlahCatatan;
}

// Fungsi untuk menampilkan daftar catatan dengan judul dan tanggal, diurutkan berdasarkan tanggal terbaru
void tampilkanCatatan(struct Catatan *catatan, int jumlahCatatan) {
    // Mengurutkan catatan berdasarkan tanggal terbaru
    qsort(catatan, jumlahCatatan, sizeof(struct Catatan), bandingkanCatatan);
    // Menampilkan daftar catatan yang telah diurutkan
    printf("\t\t\tNo.  | Judul               | Tanggal\n");
    printf("\t\t\t--------------------------------------\n");
    for (int i = 0; i < jumlahCatatan; i++) {
        printf("\t\t\t%-5d| %-20s| %s\n", i + 1, catatan[i].judul, catatan[i].tanggal);
    }
    printf("\t\t\t--------------------------------------\n");
}

// Fungsi untuk menampilkan isi catatan dengan dekripsi Vigenere
void tampilkanIsiCatatanBerdasarkanJudul(struct Catatan *catatan, int jumlahCatatan, char *judul, char *kunciEnkripsi) {
    int ditemukan = 0;
    for (int i = 0; i < jumlahCatatan; i++) {
        if (strcmp(catatan[i].judul, judul) == 0) {
            ditemukan = 1;
            printf("\n\t\t\t=== Isi Catatan ===\n\n");
            printf("\t\t\tJudul : %s\n", catatan[i].judul);
            printf("\t\t\tTanggal: %s\n", catatan[i].tanggal);
            printf("\t\t\t-----------------------------------------\n");
            printf("\t\t\tIsi Pesan:\n");
            
            // Decrypt and display note content
            char decryptedContent[500];
            strcpy(decryptedContent, catatan[i].isi);
            dekripsiVigenere(decryptedContent, kunciEnkripsi);
            printf("\n");
            printf("\t\t\t%s\n", decryptedContent);

            printf("\t\t\t-----------------------------------------\n");
            break;
        }
    }
    if (!ditemukan) {
        printf("Catatan dengan judul '%s' tidak ditemukan.\n", judul);
    }
}

// Fungsi untuk menyimpan catatan dari array ke file setelah diurutkan berdasarkan tanggal
void simpanCatatanKeFile(struct Catatan *catatan, int jumlahCatatan) {
    qsort(catatan, jumlahCatatan, sizeof(struct Catatan), bandingkanCatatan); // Urutkan catatan berdasarkan tanggal
    FILE *file = fopen("Catatan.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    for (int i = 0; i < jumlahCatatan; i++) {
        fprintf(file, "%d|%s|%s|%s\n", catatan[i].no, catatan[i].judul, catatan[i].tanggal, catatan[i].isi);
    }
    fclose(file);
}

// Fungsi untuk mengedit catatan berdasarkan judul
void editCatatanBerdasarkanJudul(struct Catatan *catatan, int jumlahCatatan, char *judul, char *kunciEnkripsi) {
    for (int i = 0; i < jumlahCatatan; i++) {
        if (strcmp(catatan[i].judul, judul) == 0) {
            // Dekripsi isi catatan sebelum mengedit
            dekripsiVigenere(catatan[i].isi, kunciEnkripsi);
            
            printf("\t\t\tJudul: ");
            scanf(" %[^\n]s", catatan[i].judul);
            printf("\t\t\tTanggal (YYYY-MM-DD): ");
            scanf(" %[^\n]s", catatan[i].tanggal);
            printf("\t\t\tIsi pesan: ");
            scanf(" %[^\n]s", catatan[i].isi);
            
            // Enkripsi kembali isi catatan setelah mengedit
            enkripsiVigenere(catatan[i].isi, kunciEnkripsi);
            
            printf("Catatan dengan judul '%s' berhasil diubah.\n", judul);
            return;
        }
    }
    printf("Catatan dengan judul '%s' tidak ditemukan.\n", judul);
}

// Fungsi untuk menghapus catatan berdasarkan judul
void hapusCatatanBerdasarkanJudul(struct Catatan *catatan, int *jumlahCatatan, char *judul) {
    int ditemukan = 0;
    for (int i = 0; i < *jumlahCatatan; i++) {
        if (strcmp(catatan[i].judul, judul) == 0) {
            ditemukan = 1;
            for (int j = i; j < *jumlahCatatan - 1; j++) {
                catatan[j] = catatan[j + 1];
            }
            (*jumlahCatatan)--;
            printf("Catatan dengan judul '%s' berhasil dihapus.\n", judul);
            break;
        }
    }
    if (!ditemukan) {
        printf("Catatan dengan judul '%s' tidak ditemukan.\n", judul);
    } else {
        // Menulis ulang seluruh catatan ke file setelah penghapusan
        simpanCatatanKeFile(catatan, *jumlahCatatan);
    }
}

void hapusLayar() {
    system("cls"); 
}

// Function to get user input for adding a new note
void getInputTambahCatatan(char judul[], char tanggal[], char isi[]) {
    printf("\t\t\tJudul: ");
    scanf(" %[^\n]s", judul);
    printf("\t\t\tTanggal (YYYY-MM-DD): ");
    scanf(" %[^\n]s", tanggal);
    printf("\t\t\tIsi pesan: ");
    scanf(" %[^\n]s", isi);
}

// Function to get user input for editing an existing note
void getInputEditCatatan(char judul[], char tanggal[], char isi[]) {
    printf("\t\t\tJudul: ");
    scanf(" %[^\n]s", judul);
    printf("\t\t\tTanggal (YYYY-MM-DD): ");
    scanf(" %[^\n]s", tanggal);
    printf("\t\t\tIsi pesan: ");
    scanf(" %[^\n]s", isi);
}

// Function to get user input for deleting a note
void getInputHapusCatatan(char judul[]) {
    printf("\t\t\tMasukkan judul catatan yang ingin dihapus: ");
    scanf(" %[^\n]s", judul);
}

// Function to handle user input for choosing an option from the main menu
int getInputMenu() {
    int pilihan;
    printf("\t\t\tPilihan Anda: ");
    scanf("%d", &pilihan);
    return pilihan;
}

// Function to wait for user to press Enter to continue
void waitForEnter() {
    printf("\nTekan Enter untuk melanjutkan...");
    getchar(); // Consume newline character left in the buffer
    getchar(); // Wait for user to press Enter
}

// Function to display a header for the menu
void tampilkanHeaderMenu() {
    printf("\n\t\t\t=== Aplikasi Pencatatan Sederhana ===\n\n");
}

// Function to display the main menu options
void tampilkanMenuUtama() {
    printf("\t\t\t1. Tampilkan Isi Catatan\n");
    printf("\t\t\t2. Tambah Catatan\n");
    printf("\t\t\t3. Edit Catatan\n");
    printf("\t\t\t4. Hapus Catatan\n");
    printf("\t\t\t5. Keluar\n");
}

int main() {
    struct Catatan catatan[100]; // Assume maximum 100 notes
    int jumlahCatatan = bacaCatatanDariFile(catatan);
    
    char kunciEnkripsi[100] = "SECRET"; // Default encryption key
    
    int pilihan;
    do {
        hapusLayar();
        tampilkanHeaderMenu();
        tampilkanCatatan(catatan, jumlahCatatan); // Display the list of notes
        printf("\n\n\n");
        tampilkanMenuUtama();
        pilihan = getInputMenu(); // Get user menu choice

        switch (pilihan) {
            case 1: {
                hapusLayar();
                tampilkanCatatan(catatan, jumlahCatatan); // Display the list of notes
                printf("\n\n\n");
                char judul[100];
                printf("\t\t\tMasukkan judul catatan yang ingin ditampilkan: ");
                scanf(" %[^\n]s", judul);
                tampilkanIsiCatatanBerdasarkanJudul(catatan, jumlahCatatan, judul, kunciEnkripsi);
                break;
            }
            case 2: {
                hapusLayar();
                tampilkanCatatan(catatan, jumlahCatatan); // Display the list of notes
                printf("\n\n\n");
                char judul[100], tanggal[20], isi[500];
                getInputTambahCatatan(judul, tanggal, isi); // Get input for adding a new note
                struct Catatan catatanBaru = buatCatatan(judul, tanggal, isi, kunciEnkripsi);
                tambahCatatanKeFile(catatanBaru);
                printf("Catatan berhasil ditambahkan.\n");
                catatan[jumlahCatatan++] = catatanBaru; // Add the new note to the array
                break;
            }
            case 3: {
                hapusLayar();
                tampilkanCatatan(catatan, jumlahCatatan); // Display the list of notes
                printf("\n\n\n");
                char judul[100], tanggal[20], isi[500];
                getInputEditCatatan(judul, tanggal, isi); // Get input for editing a note
                editCatatanBerdasarkanJudul(catatan, jumlahCatatan, judul, kunciEnkripsi);
                simpanCatatanKeFile(catatan, jumlahCatatan); // Save changes to the file
                break;
            }
            case 4: {
                hapusLayar();
                tampilkanCatatan(catatan, jumlahCatatan); // Display the list of notes
                printf("\n\n\n");
                char judul[100];
                getInputHapusCatatan(judul); // Get input for deleting a note
                hapusCatatanBerdasarkanJudul(catatan, &jumlahCatatan, judul);
                break;
            }
            case 5:
                printf("Keluar dari aplikasi.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
        waitForEnter(); // Wait for user to press Enter before continuing
    } while (pilihan != 5);

    return 0;
}
