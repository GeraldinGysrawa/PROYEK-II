#ifndef CATATAN_H
#define CATATAN_H

#define MAX_KEY 100
#define MAX_CATATAN 100

struct Catatan {
    int no;
    char judul[100];
    char tanggal[11];
    char isi[1000];
};

extern int nomorCatatanTerakhir;

//geraldin
void dekripsiVigenere(char teks[], char kunci[]);
void tambahCatatan();

//ikhsan
void enkripsiVigenere(char teks[], char kunci[]);
void tampilDaftarCatatan();
void tampilIsiCatatan(char judul[]);
void editCatatan(char judul[]);
void hapusCatatan(char judul[]);
void hapusLayar();
void MenuUtama();

//annisa
void encryptPassword(char *password, int shift);
void decryptPassword(char *password, int shift);
void readEncryptedPassword(char *encryptedPassword);
void saveEncryptedPassword(char *encrypte);

#endif /* CATATAN_H */
