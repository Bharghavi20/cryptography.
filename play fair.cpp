#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void prepare_key_table(const char* key, char key_table[SIZE][SIZE]) {
    int alphabets[26] = {0};
    int i, j, k, key_len = strlen(key);
    char ch;

    // Fill the key table with the key
    for (i = 0, k = 0; k < key_len; k++) {
        ch = toupper(key[k]);
        if (ch == 'J') ch = 'I'; // Treat 'J' as 'I'
        if (!alphabets[ch - 'A'] && ch >= 'A' && ch <= 'Z') {
            key_table[i / SIZE][i % SIZE] = ch;
            alphabets[ch - 'A'] = 1;
            i++;
        }
    }

    // Fill the remaining spaces with other alphabets
    for (ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue; // Skip 'J'
        if (!alphabets[ch - 'A']) {
            key_table[i / SIZE][i % SIZE] = ch;
            i++;
        }
    }
}

void print_key_table(char key_table[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", key_table[i][j]);
        }
        printf("\n");
    }
}

void prepare_text(char* text, char* prepared_text) {
    int i, j;
    for (i = 0, j = 0; text[i] != '\0'; i++) {
        if (text[i] == ' ') continue; // Remove spaces
        prepared_text[j++] = toupper(text[i]);
    }
    prepared_text[j] = '\0';
}

void process_digraphs(char* text) {
    int len = strlen(text);
    for (int i = 0; i < len; i += 2) {
        if (text[i] == text[i + 1]) {
            memmove(&text[i + 2], &text[i + 1], len - i);
            text[i + 1] = 'X';
            len++;
        }
    }
    if (len % 2 != 0) {
        text[len] = 'X';
        text[len + 1] = '\0';
    }
}

void find_position(char key_table[SIZE][SIZE], char ch, int* row, int* col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (key_table[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encrypt_digraphs(char* text, char key_table[SIZE][SIZE], char* ciphertext) {
    int i, row1, col1, row2, col2;
    for (i = 0; text[i] != '\0'; i += 2) {
        find_position(key_table, text[i], &row1, &col1);
        find_position(key_table, text[i + 1], &row2, &col2);

        if (row1 == row2) {
            ciphertext[i] = key_table[row1][(col1 + 1) % SIZE];
            ciphertext[i + 1] = key_table[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            ciphertext[i] = key_table[(row1 + 1) % SIZE][col1];
            ciphertext[i + 1] = key_table[(row2 + 1) % SIZE][col2];
        } else {
            ciphertext[i] = key_table[row1][col2];
            ciphertext[i + 1] = key_table[row2][col1];
        }
    }
    ciphertext[i] = '\0';
}

int main() {
    char key[100], plaintext[100], prepared_text[100], ciphertext[100];
    char key_table[SIZE][SIZE];

    printf("Enter the keyword: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline character

    prepare_key_table(key, key_table);

    printf("Key Table:\n");
    print_key_table(key_table);

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

    prepare_text(plaintext, prepared_text);
    process_digraphs(prepared_text);

    encrypt_digraphs(prepared_text, key_table, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);

    return 0;
}
