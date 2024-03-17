
#ifndef ALLMODUL_H
#define ALLMODUL_H
#define MAX_CATATAN 1000
#define MAX_KEY 100
#define MAX 100

// Struktur data untuk catatan
struct Catatan {
    int no;
    char judul[100];
    char tanggal[20];
    char isi[1000];
};

// Struktur pengguna
struct users {
    char Nama[40];
    char Email[30];
    char password[20];
    char username[20];
};

//modul geraldin
void enkripsi(char teks[], char kunci[]);
void tambahCatatan();

//modul ikhsan
void dekripsiVigenere(char teks[], char kunci[]);
int bacaCatatanDariFile(struct Catatan *catatan);
void tampilkanCatatan(struct Catatan *catatan, int jumlahCatatan);
void tampilkanIsiCatatanBerdasarkanJudul(struct Catatan *catatan, int jumlahCatatan, char *judul, char *kunciEnkripsi);
void simpanCatatanKeFile(struct Catatan *catatan, int jumlahCatatan);
void editCatatanBerdasarkanJudul(struct Catatan *catatan, int jumlahCatatan, char *judul, char *kunciEnkripsi);
void hapusCatatanBerdasarkanJudul(struct Catatan *catatan, int *jumlahCatatan, char *judul);

//modul Rizky
void multiplyMatrix(int key[MAX][MAX], int message[MAX][1], int res[MAX][1], int n);
void encryptPassword(char *plain_password, int key[MAX][MAX], char *encrypted_password, int n);
bool isEmailValid(char *email);
bool isUsernameExists(char *username);
bool isAlphaNumeric(char *password);
void Register(int index);

//modul dhea
void multiplyMatrix(int key[MAX][MAX], int message[MAX][1], int res[MAX][1], int n);
void decryptMessage(int key[MAX][MAX], int inverse[MAX][MAX], char cipher_text[], int n);
int checkCredentials(char *username, char *password, char *file_name);

//modul annisa
void encryptPassword(char *password, int shift);
void decryptPassword(char *password, int shift);
void readEncryptedPassword(char *encryptedPassword);
void saveEncryptedPassword(char *encrypte);


#endif
