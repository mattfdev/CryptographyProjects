//
// Created by Matthew Francis on 2017-11-29.
//
#include <stdio.h>
#include <openssl/ossl_typ.h>
#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// **************************** Functions ****************************
/* ======================= Encryption ======================= */
/*
Encrypt a message m with a key k in ECB mode using Light−DES as follows :
        c = Light−DES(k, m)
Args :
        m should be a bytestring multiple of 16 bytes ( i . e . a sequence of characters
such as ’Hello... ’ or ’\x02\x04... ’)
k should be a bytestring of length exactly 16 bytes.
Return :
        The bytestring ciphertext c */
/* ======================= Decryption ======================= */
/* Decrypt a ciphertext c with a key k in ECB mode using Light−DES as follows : m=Light−DES(k, c)
Args :
        c should be a bytestring multiple of 16 bytes ( i . e . a sequence of characters such as ’Hello... ’ or ’\x02\x04... ’)
k should be a bytestring of length exactly 16 bytes.
Return :
        The bytestring message m. */
/* ======================= Generating Puzzles ======================= */
//Puzzle[i] = S − AES(k = 0_14||i, plaintext = Puzzle||i||secreti
int generateRandomNum() {
    return rand() % 9000 + 1000;
}

unsigned char** gen_puzzles() {
    int num_of_keys = 32;
    unsigned char** ciphertext = malloc(sizeof(char**)*(num_of_keys));
    int outlen1, outlen2;
    int secret_array[num_of_keys];
    for (int i = 0; i < num_of_keys; i++) {
        secret_array[i] = generateRandomNum();
        unsigned char identifier[17];
        ciphertext[i] = (unsigned char *)malloc (17 * sizeof (char));
        // Create 16bit long string of key.
        if (i < 10) {
            snprintf(identifier,17,"%s%d%c","000000000000000",i,'\0');
        } else {
            int dig1 = i / 10;
            int dig2 = i % 10;
            snprintf(identifier,17,"%s%d%d%c","00000000000000",dig1,dig2,'\0');
        }
        unsigned char* plaintext = malloc(num_of_keys * sizeof (char));
        snprintf(plaintext,num_of_keys,"%s%d%d","puzzle",i,secret_array[i]);
        EVP_CIPHER_CTX ctx;
        EVP_EncryptInit(&ctx, EVP_aes_128_ecb(), identifier, NULL);
        EVP_EncryptUpdate(&ctx, ciphertext[i], &outlen1, plaintext, sizeof(plaintext));
        EVP_EncryptFinal(&ctx, ciphertext[i] + outlen1, &outlen2);
    }
    return ciphertext;
}
int solve_puzzle(unsigned char** puzzles) {
    // Choose a random puzzle to solve.
    int puzzle_to_solve = rand() % 32;
    unsigned char* puzzle = puzzles[puzzle_to_solve];
    unsigned char* plaintext = malloc(sizeof(char) * 32);
    int outlen1;
    unsigned char* key = malloc(sizeof(char) * 17);
    for (int i = 0; i < 32; i++) {
        if (i < 10) {
            snprintf(key,17,"%s%d%c","00000000000000",i,'\0');
        } else {
            int dig1 = i / 10;
            int dig2 = i % 10;
            snprintf(key,17,"%s%d%d%c","00000000000000",dig1,dig2,'\0');
        }
        printf("%s\n", key);
        EVP_CIPHER_CTX ctx;
        EVP_DecryptInit(&ctx, EVP_aes_128_ecb(), key, NULL);
        EVP_DecryptUpdate(&ctx, plaintext, &outlen1, puzzle, sizeof(puzzle));
        EVP_DecryptFinal(&ctx, plaintext + outlen1, &outlen1);
        printf("%s\n", plaintext);
    }
    return 0;
}
/* gen_puzzles ()
 *
This is Alice . She generates 2^16 random keys and 2^16 puzzles . A puzzle has the following formula :
puzzle[i] = aes_enc(key = 0..0 + i, plaintext ="Puzzle" + chr(i) + chr(j) + alice_keys [ i ])
This function shall fill in the alice_keys list and shall return a list of 2^16 puzzles . */
/* ======================= S o l v i n g a P u z z l e ======================= * /
  solve_puzzle ( puzzles )
This is Bob’s function. He tries to solve one random puzzle. His purpose is to
solve one random puzzle offered by Alice .
This function shall fill in the bob_key list with the secret discovered by Bob. The function shall return the index of the chosen puzzle. */
int main(int argc, char const *argv[]) {
    srand(time(NULL));
    unsigned char** alice_keys;
    char* bob_key;
    /* Alice generates some puzzles */
    alice_keys = gen_puzzles();
    printf("%s \n", alice_keys[15]);
    /* Bob solves one random puzzle and discovers the secret */
    int x = solve_puzzle(alice_keys);
    //printf("Bob’s Secret key %s \n", bob_key[0]);
    //printf("Alice’s secret key: %s \n", alice_keys[x]);
    //if (bob_key[0] == alice_keys[])
    //    printf("Puzzle Solved ! \n");
    //else
    //    printf("Puzzle Not Solved :( \n");
    return 0;
}
