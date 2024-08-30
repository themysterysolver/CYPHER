#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
void encrypt1(char *s) {
    int len = strlen(s);
    for (int j = 0, l = 0; s[j]; j++) {
        for (int k = 1; k <= len; k++) {
            if (!(j % k)) {
                if (l) {
                    s[j] += (k % 10);
                    l = 0;
                } else {
                    s[j] -= (k % 10);
                    l = 1;
                }
            }
        }
    }
}

void decrypt1(char *s) {
    int len = strlen(s);
    for (int j = 0, l = 0; s[j]; j++) {
        for (int k = 1; k <= len; k++) {
            if (!(j % k)) {
                if (l) {
                    s[j] -= (k % 10);
                    l = 0;
                } else {
                    s[j] += (k % 10);
                    l = 1;
                }
            }
        }
    }
}
void encrypt2(char *s) {
    for (int i = 0; s[i]; i++) {
        for (int j = 1; j < 11; j++) {
            if (s[i] % j == 0) {
                s[i] -= j;
            }
        }
    }
}

void decrypt2(char *s) {
    for (int i = 0; s[i]; i++) {
        for (int j = 10; j > 0; j--) {
            if (s[i] % j == 0) {
                s[i] += j;
            }
        }
    }
}
void encrypt3(char *s) {
    FILE *fp = fopen("encrypt.DAT", "w");
    int len = strlen(s);
    int a[100];
    for (int i = 0; i < len; i++) {
        a[i] = rand() % 10;
        s[i] += pow(-1, i) * a[i];
    }
    fwrite(&len, sizeof(len), 1, fp);
    fwrite(s, sizeof(char), len, fp);
    fwrite(a, sizeof(int), len, fp);
    fclose(fp);
}

void decrypt3(char *s) {
    int len;
    int a[100];
    FILE *fp = fopen("encrypt.DAT", "r");
    fread(&len, sizeof(len), 1, fp);
    fread(s, sizeof(char), len, fp);
    fread(a, sizeof(int), len, fp);
    for (int i = 0; i < len; i++) {
        s[i] -= pow(-1, i) * a[i];
    }
    fclose(fp);
}

void encrypt4(char *s) {
    for (int i = 0; s[i]; i++) {
        s[i] -= 2;
    }
}

void decrypt4(char *s) {
    for (int i = 0; s[i]; i++) {
        s[i] += 2;
    }
}
void encrypt5(char *s) {
    for (int i = 0; s[i]; i++) {
        for (int j = 1; j <= i; j++) {
            if (i % j) {
                s[i] += pow(-1, j) * j;
            }
        }
    }
    s[0] += 2;
    s[1] -= 2;
}

void decrypt5(char *s) {
    s[0] -= 2;
    s[1] += 2;
    for (int i = 0; s[i]; i++) {
        for (int j = 1; j <= i; j++) {
            if (i % j) {
                s[i] -= pow(-1, j) * j;
            }
        }
    }
}
void encrypt6(unsigned char *s) {
    FILE *fp = fopen("ari.txt", "w");
    int len = strlen(s);
    int arr[100];
    for (int i = 0; i < len; i++) {
        arr[i] = influenza(s[i] + 33);
        s[i] = arr[i];
    }
    fwrite(arr, sizeof(int), len, fp);
    fclose(fp);
}

void decrypt6(unsigned char *s) {
    FILE *fp = fopen("ari.txt", "rb");
    int len = strlen(s);
    int arr[100];
    fread(arr, sizeof(int), len, fp);
    for (int i = 0; i < len; i++) {
        s[i] = deinfluenza(arr[i]) - 33;
    }
    fclose(fp);
}

void encrypt7(char *s) {
    for (int i = 0; s[i]; i++) {
        s[i] = ~s[i];
    }
}

void decrypt7(char *s) {
    for (int i = 0; s[i]; i++) {
        s[i] = ~s[i];
    }
}
int influenza(int a) {
    int sum = 0, i = 0;
    while (a > 0) {
        sum += (a % 6) * pow(10, i);
        a /= 6;
        i++;
    }
    return sum;
}

int deinfluenza(int a) {
    int sum = 0, i = 0;
    while (a > 0) {
        sum += (a % 10) * pow(6, i);
        a /= 10;
        i++;
    }
    return sum;
}

void encrypt(FILE *input, FILE *output) {
    char s[500];
    fgets(s, 500, input);
    puts(s);

    srand(time(0));
    int num_encryptions = rand() % 5 + 1;
    printf("%d\n", num_encryptions);
    fprintf(output, "%c", 'A' + num_encryptions);

    int used_encryptions[7] = {0};
    for (int i = 0; i < num_encryptions; i++) {
        int enc_type;
        do {
            enc_type = rand() % 7;
        } while (used_encryptions[enc_type]);
        used_encryptions[enc_type] = 1;

        fprintf(output, "%c", 'A' + enc_type);
        printf("%d\n", enc_type);

        switch (enc_type) {
            case 0: encrypt1(s); break;
            case 1: encrypt2(s); break;
            case 2: encrypt3(s); break;
            case 3: encrypt4(s); break;
            case 4: encrypt5(s); break;
            case 5: encrypt6((unsigned char *)s); break;
            case 6: encrypt7(s); break;
        }
    }
    puts(s);
    fprintf(output, "%s", s);
}
void decrypt(FILE *input, FILE *output) {
    char c, s[500];
    fscanf(input, "%c", &c);
    int num_encryptions = c - 'A';
    int decrypt_types[num_encryptions];

    for (int i = 0; i < num_encryptions; i++) {
        fscanf(input, "%c", &c);
        decrypt_types[num_encryptions - i - 1] = c - 'A';
    }

    fgets(s, 500, input);
    for (int i = 0; i < num_encryptions; i++) {
        switch (decrypt_types[i]) {
            case 0: decrypt1(s); break;
            case 1: decrypt2(s); break;
            case 2: decrypt3(s); break;
            case 3: decrypt4(s); break;
            case 4: decrypt5(s); break;
            case 5: decrypt6((unsigned char *)s); break;
            case 6: decrypt7(s); break;
        }
        printf("%d\n", decrypt_types[i]);
    }
    puts(s);
    fputs(s, output);
}

int main() {
    FILE *input = fopen("Message.txt", "r");
    FILE *encrypted = fopen("Encrypted.txt", "w+");
    FILE *decrypted = fopen("Decrypted.txt", "w+");

    rewind(input);
    encrypt(input, encrypted);

    rewind(encrypted);
    decrypt(encrypted, decrypted);

    fclose(input);
    fclose(encrypted);
    fclose(decrypted);

    return 0;
}
