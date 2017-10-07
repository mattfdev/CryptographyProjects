#include <iostream>
#include <openssl/evp.h>
#include <openssl/md5.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {
    EVP_MD_CTX ctx;
    EVP_MD_CTX_init(&ctx);
    const EVP_MD *md;
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len;
    ifstream inFile;
    string unhashed_file;
    string line;
    string filename;

    if (argc != 2) {
       cout << "Incorrect number of arguments sent the program, try adding a file name?";
        return 1;
    }

    //Read specified file in, and feed to md5 digest function
    filename = argv[1];
    cout << "Filename given: " + filename << "\n";
    inFile.open(filename);
    if (inFile.fail()) {
        cout << "Unable to open file";
    }
    md = EVP_md5();
    EVP_DigestInit_ex(&ctx, md, nullptr);
    stringstream buffer;
    // WOrkfing
    buffer << inFile.rdbuf();
    //cout << buffer.str().c_str();
    char* contents = strdup(buffer.str().c_str()) ;
    EVP_DigestUpdate(&ctx, contents, strlen(contents));
    inFile.close();

    //Print out final digest
    EVP_DigestFinal(&ctx, md_value, &md_len);
    printf("Digest is: ");
    for(int i = 0; i < md_len; i++)  {
        printf("%02x", md_value[i]);
    }

    return 0;
}