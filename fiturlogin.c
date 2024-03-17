#include <stdio.h>
#include <string.h>

#define MAX 100

// Fungsi untuk memeriksa kecocokan username dan password
int checkCredentials(char *username, char *password, char *file_name);

int main() {
    char username[MAX], password[MAX];
    printf("Username: ");
    fgets(username, MAX, stdin);
    username[strcspn(username, "\n")] = '\0'; // Menghapus karakter newline dari username
    printf("Password: ");
    fgets(password, MAX, stdin);
    password[strcspn(password, "\n")] = '\0'; // Menghapus karakter newline dari password

    // Memeriksa kecocokan username dan password
    if (checkCredentials(username, password, "datauser.txt")) {
        printf("Login berhasil!\n");
    } else {
        printf("Login gagal. Username atau password salah.\n");
    }

    return 0;
}

// Fungsi untuk memeriksa kecocokan username dan password
int checkCredentials(char *username, char *password, char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return 0;
    }

    char file_username[MAX], file_password[MAX];
    while (fscanf(file, "%s %s", file_username, file_password) != EOF) {
        // Membandingkan input dengan data di file
        if (strcmp(file_username, username) == 0 && strcmp(file_password, password) == 0) {
            fclose(file);
            return 1; // Username dan password cocok
        }
    }

    fclose(file);
    return 0; // Username dan password tidak cocok
}
