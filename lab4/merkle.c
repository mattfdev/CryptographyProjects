//
// Created by Matthew Francis on 2017-11-29.
//
#include <stdio.h>

/* **************************** Functions **************************** */
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
/* gen_puzzles ()
This is Alice . She generates 2^16 random keys and 2^16 puzzles . A puzzle has the following formula :
puzzle[i] = aes_enc(key = 0..0 + i, plaintext ="Puzzle" + chr(i) + chr(j) + alice_keys [ i ])
This function shall fill in the alice_keys list and shall return a list of 2^16 puzzles . */
/* ======================= S o l v i n g a P u z z l e ======================= * / /* solve_puzzle ( puzzles )
This is Bob’s function. He tries to solve one random puzzle. His purpose is to
solve one random puzzle offered by Alice .
This function shall fill in the bob_key list with the secret discovered by Bob. The function shall return the index of the chosen puzzle. */
int main(int argc, char const *argv[]) {
    char alice_keys = [];
    char bob_key = [];
    /* Alice generates some puzzles */
    puzzles = gen_puzzles();
    /* Bob solves one random puzzle and discovers the secret */
    x = solve_puzzle(puzzles);
    printf("Bob’s Secret key %s \n", bob_key[0]);
    printf("Alice’s secret key: %s \n", alice_keys[x]);
    if (bob_key[0] == alice_keys[x])
        printf("Puzzle Solved ! \n");
    else
        printf("Puzzle Not Solved :( \n")
    return 0;
}