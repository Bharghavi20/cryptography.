#include <stdio.h>
#include <string.h>
#include <stdint.h>

// Simplified S-box (substitution box)
int S_BOX[4][16] = {
    { 14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
    {  0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
    {  4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
    { 15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13}
};

// Simplified permutation (P-box)
int P_BOX[32] = {
    16,  7, 20, 21,
    29, 12, 28, 17,
     1, 15, 23, 26,
     5, 18, 31, 10,
     2,  8, 24, 14,
    32, 27,  3,  9,
    19, 13, 30,  6,
    22, 11,  4, 25
};

// Key schedule array (16 subkeys)
uint64_t subkeys[16];

// Simplified key schedule
void generateSubkeys(uint64_t key) {
    for (int i = 0; i < 16; i++) {
        subkeys[i] = (key >> (16 - i)) & 0xFFFFFFFF; // Simplified subkey generation
    }
}

// Simplified Feistel function
uint32_t feistel(uint32_t half_block, uint64_t subkey) {
    uint32_t expanded = half_block; // No expansion in simplified version
    uint32_t sbox_output = S_BOX[expanded & 0x3][subkey & 0xF]; // Simplified S-box lookup
    uint32_t pbox_output = 0;

    for (int i = 0; i < 32; i++) {
        pbox_output |= ((sbox_output >> i) & 1) << (P_BOX[i] - 1);
    }

    return pbox_output;
}

// DES encryption function
uint64_t desEncrypt(uint64_t plaintext, uint64_t key) {
    generateSubkeys(key);

    uint32_t left = (plaintext >> 32) & 0xFFFFFFFF;
    uint32_t right = plaintext & 0xFFFFFFFF;

    for (int i = 0; i < 16; i++) {
        uint32_t temp = right;
        right = left ^ feistel(right, subkeys[i]);
        left = temp;
    }

    return ((uint64_t)right << 32) | left;
}

// DES decryption function
uint64_t desDecrypt(uint64_t ciphertext, uint64_t key) {
    generateSubkeys(key);

    uint32_t left = (ciphertext >> 32) & 0xFFFFFFFF;
    uint32_t right = ciphertext & 0xFFFFFFFF;

    for (int i = 15; i >= 0; i--) {
        uint32_t temp = right;
        right = left ^ feistel(right, subkeys[i]);
        left = temp;
    }

    return ((uint64_t)right << 32) | left;
}

int main() {
    uint64_t plaintext = 0x1234567890abcdef; // Example 64-bit plaintext
    uint64_t key = 0x133457799bbcdff1;      // Example 64-bit key

    printf("Plaintext: %016lx\n", plaintext);

    uint64_t encrypted = desEncrypt(plaintext, key);
    printf("Encrypted: %016lx\n", encrypted);

    uint64_t decrypted = desDecrypt(encrypted, key);
    printf("Decrypted: %016lx\n", decrypted);

    return 0;
}
