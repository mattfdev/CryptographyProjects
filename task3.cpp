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
    EVP_MD_CTX ctx, ctx2; //These are the contexts hash objects. More specifically, message digests (MD).
    EVP_MD_CTX_init(&ctx); //These are used to initialize the hash/MD. Note how they point to the address of the context.
    EVP_MD_CTX_init(&ctx2);
    const EVP_MD *md; //md is fixed as a constant for a message-digest function.
    unsigned char md_value[EVP_MAX_MD_SIZE]; // This is the value of the MD.
    unsigned int md_len; //This is the length of the MD
    fstream inFile; //this reads inFile
    string filename;
    stringstream buffer;

    if (argc != 2) {
       cout << "Incorrect number of arguments sent the program, try adding a file name?\n";
        return 1;
    }

    //Read specified file in, and feed to md5 digest function
    filename = argv[1]; //The 2nd argument of the command chould be a file name. The following lines verify this.
    cout << "Filename given: " + filename << endl;
    inFile.open(filename);
    if (inFile.fail()) {
        cout << "Unable to open file";
        return 1;
    }
    md = EVP_md5(); //This calls the MD5 algorithm on md.
    EVP_DigestInit_ex(&ctx, md, nullptr); //This initializes the hash function @ ctx, with the nullptr ensuring that the default implementation of the hash function is used.
    buffer << inFile.rdbuf(); //inFile results in a stream of information. .rdbuf returns a pointer to this streamed information. Essentially, the contents of inFile are being written to bugger
    char* contents = strdup(buffer.str().c_str()); //strdup duplicates the string in buffer to contents.
    size_t contents_size = strlen(contents); //This is the size of contents.
    EVP_DigestUpdate(&ctx, contents, contents_size); //This updates the digest initialized on line 40. It hashes the entirety of contents.


    //Print out initial file md5 digest
    EVP_DigestFinal(&ctx, md_value, &md_len); //This retrieves the hash value called in line 44 and places it into md_value.
    cout << "MD5 hash for input file [H1] −−> ";
    for(int i = 0; i < md_len; i++)  {
        printf("%02x", md_value[i]);
    }

    // Alter the last byte(char) of the file contents, simpler than bit flipping.
    char contents_bit_shifted[contents_size];
    strncpy(contents_bit_shifted, contents, contents_size);
    cout << endl << "Flipping Last bit ..." << endl;
    contents_bit_shifted[contents_size - 1] = ' ';
    EVP_DigestInit_ex(&ctx2, md, nullptr);
    EVP_DigestUpdate(&ctx2, contents_bit_shifted, strlen(contents_bit_shifted));
    EVP_DigestFinal(&ctx2, md_value, &md_len);
    cout << "MD5 hash for input file [H2] −−> ";
    for(int i = 0; i < md_len; i++)  {
        printf("%02x", md_value[i]);
    }
    cout << endl << "These two files have 8 different bits (1 byte)\n";

    inFile.close();
    return 0;
}

//https://linux.die.net/man/3/evp_digestinit
