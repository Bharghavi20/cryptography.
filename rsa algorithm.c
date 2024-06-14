#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}
int mod_inverse(int e, int phi) {
    int t = 0, newt = 1;
    int r = phi, newr = e;
    while (newr != 0) {
        int quotient = r / newr;
        int temp = newt;
        newt = t - quotient * newt;
        t = temp;
        temp = newr;
        newr = r - quotient * newr;
        r = temp;
    }
    if (r > 1) return -1; // e is not invertible
    if (t < 0) t += phi;
    return t;
}
int main() {
    int p, q, e, message;
    printf("Enter a prime number p: ");
    scanf("%d", &p);
    printf("Enter a prime number q: ");
    scanf("%d", &q);
    printf("Enter the public exponent e: ");
    scanf("%d", &e);
    printf("Enter the message to be encrypted (as an integer): ");
    scanf("%d", &message);
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    while (gcd(e, phi) != 1) {
        printf("The number e is not coprime with phi. Enter another public exponent e: ");
        scanf("%d", &e);
    }
    int d = mod_inverse(e, phi);
    if (d == -1) {
        printf("Modular inverse not found. Choose a different e.\n");
        return 1;
    }
    printf("Public Key: (e = %d, n = %d)\n", e, n);
    printf("Private Key: (d = %d, n = %d)\n", d, n);
    printf("Original Message: %d\n", message);
    long long encrypted = mod_exp(message, e, n);
    printf("Encrypted Message: %lld\n", encrypted);
    long long decrypted = mod_exp(encrypted, d, n);
    printf("Decrypted Message: %lld\n", decrypted);
    return 0;
}