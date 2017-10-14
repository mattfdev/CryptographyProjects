#include <iostream>
#include <openssl/evp.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>


using namespace std;

int main(int argc, char *argv[]) {
    EVP_MD_CTX ctx, ctx2;
    EVP_MD_CTX_init(&ctx);
    EVP_MD_CTX_init(&ctx2);
    const EVP_MD *md;
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned char md_value2[EVP_MAX_MD_SIZE];
    unsigned int md_len;
    fstream inFile;
    string a1, a2, filename;
    char h1[EVP_MAX_MD_SIZE];
    char h2[EVP_MAX_MD_SIZE];
    stringstream buffer;

    if (argc != 2) {
        cout << "Incorrect number of arguments sent to the program, try adding a file name?" << endl;
        return 1;
    }

    //Read specified file in, and feed to md5 digest function
    filename = argv[1];
    cout << "Filename given: " + filename << endl;
    inFile.open(filename);
    if (inFile.fail()) {
        cout << "Unable to open file" << endl;
        return 1;
    }
    md = EVP_md5();
    EVP_DigestInit_ex(&ctx, md, nullptr);
    buffer << inFile.rdbuf();
    char* contents = strdup(buffer.str().c_str());
    char* contents_bit_shifted = strdup(buffer.str().c_str());
    size_t contents_size = strlen(contents);
    int bit_similarity_counter = 0;
    EVP_DigestUpdate(&ctx, contents, contents_size);

    //Print out initial file md5 digest
    EVP_DigestFinal(&ctx, md_value, &md_len);
    cout << "MD5 hash for input file [H1] −−> ";
    for(int i = 0; i < md_len; i++)  {
        printf("%02x", md_value[i]);
        sprintf(h1,"%x", md_value[i]);
        a1.append(h1);
    }

    cout << endl << "Flipping Last bit ..." << endl;
    contents_bit_shifted[contents_size - 1] = ~contents_bit_shifted[contents_size - 1];
    EVP_DigestInit_ex(&ctx2, md, nullptr);
    EVP_DigestUpdate(&ctx2, contents_bit_shifted, contents_size);
    EVP_DigestFinal(&ctx2, md_value2, &md_len);
    cout << "MD5 hash for input file [H2] −−> ";
    for (int i = 0; i < md_len; i++)  {
        printf("%02x", md_value2[i]);
	    sprintf(h2,"%x", md_value2[i]);
        a2.append(h2);
    }

    for (int i = 0; i < a1.length(); i++) {
        if (a1.c_str()[i] == a2.c_str()[i]) {
            bit_similarity_counter++;
        }
    }
    printf("\nCount of similar characters: %i\n", bit_similarity_counter*32);

    inFile.close();
    return 0;
}